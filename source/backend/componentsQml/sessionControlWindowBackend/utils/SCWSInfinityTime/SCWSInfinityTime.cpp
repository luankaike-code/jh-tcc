#include "SCWSInfinityTime.h"
#include "../sessionControlWindowBackend/sessionControlWindowBackend.h"
#include <iostream>

SCWSInfinityTime::SCWSInfinityTime(SessionControlWindowBackend* sessionControlWindowBackend) : SessionControlWindowState(sessionControlWindowBackend) {}

void SCWSInfinityTime::nextButtonPressed(SessionControlWindowBackend* sessionControlWindowBackend) {
    sessionControlWindowBackend->setCurrentImageIndex(sessionControlWindowBackend->getCurrentImageIndex()+1);
    sessionControlWindowBackend->goToNextImage();

    if(isSessionFinished(sessionControlWindowBackend))
        sessionControlWindowBackend->sessionFinish();
}

void SCWSInfinityTime::pressPreventButton(SessionControlWindowBackend* sessionControlWindowBackend) {
    sessionControlWindowBackend->setCurrentImageIndex(sessionControlWindowBackend->getCurrentImageIndex()-1);
    sessionControlWindowBackend->goToPreventImage();
}

void SCWSInfinityTime::intervalTimerFinish(SessionControlWindowBackend* sessionControlWindowBackend) {
    std::cerr << "Timer is not be activated" << std::endl;
}