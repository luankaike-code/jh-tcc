// SPDX-FileCopyrightText: 2026 luankaike-code <https://github.com/luankaike-code>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "sessionControlWindowMode.h"

#include "../../sessionControlWindowBackend.h"

SessionControlWindowMode::SessionControlWindowMode(SessionControlWindowBackend* sessionControlWindowBackend) : QObject{sessionControlWindowBackend} {}

const bool SessionControlWindowMode::isSessionFinished(SessionControlWindowBackend* sessionControlWindowBackend) const {
    return sessionControlWindowBackend->getCurrentImageIndex() > sessionControlWindowBackend->getImageCount();
}

void SessionControlWindowMode::startSession(SessionControlWindowBackend* sessionControlWindowBackend) {}

void SessionControlWindowMode::pressNextButton(SessionControlWindowBackend* sessionControlWindowBackend) {
    sessionControlWindowBackend->resetTimer();
    sessionControlWindowBackend->goToNextImage();
}

void SessionControlWindowMode::pressPreventButton(SessionControlWindowBackend* sessionControlWindowBackend) {
    sessionControlWindowBackend->resetTimer();
    sessionControlWindowBackend->goToPreventImage();
}

void SessionControlWindowMode::intervalTimerFinish(SessionControlWindowBackend* sessionControlWindowBackend) {
    sessionControlWindowBackend->setCurrentImageIndex(sessionControlWindowBackend->getCurrentImageIndex()+1);

    if(isSessionFinished(sessionControlWindowBackend))
        sessionControlWindowBackend->sessionFinished();

    sessionControlWindowBackend->goToNextImage();
}
