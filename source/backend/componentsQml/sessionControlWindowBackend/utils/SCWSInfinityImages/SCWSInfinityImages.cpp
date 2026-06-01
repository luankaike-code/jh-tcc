#include "SCWSInfinityImages.h"

#include "../../sessionControlWindowBackend.h"

SCWSInfinityImages::SCWSInfinityImages(SessionControlWindowBackend* sessionControlWindowBackend) : SessionControlWindowState(sessionControlWindowBackend) {}

const bool SCWSInfinityImages::isSessionFinished(SessionControlWindowBackend* sessionControlWindowBackend) const {
    return false;
}

void SCWSInfinityImages::startSession(SessionControlWindowBackend* sessionControlWindowBackend) {
    sessionControlWindowBackend->startTimer();
};