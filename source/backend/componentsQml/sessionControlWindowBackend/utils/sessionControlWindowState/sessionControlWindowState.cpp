#include "sessionControlWindowState.h"

#include "../../sessionControlWindowBackend.h"
#include <iostream>

SessionControlWindowState::SessionControlWindowState() {}

bool SessionControlWindowState::isSessionFinished(const int& currentImageIndex, const int& countImage) {
    return currentImageIndex > countImage;
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
