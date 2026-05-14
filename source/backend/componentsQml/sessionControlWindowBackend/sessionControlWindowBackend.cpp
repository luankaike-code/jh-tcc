#include "sessionControlWindowBackend.h"
#include "../../helpers/sessionModeReader.h"

#include "utils/SCWSInfinityImages/SCWSInfinityImages.h"
#include "utils/SCWSInfinityTime/SCWSInfinityTime.h"
#include "utils/SCWSNormal/SCWSNormal.h"
#include "utils/SCWSSandbox/SCWSSandbox.h"
#include <iostream>

SessionControlWindowBackend::SessionControlWindowBackend(QObject *parent) :
    QObject{parent}, currentState(nullptr), timer(this), m_currentImageIndex(0), m_imagesCount(0), m_imagesDelay(0)
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

void SessionControlWindowBackend::pauseTimer() {
    if(m_hasTimerLimit)
        timer.stop();
}

void SessionControlWindowBackend::playTimer() {
    if(m_hasTimerLimit)
        timer.play();
}

void SessionControlWindowBackend::resetTimer() {
    if(m_hasTimerLimit)
        timer.play(true);
}

SessionModes::Enum SessionControlWindowBackend::getSessionModes() const {
    return m_sessionModes;
}

void SessionControlWindowBackend::startTimer() {
    if(m_imagesDelay > 0 && m_imagesCount > 0)
        timer.startRhythmIntervals(m_imagesDelay, m_imagesCount-m_currentImageIndex+2);
}

bool SessionControlWindowBackend::getHasTimerLimit() const {
    return m_hasTimerLimit;
}

bool SessionControlWindowBackend::getHasImagesLimit() const {
    return m_hasImagesLimit;
}

const bool SessionControlWindowBackend::getTimerIsRunnig() {
    return timer.getIsRunning();
}

int SessionControlWindowBackend::getRemainingTime() {
    return timer.getRemainingTime();
}

int SessionControlWindowBackend::getDelayImage() const {
    return m_imagesDelay;
}

int SessionControlWindowBackend::getImagesCount() const {
    return m_imagesCount;
}

int SessionControlWindowBackend::getCurrentImageIndex() const {
    return m_currentImageIndex;
}

void SessionControlWindowBackend::setDelayImage(int delayImage) {
    m_imagesDelay = delayImage;
    delayImageChanged();
    if(m_hasTimerLimit)
        startTimer();
}

void SessionControlWindowBackend::setSessionModes(SessionModes::Enum sessionModes) {
    setHasTimerLimit(SessionModeReader::hasTimerLimit(sessionModes));
    setHasImagesLimit(SessionModeReader::hasImagesLimit(sessionModes));

    delete currentState;
    currentState = nullptr;
    switch (sessionModes) {
        case SessionModes::Enum::Classroom:
            currentState = new SCWSNormal(this);
            break;
        case SessionModes::Enum::InfinityImages:
            currentState = new SCWSInfinityImages(this);
            break;
        case SessionModes::Enum::Normal:
            currentState = new SCWSNormal(this);
            break;
        case SessionModes::Enum::InfinityTime:
            currentState = new SCWSInfinityTime();
            break;
        case SessionModes::Enum::Sandbox:
            currentState = new SCWSSandbox();
            break;
        default:
            std::cerr << sessionModes << " isnt a valid SessionModes::Enum" << std::endl;
            break;
    }

    m_sessionModes = sessionModes;
    sessionModesChanged();
}

void SessionControlWindowBackend::setHasTimerLimit(bool hasTimerLimit) {
    m_hasTimerLimit = hasTimerLimit;
    hasTimerLimitChanged();
}

void SessionControlWindowBackend::setHasImagesLimit(bool hasImagesLimit) {
    m_hasImagesLimit = hasImagesLimit;
    hasImagesLimitChanged();
}

void SessionControlWindowBackend::setImagesCount(int imagesCount) {
    m_imagesCount = imagesCount;
    imagesCountChanged();
    if(m_hasTimerLimit)
        startTimer();
}

void SessionControlWindowBackend::setCurrentImageIndex(int currentImageIndex) {
    m_currentImageIndex = currentImageIndex;
    currentImageIndexChanged();

    if(currentState && currentState->isSessionFinished(m_currentImageIndex, m_imagesCount))
        sessionFinish();
}
