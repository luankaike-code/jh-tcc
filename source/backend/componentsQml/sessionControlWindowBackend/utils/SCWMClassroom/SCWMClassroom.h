#ifndef SCWMCLASSROOM_H
#define SCWMCLASSROOM_H

#include "../sessionControlWindowMode/sessionControlWindowMode.h"
#include "../../helpers/classroomSessionHelper/classroomSessionHelper.h"

class SCWMClassroom : public SessionControlWindowMode {
    std::vector<ClassroomSessionRoadmapStep> roadmap;
    int currentRoadmapStepIndex;

    void configureCurrentRoadmapStep(SessionControlWindowBackend* sessionControlWindowBackend);

    bool isCurrentRoadmapStepFinished(SessionControlWindowBackend* sessionControlWindowBackend);
    void startSession(SessionControlWindowBackend* sessionControlWindowBackend) override;
public:
    SCWMClassroom(SessionControlWindowBackend* sessionControlWindowBackend);
    void intervalTimerFinish(SessionControlWindowBackend* sessionControlWindowBackend) override;
    const bool isSessionFinished(SessionControlWindowBackend* sessionControlWindowBackend) const override;
};

#endif // SCWMCLASSROOM_H
