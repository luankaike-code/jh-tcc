#include "SCWSSandbox.h"

#include "../../sessionControlWindowBackend.h"
#include <iostream>

SCWSSandbox::SCWSSandbox(SessionControlWindowBackend* sessionControlWindowBackend) : SessionControlWindowState(sessionControlWindowBackend) {}

void SCWSSandbox::pressNextButton(SessionControlWindowBackend* sessionControlWindowBackend) {
    sessionControlWindowBackend->setCurrentImageIndex(sessionControlWindowBackend->getCurrentImageIndex()+1);
    sessionControlWindowBackend->goToNextImage();
}

void SCWSSandbox::pressPreventButton(SessionControlWindowBackend* sessionControlWindowBackend) {
    sessionControlWindowBackend->setCurrentImageIndex(sessionControlWindowBackend->getCurrentImageIndex()-1);
    sessionControlWindowBackend->goToPreventImage();
}

const bool SCWSSandbox::isSessionFinished(SessionControlWindowBackend* sessionControlWindowBackend) const {
    return false;
}

void SCWSSandbox::intervalTimerFinish(SessionControlWindowBackend* sessionControlWindowBackend) {
    std::cerr << "Timer is not be activated" << std::endl;
}