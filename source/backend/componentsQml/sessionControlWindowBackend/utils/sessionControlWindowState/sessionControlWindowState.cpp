#include "sessionControlWindowState.h"

#include "../../sessionControlWindowBackend.h"

SessionControlWindowState::SessionControlWindowState(SessionControlWindowBackend* sessionControlWindowBackend) : QObject{sessionControlWindowBackend} {}

const bool SessionControlWindowState::isSessionFinished(SessionControlWindowBackend* sessionControlWindowBackend) const {
    return sessionControlWindowBackend->getCurrentImageIndex() > sessionControlWindowBackend->getImageCount();
}

void SessionControlWindowState::startSession(SessionControlWindowBackend* sessionControlWindowBackend) {}

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
