#ifndef SCWSNORMAL_H
#define SCWSNORMAL_H

#include "../sessionControlWindowState/sessionControlWindowState.h"

class SessionControlWindowBackend;

class SCWSNormal : public SessionControlWindowState {
public:
    SCWSNormal(SessionControlWindowBackend* sessionControlWindowBackend);

    void delayImageChanged(SessionControlWindowBackend* sessionControlWindowBackend) override;
    void startSession(SessionControlWindowBackend* sessionControlWindowBackend) override;
};

#endif // SCWSNORMAL_H
