#ifndef SCWMSANDBOX_H
#define SCWMSANDBOX_H

#include "../sessionControlWindowMode/sessionControlWindowMode.h"

class SCWMSandbox : public SessionControlWindowMode {
public:
    SCWMSandbox(SessionControlWindowBackend* sessionControlWindowBackend);

    void pressNextButton(SessionControlWindowBackend* sessionControlWindowBackend) override;
    void pressPreventButton(SessionControlWindowBackend* sessionControlWindowBackend) override;
    const bool isSessionFinished(SessionControlWindowBackend* sessionControlWindowBackend) const override;
    void intervalTimerFinish(SessionControlWindowBackend* sessionControlWindowBackend) override;
};

#endif // SCWMSANDBOX_H
