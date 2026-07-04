#include "SCWMNormal.h"

#include "../../sessionControlWindowBackend.h"

SCWMNormal::SCWMNormal(SessionControlWindowBackend* sessionControlWindowBackend) : SessionControlWindowMode(sessionControlWindowBackend) {}

void SCWMNormal::startSession(SessionControlWindowBackend* sessionControlWindowBackend) {
    sessionControlWindowBackend->startTimer();
};