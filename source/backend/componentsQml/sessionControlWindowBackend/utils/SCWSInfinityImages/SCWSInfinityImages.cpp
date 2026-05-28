#include "SCWSInfinityImages.h"

#include "../../sessionControlWindowBackend.h"

SCWSInfinityImages::SCWSInfinityImages(SessionControlWindowBackend* sessionControlWindowBackend) : SessionControlWindowState(sessionControlWindowBackend) {}

void SCWSInfinityImages::delayImageChanged(SessionControlWindowBackend* sessionControlWindowBackend) {
    // sessionControlWindowBackend->startTimer();
}

const bool SCWSInfinityImages::isSessionFinished(SessionControlWindowBackend* sessionControlWindowBackend) const {
    return false;
}

void SCWSInfinityImages::startSession(SessionControlWindowBackend* sessionControlWindowBackend) {
    sessionControlWindowBackend->startTimer();
};