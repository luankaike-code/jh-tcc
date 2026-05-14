#ifndef SESSIONCONTROLWINDOWBACKEND_H
#define SESSIONCONTROLWINDOWBACKEND_H

#include <QObject>
#include <QQmlEngine>
#include "../../enums/sessionModes.h"
#include "../timer/timer.h"
#include "utils/sessionControlWindowState/sessionControlWindowState.h"

class SessionControlWindowBackend : public QObject {
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(SessionModes::Enum sessionModes READ getSessionModes WRITE setSessionModes NOTIFY sessionModesChanged REQUIRED)
    Q_PROPERTY(bool hasTimerLimit READ getHasTimerLimit WRITE setHasTimerLimit NOTIFY hasTimerLimitChanged)
    Q_PROPERTY(bool hasImagesLimit READ getHasImagesLimit WRITE setHasImagesLimit NOTIFY hasImagesLimitChanged)
    Q_PROPERTY(bool timerIsRunnig READ getTimerIsRunnig NOTIFY timerIsRunnigChanged)

    Q_PROPERTY(int delayImage READ getDelayImage WRITE setDelayImage NOTIFY delayImageChanged REQUIRED)
    Q_PROPERTY(int imagesCount READ getImagesCount WRITE setImagesCount NOTIFY imagesCountChanged REQUIRED)
    Q_PROPERTY(int currentImageIndex READ getCurrentImageIndex WRITE setCurrentImageIndex NOTIFY currentImageIndexChanged)
    Q_PROPERTY(int remainingTime READ getRemainingTime NOTIFY remainingTimeChanged)

    Timer timer;
    SessionControlWindowState* currentState;
    SessionModes::Enum m_sessionModes;
    bool m_hasTimerLimit;
    bool m_hasImagesLimit;
    int m_imagesDelay;
    int m_imagesCount;
    int m_currentImageIndex;

public:
    explicit SessionControlWindowBackend(QObject *parent = nullptr);
    ~SessionControlWindowBackend();

    Q_INVOKABLE void nextButtonPressed();
    Q_INVOKABLE void preventButtonPressed();
    Q_INVOKABLE void pauseTimer();
    Q_INVOKABLE void playTimer();
    Q_INVOKABLE void resetTimer();

    void startTimer();
    void updateTimerIsRunnigValue();

    SessionModes::Enum getSessionModes() const;
    bool getHasTimerLimit() const;
    bool getHasImagesLimit() const;
    const bool getTimerIsRunnig();
    int getDelayImage() const;
    int getImagesCount() const;
    int getCurrentImageIndex() const;
    int getRemainingTime();

    void setDelayImage(int delayImage);
    void setSessionModes(SessionModes::Enum sessionModes);
    void setHasTimerLimit(bool hasTimerLimit);
    void setHasImagesLimit(bool hasImagesLimit);
    void setImagesCount(int ImagesCount);
    void setCurrentImageIndex(int currentImageIndex);

signals:
    void goToNextImage();
    void goToPreventImage();

    void sessionFinish();

    void sessionModesChanged();
    void hasTimerLimitChanged();
    void hasImagesLimitChanged();
    void imagesCountChanged();
    void currentImageIndexChanged();
    void remainingTimeChanged();
    void delayImageChanged();
    void timerIsRunnigChanged();
};

#endif // SESSIONCONTROLWINDOWBACKEND_H
