#include "timer.h"

Timer::Timer(QObject *parent, int timeElapsedDelay) : QObject{parent}, timeElapsedDelay(timeElapsedDelay) {
    connect(&qTimer, &QTimer::timeout, this, &Timer::intervalTimeout);
    connect(&qTimerElapsed, &QTimer::timeout, this, &Timer::emitTimeElapsed);

    qTimerElapsed.setInterval(timeElapsedDelay);
}

void Timer::emitTimeElapsed() {
    emit timeElapsed();
}

void Timer::play() {
    qTimerElapsed.start();
    qTimer.start();
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
        emit finishAllIntervals();
    } else {
        emit finishInterval();
    }
}

void Timer::startRhythmIntervals(const int& delay, const int& count) {
    stop();

    currentInterval = 0;
    intervalCount = count;

    qTimer.setInterval(delay);

    play();
}

const int Timer::getRemainingTime() {
    return qTimer.remainingTime() - timeElapsedDelay;
}