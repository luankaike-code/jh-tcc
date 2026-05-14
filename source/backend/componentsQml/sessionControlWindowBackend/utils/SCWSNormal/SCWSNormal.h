#ifndef SCWSNORMAL_H
#define SCWSNORMAL_H

#include "../sessionControlWindowState/sessionControlWindowState.h"

class SessionControlWindowBackend;

class SCWSNormal : public SessionControlWindowState {
public:
    SCWSNormal(SessionControlWindowBackend* sessionControlWindowBackend);
};

#endif // SCWSNORMAL_H
