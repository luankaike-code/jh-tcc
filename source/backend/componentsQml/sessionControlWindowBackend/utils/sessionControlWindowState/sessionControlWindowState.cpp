#include "sessionControlWindowState.h"

#include "../../sessionControlWindowBackend.h"
#include <iostream>

SessionControlWindowState::SessionControlWindowState(SessionControlWindowBackend* sessionControlWindowBackend) : QObject{sessionControlWindowBackend} {}

bool SessionControlWindowState::isSessionFinished(const int& currentImageIndex, const int& countImage) {
    return currentImageIndex > countImage;
}

void SessionControlWindowState::timerUpdated(SessionControlWindowBackend* sessionControlWindowBackend) {}

void SessionControlWindowState::makeConnectionToAutoUpdateTimer(SessionControlWindowBackend* sessionControlWindowBackend) {
    connect(sessionControlWindowBackend, &SessionControlWindowBackend::delayImageChanged, this, [this, sessionControlWindowBackend](){
        sessionControlWindowBackend->startTimer();
        this->timerUpdated(sessionControlWindowBackend);
    });
}

void SessionControlWindowState::nextButtonPressed(SessionControlWindowBackend* sessionControlWindowBackend) {
    std::cout << "teste" << std::endl;
    sessionControlWindowBackend->resetTimer();
    sessionControlWindowBackend->goToNextImage();
}

void SessionControlWindowState::preventButtonPressed(SessionControlWindowBackend* sessionControlWindowBackend) {
    sessionControlWindowBackend->resetTimer();
    sessionControlWindowBackend->goToPreventImage();
}

void SessionControlWindowState::intervalTimerFinish(SessionControlWindowBackend* sessionControlWindowBackend) {
    if(isSessionFinished(sessionControlWindowBackend->getCurrentImageIndex(), sessionControlWindowBackend->getImagesCount()))
        sessionControlWindowBackend->sessionFinish();
    sessionControlWindowBackend->setCurrentImageIndex(sessionControlWindowBackend->getCurrentImageIndex()+1);
    sessionControlWindowBackend->goToNextImage();
}
