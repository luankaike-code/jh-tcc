#ifndef SCWSSANDBOX_H
#define SCWSSANDBOX_H

#include "../sessionControlWindowState/sessionControlWindowState.h"

class SCWSSandbox : public SessionControlWindowState {
public:
    SCWSSandbox(SessionControlWindowBackend* sessionControlWindowBackend);

    void nextButtonPressed(SessionControlWindowBackend* sessionControlWindowBackend) override;
    void preventButtonPressed(SessionControlWindowBackend* sessionControlWindowBackend) override;
    const bool isSessionFinished(SessionControlWindowBackend* sessionControlWindowBackend) const override;
    void intervalTimerFinish(SessionControlWindowBackend* sessionControlWindowBackend) override;
};

#endif // SCWSSANDBOX_H
