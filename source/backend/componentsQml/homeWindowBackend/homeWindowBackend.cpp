#include "homeWindowBackend.h"
#include <iostream>
#include <qqmlcomponent.h>
#include <QQuickItem>
#include <filesystem>
#include <system_error>
#include <stdexcept>
#include "../applicationBackend/applicationBackend.hpp"
#include "../utils/filesGrabber/filesGrabber.h"

namespace fs = std::filesystem;

HomeWindowBackend::HomeWindowBackend(QObject *parent) : QObject{parent} {}

void HomeWindowBackend::startSession() {
    if(!propertysValueAreValids())
        return;

    openSessionWindow();
}

bool HomeWindowBackend::propertysValueAreValids() {
    if(m_repositoryPath.isEmpty())
        emit errorEmptyRepositoryPath();
    else if(m_imageDelay < 1)
        emit errorEmptyImageDelay();
    else if(m_imageCount < 1)
        emit errorEmptyImageCount();
    else
        return true;

    return false;
}

void HomeWindowBackend::openSessionWindow() {

    QStringList images;

    try {
        images = FilesGrabber::getAllImagesAtFolder(m_repositoryPath);
    } catch (const fs::filesystem_error& e) {
        switch (static_cast<std::errc>(e.code().value())) {
        case std::errc::no_such_file_or_directory:
            emit errorInvalidRepositoryPath();
            break;
        default:
            std::cerr << "code: " << e.code() << " | " << "what: " << e.what() << std::endl;
            throw std::invalid_argument("Error not handler");
        }

        return;
    }

    ApplicationBackend* applicationBackend = ApplicationBackend::getInstance();
    QQmlApplicationEngine* engine = applicationBackend->getEngine();
    QQmlComponent component(applicationBackend->getEngine(), QUrl("qrc:/qt/qml/flashdraws/source/frontend/components/flashDrawSessionWrapper/FlashDrawSessionWrapper.qml"));

    QQuickItem* visualParent = qobject_cast<QQuickItem*>(parent());

    QObject* object = component.beginCreate(engine->rootContext());
    if (object) {
        QObject::connect(object, SIGNAL(sessionFinished()), this, SLOT(emitSessionFinished()));
        engine->setObjectOwnership(object, QQmlEngine::JavaScriptOwnership);

        QQuickItem *item = qobject_cast<QQuickItem*>(object);

        item->setParent(this);
        item->setParentItem(visualParent);

        item->setProperty("images", images);
        item->setProperty("delayImages", m_imageDelay);
        item->setProperty("imagesCount", m_imageCount);
        item->setProperty("sessionMode", m_sessionMode);

        component.completeCreate();
        emit sessionStarted();
    } else {
        qDebug() << component.errorString();
    }
}

void HomeWindowBackend::emitSessionFinished() {
    emit sessionFinished();
}

QString HomeWindowBackend::getRepositoryPath() const {
    return m_repositoryPath;
}

int HomeWindowBackend::getImageCount() const {
    return m_imageCount;
}

int HomeWindowBackend::getImageDelay() const {
    return m_imageDelay;
}

SessionModes::Enum HomeWindowBackend::getSessionMode() const {
    return m_sessionMode;
}

void HomeWindowBackend::setRepositoryPath(QString repositoryPath) {
    m_repositoryPath = repositoryPath;
}

void HomeWindowBackend::setImageCount(int imageCount) {
    m_imageCount = imageCount;
}

void HomeWindowBackend::setImageDelay(int imageDelay) {
    m_imageDelay = imageDelay;
}

void HomeWindowBackend::setSessionMode(SessionModes::Enum sessionMode) {
    m_sessionMode = sessionMode;
    sessionModeChanged();
}