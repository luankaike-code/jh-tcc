#include "SCWMInfinityTime.h"
#include "../sessionControlWindowBackend/sessionControlWindowBackend.h"
#include <iostream>

SCWMInfinityTime::SCWMInfinityTime(SessionControlWindowBackend* sessionControlWindowBackend) : SessionControlWindowMode(sessionControlWindowBackend) {}

void SCWMInfinityTime::pressNextButton(SessionControlWindowBackend* sessionControlWindowBackend) {
    sessionControlWindowBackend->setCurrentImageIndex(sessionControlWindowBackend->getCurrentImageIndex()+1);
    sessionControlWindowBackend->goToNextImage();

    if(isSessionFinished(sessionControlWindowBackend))
        sessionControlWindowBackend->sessionFinished();
}

void SCWMInfinityTime::pressPreventButton(SessionControlWindowBackend* sessionControlWindowBackend) {
    sessionControlWindowBackend->setCurrentImageIndex(sessionControlWindowBackend->getCurrentImageIndex()-1);
    sessionControlWindowBackend->goToPreventImage();
}

void SCWMInfinityTime::intervalTimerFinish(SessionControlWindowBackend* sessionControlWindowBackend) {
    std::cerr << "Timer is not be activated" << std::endl;
}