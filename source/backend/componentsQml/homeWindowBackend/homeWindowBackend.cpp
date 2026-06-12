#include "homeWindowBackend.h"
#include <iostream>
#include <qqmlcomponent.h>
#include <QQuickItem>
#include <filesystem>
#include <system_error>
#include <stdexcept>
#include "../applicationBackend/applicationBackend.hpp"
#include "../utils/filesGrabber/filesGrabber.h"
#include "../../helpers/sessionModeReader/sessionModeReader.h"

namespace fs = std::filesystem;

HomeWindowBackend::HomeWindowBackend(QObject *parent) : QObject{parent} {}

void HomeWindowBackend::startSession() {
    if(!propertysValueAreValids())
        return;

    openSessionWindow();
}

bool HomeWindowBackend::propertysValueAreValids() {
    bool hasTimerLimit = SessionModeReader::hasTimerLimit(m_sessionMode);
    bool hasImagesLimit = SessionModeReader::hasImagesLimit(m_sessionMode);
    bool hasRoadmap = SessionModeReader::hasRoadmap(m_sessionMode);

    if(m_repositoryPath.isEmpty())
        emit errorEmptyRepositoryPath();
    else if(!hasRoadmap && hasTimerLimit && m_imageDelay < 1)
        emit errorEmptyImageDelay();
    else if(!hasRoadmap && hasImagesLimit && m_imageCount < 1)
        emit errorEmptyImageCount();
    else if(hasRoadmap && m_roadmapDuration < 1)
        emit errorEmptyRoadmapDuration();
    else
        return true;

    return false;
}

ResponseData<QStringList> HomeWindowBackend::tryGetAllImagesAtRepositoryPath() {
    ResponseData<QStringList> response;
    QStringList images;

    try {
        images = FilesGrabber::getAllImagesAtFolder(m_repositoryPath);
    } catch (const fs::filesystem_error& e) {
        switch (static_cast<std::errc>(e.code().value())) {
        case std::errc::no_such_file_or_directory:
            emit errorInvalidRepositoryPath();
            response.status = response.ERROR_HANDLER;
            return response;
            break;
        default:
            std::cerr << "code: " << e.code() << " | " << "what: " << e.what() << std::endl;
            throw std::invalid_argument("Error not handler");
        }
    }

    response.status = response.OK;
    response.data = images;
    return response;
}

void HomeWindowBackend::openSessionWindow() {
    ResponseData<QStringList> images = tryGetAllImagesAtRepositoryPath();

    switch (images.status) {
    case ResponseData<QStringList>::ERROR_NOT_HANDLER:
        return;
        break;
    case ResponseData<QStringList>::ERROR_HANDLER:
        std::cerr << "unexpected error from HomeWindowBackend::tryGetAllImagesAtRepositoryPath" << std::endl;
        throw std::invalid_argument("Error not handler");
        break;
    case ResponseData<QList<QString>>::OK:
        if(images.data.empty()) {
            emit errorNoneImageFound();
            return;
        }
        break;
    }

    ApplicationBackend* applicationBackend = ApplicationBackend::getInstance();
    QQmlApplicationEngine* engine = applicationBackend->getEngine();
    QQmlComponent component(applicationBackend->getEngine(), QUrl("qrc:/qt/qml/flashdraws/source/frontend/components/sessionWrapper/SessionWrapper.qml"));

    QQuickItem* visualParent = qobject_cast<QQuickItem*>(parent());

    QObject* object = component.beginCreate(engine->rootContext());
    if (object) {
        QObject::connect(object, SIGNAL(sessionFinished()), this, SLOT(emitSessionFinished()));
        engine->setObjectOwnership(object, QQmlEngine::JavaScriptOwnership);

        QQuickItem *item = qobject_cast<QQuickItem*>(object);

        item->setParent(this);
        item->setParentItem(visualParent);

        item->setProperty("images", images.data);
        item->setProperty("delayImages", m_imageDelay);
        item->setProperty("imageCount", m_imageCount);
        item->setProperty("sessionMode", m_sessionMode);
        item->setProperty("roadmapDuration", m_roadmapDuration);

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

const int& HomeWindowBackend::getImageCount() const {
    return m_imageCount;
}

const int& HomeWindowBackend::getImageDelay() const {
    return m_imageDelay;
}

SessionModes::Enum HomeWindowBackend::getSessionMode() const {
    return m_sessionMode;
}

const int& HomeWindowBackend::getRoadmapDuration() const {
    return m_roadmapDuration;
}

void HomeWindowBackend::setRoadmapDuration(const int& roadmapDuration) {
    m_roadmapDuration = roadmapDuration;
}

void HomeWindowBackend::setRepositoryPath(QString repositoryPath) {
    m_repositoryPath = repositoryPath;
}

void HomeWindowBackend::setImageCount(const int& imageCount) {
    m_imageCount = imageCount;
}

void HomeWindowBackend::setImageDelay(const int& imageDelay) {
    m_imageDelay = imageDelay;
}

void HomeWindowBackend::setSessionMode(SessionModes::Enum sessionMode) {
    m_sessionMode = sessionMode;
    sessionModeChanged();
}