#include "SCWMSandbox.h"

#include "../../sessionControlWindowBackend.h"
#include <iostream>

SCWMSandbox::SCWMSandbox(SessionControlWindowBackend* sessionControlWindowBackend) : SessionControlWindowMode(sessionControlWindowBackend) {}

void SCWMSandbox::pressNextButton(SessionControlWindowBackend* sessionControlWindowBackend) {
    sessionControlWindowBackend->setCurrentImageIndex(sessionControlWindowBackend->getCurrentImageIndex()+1);
    sessionControlWindowBackend->goToNextImage();
}

void SCWMSandbox::pressPreventButton(SessionControlWindowBackend* sessionControlWindowBackend) {
    sessionControlWindowBackend->setCurrentImageIndex(sessionControlWindowBackend->getCurrentImageIndex()-1);
    sessionControlWindowBackend->goToPreventImage();
}

const bool SCWMSandbox::isSessionFinished(SessionControlWindowBackend* sessionControlWindowBackend) const {
    return false;
}

void SCWMSandbox::intervalTimerFinish(SessionControlWindowBackend* sessionControlWindowBackend) {
    std::cerr << "Timer is not be activated" << std::endl;
}