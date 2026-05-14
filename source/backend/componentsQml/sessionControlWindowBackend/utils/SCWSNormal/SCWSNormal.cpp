#include "SCWSNormal.h"

#include "../../sessionControlWindowBackend.h"

SCWSNormal::SCWSNormal(SessionControlWindowBackend* sessionControlWindowBackend) {
    sessionControlWindowBackend->startTimer();
}
