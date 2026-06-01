#include "SCWSNormal.h"

#include "../../sessionControlWindowBackend.h"

SCWSNormal::SCWSNormal(SessionControlWindowBackend* sessionControlWindowBackend) : SessionControlWindowState(sessionControlWindowBackend) {}

void SCWSNormal::startSession(SessionControlWindowBackend* sessionControlWindowBackend) {
    sessionControlWindowBackend->startTimer();
};