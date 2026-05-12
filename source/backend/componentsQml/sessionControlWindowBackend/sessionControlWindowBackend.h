#ifndef SESSIONCONTROLWINDOWBACKEND_H
#define SESSIONCONTROLWINDOWBACKEND_H

#include <QObject>
#include <QQmlEngine>
#include "../../enums/sessionModes.h"

class SessionControlWindowBackend : public QObject {
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(SessionModes::Enum sessionModes READ getSessionModes WRITE setSessionModes NOTIFY sessionModesChanged REQUIRED)
    Q_PROPERTY(bool hasTimerLimit READ getHasTimerLimit WRITE setHasTimerLimit NOTIFY hasTimerLimitChanged)
    Q_PROPERTY(bool hasImagesLimit READ getHasImagesLimit WRITE setHasImagesLimit NOTIFY hasImagesLimitChanged)

    Q_PROPERTY(int imagesCount READ getImagesCount WRITE setImagesCount NOTIFY imagesCountChanged REQUIRED)
    Q_PROPERTY(int currentImageIndex READ getCurrentImageIndex WRITE setCurrentImageIndex NOTIFY currentImageIndexChanged)

    SessionModes::Enum m_sessionModes;
    bool m_hasTimerLimit;
    bool m_hasImagesLimit;
    int m_imagesCount;
    int m_currentImageIndex;

public:
    explicit SessionControlWindowBackend(QObject *parent = nullptr);

    SessionModes::Enum getSessionModes() const;
    bool getHasTimerLimit() const;
    bool getHasImagesLimit() const;
    int getImagesCount() const;
    int getCurrentImageIndex() const;

    void setSessionModes(SessionModes::Enum sessionModes);
    void setHasTimerLimit(bool hasTimerLimit);
    void setHasImagesLimit(bool hasImagesLimit);
    void setImagesCount(int ImagesCount);
    void setCurrentImageIndex(int currentImageIndex);
signals:
    void sessionModesChanged();
    void hasTimerLimitChanged();
    void hasImagesLimitChanged();
    void imagesCountChanged();
    void currentImageIndexChanged();
};

#endif // SESSIONCONTROLWINDOWBACKEND_H
