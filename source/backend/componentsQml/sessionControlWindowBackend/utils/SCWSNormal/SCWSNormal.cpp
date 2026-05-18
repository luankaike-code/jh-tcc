#include "SCWSNormal.h"

#include "../../sessionControlWindowBackend.h"

SCWSNormal::SCWSNormal(SessionControlWindowBackend* sessionControlWindowBackend) : SessionControlWindowState(sessionControlWindowBackend) {
    makeConnectionToAutoUpdateTimer(sessionControlWindowBackend);
}
