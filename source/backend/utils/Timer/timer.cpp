#include "timer.h"
#include <iostream>

Timer::Timer(QObject *parent) : QObject{parent} {}

void Timer::hello_world() {
    std::cout << "hello world" << std::endl;
}