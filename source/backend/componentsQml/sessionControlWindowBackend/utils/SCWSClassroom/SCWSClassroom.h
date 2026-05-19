#ifndef SCWSCLASSROOM_H
#define SCWSCLASSROOM_H

#include "../sessionControlWindowState/sessionControlWindowState.h"
#include "../../helpers/classroomSessionHelper/classroomSessionHelper.h"

class SCWSClassroom : public SessionControlWindowState {
    std::vector<ClassroomSessionRoadmapStep> roadmap;
    int currentRoadmapStepIndex;
    int currentStepRepetionIndex;
public:
    SCWSClassroom(SessionControlWindowBackend* sessionControlWindowBackend);
    void intervalTimerFinish(SessionControlWindowBackend* sessionControlWindowBackend) override;
};

#endif // SCWSCLASSROOM_H
