#include "SCWSSandbox.h"

#include "../../sessionControlWindowBackend.h"
#include <iostream>

SCWSSandbox::SCWSSandbox() {}

void SCWSSandbox::nextButtonPressed(SessionControlWindowBackend* sessionControlWindowBackend) {
    sessionControlWindowBackend->setCurrentImageIndex(sessionControlWindowBackend->getCurrentImageIndex()+1);
    sessionControlWindowBackend->goToNextImage();
}

void SCWSSandbox::preventButtonPressed(SessionControlWindowBackend* sessionControlWindowBackend) {
    sessionControlWindowBackend->setCurrentImageIndex(sessionControlWindowBackend->getCurrentImageIndex()-1);
    sessionControlWindowBackend->goToPreventImage();
}

bool SCWSSandbox::isSessionFinished(const int& currentImageIndex, const int& countImage) {
    return false;
}

void SCWSSandbox::intervalTimerFinish(SessionControlWindowBackend* sessionControlWindowBackend) {
    std::cerr << "Timer is not be activated" << std::endl;
}
