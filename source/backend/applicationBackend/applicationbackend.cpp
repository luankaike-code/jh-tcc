#include "applicationBackend.hpp"

ApplicationBackend* ApplicationBackend::instance = nullptr;

ApplicationBackend::ApplicationBackend() { }

ApplicationBackend* ApplicationBackend::getInstance() {
    if(instance == nullptr) {
        instance = new ApplicationBackend();
    }
    return instance;
}

QQmlApplicationEngine* ApplicationBackend::getEngine() {
    return &engine;
}