#ifndef SCWSCLASSROOM_H
#define SCWSCLASSROOM_H

#include "../sessionControlWindowState/sessionControlWindowState.h"

class SCWSClassroom : public SessionControlWindowState {
public:
    SCWSClassroom(SessionControlWindowBackend* sessionControlWindowBackend);
    void intervalTimerFinish(SessionControlWindowBackend* sessionControlWindowBackend) override;
};

#endif // SCWSCLASSROOM_H
