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
}

void Timer::stop() {
    qTimer.stop();
    qTimerElapsed.stop();
}

void Timer::intervalTimeout() {
    setCurrentInterval(m_currentInterval+1);

    bool is_finished_all_intervals = (m_currentInterval > m_intervalCount);

    if(is_finished_all_intervals){
        stop();
        emitTimeElapsed(0);
        emit finishAllIntervals();
        return;
    }

    if(qTimer.interval() != intervalDelay)
        qTimer.start(intervalDelay);

    emitTimeElapsed();
    emit finishInterval();
}

void Timer::startRhythmIntervals(const int& delay, const int& count) {
    stop();

    setCurrentInterval(1);
    setIntervalCount(count);
    intervalDelay = delay;

    qTimer.setInterval(intervalDelay);

    play(true);
}

void Timer::setIntervalCount(int value) {
    m_intervalCount = value;
    emit intervalCountChanged();
}

void Timer::setCurrentInterval(int value) {
    m_currentInterval = value;
    emit currentIntervalChanged();
}


const int Timer::getIntervalCount() {
    return m_intervalCount;
}

const int Timer::getCurrentInterval() {
    return m_currentInterval;
}

const int Timer::getRemainingTime() {
    return m_remainingTime;
}