#include "homeWindowBackend.h"
#include <iostream>
#include <qqmlcomponent.h>
#include <QQuickItem>
#include "../applicationBackend/applicationBackend.hpp"
#include "../utils/filesGrabber/filesGrabber.h"

HomeWindowBackend::HomeWindowBackend(QObject *parent) : QObject{parent} {}

void HomeWindowBackend::startSession() {
    if(!propertysValueAreValids())
        return;

    std::cout << m_repositoryPath.toStdString() << std::endl;
    std::cout << m_imageDelay << std::endl;
    std::cout << m_imageCount << std::endl;
    openSessionWindow();
}

bool HomeWindowBackend::propertysValueAreValids() {
    std::cout << m_repositoryPath.toStdString() << std::endl;
    std::cout << m_repositoryPath.isEmpty() << std::endl;
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

    ApplicationBackend* applicationBackend = ApplicationBackend::getInstance();
    QQmlApplicationEngine* engine = applicationBackend->getEngine();
    QQmlComponent component(applicationBackend->getEngine(), QUrl("qrc:/qt/qml/flashdraws/source/frontend/components/flashDrawSessionWrapper/FlashDrawSessionWrapper.qml"));

    QQuickItem* visualParent = qobject_cast<QQuickItem*>(parent());

    QObject* object = component.beginCreate(engine->rootContext());
    if (object) {
        QObject::connect(object, SIGNAL(sessionFinished()), this, SLOT(emitSessionFinished()));
        engine->setObjectOwnership(object, QQmlEngine::JavaScriptOwnership);

        QQuickItem *item = qobject_cast<QQuickItem*>(object);
        QStringList images = FilesGrabber::getAllImagesAtFolder(m_repositoryPath);

        item->setParent(this);
        item->setParentItem(visualParent);

        item->setProperty("images", QVariant::fromValue(images));
        item->setProperty("delayImages", QVariant::fromValue(m_imageDelay));
        item->setProperty("imagesCount", QVariant::fromValue(m_imageCount));

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

void HomeWindowBackend::setRepositoryPath(QString repositoryPath) {
    m_repositoryPath = repositoryPath;
}

void HomeWindowBackend::setImageCount(int imageCount) {
    m_imageCount = imageCount;
}

void HomeWindowBackend::setImageDelay(int imageDelay) {
    m_imageDelay = imageDelay;
}