#include "sessionControlWindowState.h"

#include "../../sessionControlWindowBackend.h"
#include <iostream>

SessionControlWindowState::SessionControlWindowState(SessionControlWindowBackend* sessionControlWindowBackend) : QObject{sessionControlWindowBackend} {
    connect(sessionControlWindowBackend, &SessionControlWindowBackend::delayImageChanged, this, [this, sessionControlWindowBackend](){
        this->delayImageChanged(sessionControlWindowBackend);
    });

    connect(sessionControlWindowBackend, &SessionControlWindowBackend::roadmapDurationChanged, this, [this, sessionControlWindowBackend](){
        this->roadmapDurationChanged(sessionControlWindowBackend);
    });
}

const bool SessionControlWindowState::isSessionFinished(SessionControlWindowBackend* sessionControlWindowBackend) const {
    return sessionControlWindowBackend->getCurrentImageIndex() > sessionControlWindowBackend->getImagesCount();
}

void SessionControlWindowState::startSession(SessionControlWindowBackend* sessionControlWindowBackend) {}

void SessionControlWindowState::delayImageChanged(SessionControlWindowBackend* sessionControlWindowBackend) {}

void SessionControlWindowState::roadmapDurationChanged(SessionControlWindowBackend* sessionControlWindowBackend) {}

void SessionControlWindowState::nextButtonPressed(SessionControlWindowBackend* sessionControlWindowBackend) {
    sessionControlWindowBackend->resetTimer();
    sessionControlWindowBackend->goToNextImage();
}

void SessionControlWindowState::preventButtonPressed(SessionControlWindowBackend* sessionControlWindowBackend) {
    sessionControlWindowBackend->resetTimer();
    sessionControlWindowBackend->goToPreventImage();
}

void SessionControlWindowState::intervalTimerFinish(SessionControlWindowBackend* sessionControlWindowBackend) {
    sessionControlWindowBackend->setCurrentImageIndex(sessionControlWindowBackend->getCurrentImageIndex()+1);

    if(isSessionFinished(sessionControlWindowBackend))
        sessionControlWindowBackend->sessionFinish();

    sessionControlWindowBackend->goToNextImage();
}
