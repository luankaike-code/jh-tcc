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
    Q_PROPERTY(bool hasRoadmap READ getHasRoadmap WRITE setHasRoadmap NOTIFY hasRoadmapChanged)
    Q_PROPERTY(bool timerIsRunnig READ getTimerIsRunnig NOTIFY timerIsRunnigChanged)
    Q_PROPERTY(bool isRestPause READ getIsRestPause WRITE setIsRestPause NOTIFY isRestPauseChanged)
    Q_PROPERTY(bool isStarted READ getIsStarted WRITE setIsStarted NOTIFY isStartedChanged)

    Q_PROPERTY(int delayImage READ getDelayImage WRITE setDelayImage NOTIFY delayImageChanged REQUIRED)
    Q_PROPERTY(int imageCount READ getImageCount WRITE setImageCount NOTIFY imageCountChanged REQUIRED)
    Q_PROPERTY(int roadmapDuration READ getRoadmapDuration WRITE setRoadmapDuration NOTIFY roadmapDurationChanged REQUIRED)
    Q_PROPERTY(int currentImageIndex READ getCurrentImageIndex WRITE setCurrentImageIndex NOTIFY currentImageIndexChanged)
    Q_PROPERTY(int remainingTime READ getRemainingTime NOTIFY remainingTimeChanged)

    Timer timer;
    SessionControlWindowState* currentState;
    SessionModes::Enum m_sessionModes;
    bool m_hasTimerLimit;
    bool m_hasImagesLimit;
    bool m_hasRoadmap;
    bool m_isRestPause;
    bool m_isStarted;
    int m_imageDelay;
    int m_imageCount;
    int m_roadmapDuration;
    int m_currentImageIndex;

public:
    explicit SessionControlWindowBackend(QObject *parent = nullptr);
    ~SessionControlWindowBackend();

    Q_INVOKABLE void nextButtonPressed();
    Q_INVOKABLE void preventButtonPressed();
    Q_INVOKABLE void pauseTimer();
    Q_INVOKABLE void playTimer();
    Q_INVOKABLE void resetTimer();
    Q_INVOKABLE void startSession();

    void startTimer();
    void updateTimerIsRunnigValue();

    SessionModes::Enum getSessionModes() const;
    const bool& getHasTimerLimit() const;
    const bool& getHasImagesLimit() const;
    const bool& getHasRoadmap() const;
    const bool getTimerIsRunnig();
    const int& getDelayImage() const;
    const int& getImageCount() const;
    const int& getCurrentImageIndex() const;
    const int& getRemainingTime();
    const int& getRoadmapDuration() const;
    const bool& getIsRestPause() const;
    const bool& getIsStarted() const;

    void setIsRestPause(const bool& isRestPause);
    void setDelayImage(const int& delayImage);
    void setSessionModes(SessionModes::Enum sessionModes);
    void setHasTimerLimit(const bool& hasTimerLimit);
    void setHasImagesLimit(const bool& hasImagesLimit);
    void setHasRoadmap(const bool& hasRoadmap);
    void setImageCount(const int& ImageCount);
    void setCurrentImageIndex(const int& currentImageIndex);
    void setRoadmapDuration(const int& roadmapDuration);
    void setIsStarted(const bool& isStarted);

signals:
    void goToNextImage();
    void goToPreventImage();

    void sessionFinish();

    void isRestPauseChanged();
    void sessionModesChanged();
    void hasTimerLimitChanged();
    void hasRoadmapChanged();
    void isStartedChanged();
    void hasImagesLimitChanged();
    void imageCountChanged();
    void currentImageIndexChanged();
    void remainingTimeChanged();
    void roadmapDurationChanged();
    void delayImageChanged();
    void timerIsRunnigChanged();
};

#endif // SESSIONCONTROLWINDOWBACKEND_H
