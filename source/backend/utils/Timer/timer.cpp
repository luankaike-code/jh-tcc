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
    currentInterval++;
    bool is_finished_all_intervals = (currentInterval > intervalCount);

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

    currentInterval = 1;
    intervalCount = count;
    intervalDelay = delay;

    qTimer.setInterval(intervalDelay);

    play(true);
}

const int Timer::getRemainingTime() {
    return m_remainingTime;
}