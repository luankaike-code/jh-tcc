#include "timer.h"
#include <iostream>

Timer::Timer(QObject *parent, int timeElapsedDelay) : QObject{parent}, timeElapsedDelay(timeElapsedDelay) {
    connect(&qTimer, &QTimer::timeout, this, &Timer::intervalTimeout);
    connect(&qTimerElapsed, &QTimer::timeout, this, [this](){
        emitTimeElapsed();
    });

    qTimerElapsed.setInterval(timeElapsedDelay);
}

void Timer::emitTimeElapsed(int customRemainingTime) {
    m_remainingTime = customRemainingTime < 0? qTimer.remainingTime() : customRemainingTime;
    emit timeElapsed();
}

void Timer::play(bool resetTimer) {
    qTimerElapsed.start();

    qTimer.start(resetTimer? intervalDelay : m_remainingTime);
    emit isRunningChanged();
}

void Timer::stop() {
    qTimer.stop();
    qTimerElapsed.stop();
    emit isRunningChanged();
}

void Timer::intervalTimeout() {
    if(qTimer.interval() != intervalDelay)
        qTimer.start(intervalDelay);

    emitTimeElapsed();
    emit finishInterval();
}

void Timer::startInfinityIntervals(const int& delay) {
    stop();
    intervalDelay = delay;

    qTimer.setInterval(intervalDelay);

    play(true);
}

const int& Timer::getRemainingTime() {
    return m_remainingTime;
}

const bool Timer::getIsRunning() {
    return qTimer.isActive();
}