#ifndef SCWSCLASSROOM_H
#define SCWSCLASSROOM_H

#include "../sessionControlWindowState/sessionControlWindowState.h"
#include "../../helpers/classroomSessionHelper/classroomSessionHelper.h"

class SCWSClassroom : public SessionControlWindowState {
    std::vector<ClassroomSessionRoadmapStep> roadmap;
    int currentRoadmapStepIndex;

    void configureCurrentRoadmapStep(SessionControlWindowBackend* sessionControlWindowBackend);

    bool isCurrentRoadmapStepFinished(SessionControlWindowBackend* sessionControlWindowBackend);
public:
    SCWSClassroom(SessionControlWindowBackend* sessionControlWindowBackend);
    void intervalTimerFinish(SessionControlWindowBackend* sessionControlWindowBackend) override;
    void roadmapDurationChanged(SessionControlWindowBackend* sessionControlWindowBackend) override;
    bool isSessionFinished(const int& currentImageIndex, const int& countImage) override;
};

#endif // SCWSCLASSROOM_H
