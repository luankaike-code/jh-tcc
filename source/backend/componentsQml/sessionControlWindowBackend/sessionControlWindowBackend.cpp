#include "sessionControlWindowBackend.h"
#include "../../helpers/sessionModeReader/sessionModeReader.h"

#include "utils/SCWSInfinityImages/SCWSInfinityImages.h"
#include "utils/SCWSInfinityTime/SCWSInfinityTime.h"
#include "utils/SCWSNormal/SCWSNormal.h"
#include "utils/SCWSSandbox/SCWSSandbox.h"
#include "utils/SCWSClassroom/SCWSClassroom.h"
#include <iostream>

SessionControlWindowBackend::SessionControlWindowBackend(QObject *parent) :
    QObject{parent},
    currentState(nullptr), timer(this),
    m_currentImageIndex(0), m_imageCount(0), m_imagesDelay(0), m_roadmapDuration(0),
    m_isStarted(false), m_hasRoadmap(false), m_hasTimerLimit(false), m_hasImagesLimit(false)
{
    setCurrentImageIndex(1);

    connect(&timer, &Timer::timeElapsed, this, [this](){
        remainingTimeChanged();
    });
    connect(&timer, &Timer::isRunningChanged, this, [this](){
        timerIsRunnigChanged();
    });
    connect(&timer, &Timer::finishInterval, this, [this](){
        if(!currentState) {
            std::cerr << "currentState isnt defined" << std::endl;
            return;
        }

        currentState->intervalTimerFinish(this);
    });
}

SessionControlWindowBackend::~SessionControlWindowBackend() {
    delete currentState;
}

void SessionControlWindowBackend::SessionControlWindowBackend::nextButtonPressed() {
    if(!currentState) {
        std::cerr << "currentState isnt defined" << std::endl;
        return;
    }
    currentState->nextButtonPressed(this);
}

void SessionControlWindowBackend::preventButtonPressed() {
    if(!currentState) {
        std::cerr << "currentState isnt defined" << std::endl;
        return;
    }
    currentState->preventButtonPressed(this);
}

void SessionControlWindowBackend::startSession() {
    if(!currentState) {
        std::cerr << "currentState isnt defined" << std::endl;
        return;
    }
    currentState->startSession(this);
    setIsStarted(true);
}

void SessionControlWindowBackend::pauseTimer() {
    if(m_hasTimerLimit)
        timer.stop();
    else
        std::cerr << "SessionControlWindowBackend::pauseTimer: It session not should manipulate timer" << std::endl;
}

void SessionControlWindowBackend::playTimer() {
    if(m_hasTimerLimit)
        timer.play();
    else
        std::cerr << "SessionControlWindowBackend::playTimer: It session not should manipulate timer" << std::endl;
}

void SessionControlWindowBackend::resetTimer() {
    if(m_hasTimerLimit)
        timer.play(true);
    else
        std::cerr << "SessionControlWindowBackend::resetTimer: It session not should manipulate timer" << std::endl;
}

SessionModes::Enum SessionControlWindowBackend::getSessionModes() const {
    return m_sessionModes;
}

void SessionControlWindowBackend::startTimer() {
    if(m_imagesDelay > 0)
        timer.startInfinityIntervals(m_imagesDelay);
}

const bool& SessionControlWindowBackend::getHasTimerLimit() const {
    return m_hasTimerLimit;
}

const bool& SessionControlWindowBackend::getHasImagesLimit() const {
    return m_hasImagesLimit;
}

const bool& SessionControlWindowBackend::getHasRoadmap() const {
    return m_hasRoadmap;
}

const bool SessionControlWindowBackend::getTimerIsRunnig() {
    return timer.getIsRunning();
}

const int& SessionControlWindowBackend::getRemainingTime() {
    return timer.getRemainingTime();
}

const int& SessionControlWindowBackend::getDelayImage() const {
    return m_imagesDelay;
}

const int& SessionControlWindowBackend::getImageCount() const {
    return m_imageCount;
}

const int& SessionControlWindowBackend::getCurrentImageIndex() const {
    return m_currentImageIndex;
}

const int& SessionControlWindowBackend::getRoadmapDuration() const {
    return m_roadmapDuration;
}

const bool& SessionControlWindowBackend::getIsRestPause() const {
    return m_isRestPause;
}

const bool& SessionControlWindowBackend::getIsStarted() const {
    return m_isStarted;
}

void SessionControlWindowBackend::setIsRestPause(const bool& isRestPause) {
    m_isRestPause = isRestPause;
    isRestPauseChanged();
}

void SessionControlWindowBackend::setDelayImage(const int& delayImage) {
    if(m_imagesDelay == delayImage)
        return;

    m_imagesDelay = delayImage;
    delayImageChanged();
}

void SessionControlWindowBackend::setSessionModes(SessionModes::Enum sessionModes) {
    setHasTimerLimit(SessionModeReader::hasTimerLimit(sessionModes));
    setHasImagesLimit(SessionModeReader::hasImagesLimit(sessionModes));
    setHasRoadmap(SessionModeReader::hasRoadmap(sessionModes));

    delete currentState;
    currentState = nullptr;
    switch (sessionModes) {
        case SessionModes::Enum::Classroom:
            currentState = new SCWSClassroom(this);
            break;
        case SessionModes::Enum::InfinityImages:
            currentState = new SCWSInfinityImages(this);
            break;
        case SessionModes::Enum::Normal:
            currentState = new SCWSNormal(this);
            break;
        case SessionModes::Enum::InfinityTime:
            currentState = new SCWSInfinityTime(this);
            break;
        case SessionModes::Enum::Sandbox:
            currentState = new SCWSSandbox(this);
            break;
        default:
            std::cerr << sessionModes << " isnt a valid SessionModes::Enum" << std::endl;
            break;
    }

    m_sessionModes = sessionModes;
    sessionModesChanged();
}

void SessionControlWindowBackend::setHasTimerLimit(const bool& hasTimerLimit) {
    m_hasTimerLimit = hasTimerLimit;
    hasTimerLimitChanged();
}

void SessionControlWindowBackend::setRoadmapDuration(const int& roadmapDuration) {
    m_roadmapDuration = roadmapDuration;
    roadmapDurationChanged();
}

void SessionControlWindowBackend::setIsStarted(const bool& isStarted) {
    m_isStarted = isStarted;
    emit isStartedChanged();
}

void SessionControlWindowBackend::setHasImagesLimit(const bool& hasImagesLimit) {
    m_hasImagesLimit = hasImagesLimit;
    hasImagesLimitChanged();
}

void SessionControlWindowBackend::setHasRoadmap(const bool& hasRoadmap) {
    m_hasRoadmap = hasRoadmap;
    hasRoadmapChanged();
}

void SessionControlWindowBackend::setImageCount(const int& imageCount) {
    if(m_imageCount == imageCount)
        return;

    m_imageCount = imageCount;
    imageCountChanged();
}

void SessionControlWindowBackend::setCurrentImageIndex(const int& currentImageIndex) {
    m_currentImageIndex = currentImageIndex;
    currentImageIndexChanged();
}
