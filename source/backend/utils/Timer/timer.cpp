#include "timer.h"
#include <iostream>

Timer::Timer(QObject *parent) : QObject{parent} {}

void Timer::intervalTimeout() {
    currentInterval++;
    bool is_finished_all_intervals = (currentInterval >= intervalCount);

    std::cout << "interval: " << is_finished_all_intervals << std::endl;

    if(is_finished_all_intervals)
        qTimer.stop();
}

void Timer::startRhythmIntervals(const int& delay, const int& count) {
    qTimer.stop();
    qTimer.disconnect(this);

    currentInterval = 0;
    intervalCount = count;

    qTimer.setInterval(delay);
    connect(&qTimer, &QTimer::timeout, this, &Timer::intervalTimeout);
    qTimer.start();
}