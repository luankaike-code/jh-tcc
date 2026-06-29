#ifndef SCWSINFINITYTIME_H
#define SCWSINFINITYTIME_H

#include "../sessionControlWindowState/sessionControlWindowState.h"

class SCWSInfinityTime : public SessionControlWindowState {
public:
    SCWSInfinityTime(SessionControlWindowBackend* sessionControlWindowBackend);

    void pressNextButton(SessionControlWindowBackend* sessionControlWindowBackend) override;
    void pressPreventButton(SessionControlWindowBackend* sessionControlWindowBackend) override;
    void intervalTimerFinish(SessionControlWindowBackend* sessionControlWindowBackend) override;
};

#endif // SCWSINFINITYTIME_H
