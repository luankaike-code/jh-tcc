#include "SCWMInfinityImages.h"

#include "../../sessionControlWindowBackend.h"

SCWMInfinityImages::SCWMInfinityImages(SessionControlWindowBackend* sessionControlWindowBackend) : SessionControlWindowMode(sessionControlWindowBackend) {}

const bool SCWMInfinityImages::isSessionFinished(SessionControlWindowBackend* sessionControlWindowBackend) const {
    return false;
}

void SCWMInfinityImages::startSession(SessionControlWindowBackend* sessionControlWindowBackend) {
    sessionControlWindowBackend->startTimer();
};