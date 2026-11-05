// SPDX-FileCopyrightText: 2026 luankaike-code <https://github.com/luankaike-code>
//
// SPDX-License-Identifier: GPL-3.0-or-later

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