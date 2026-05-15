#include "SCWSClassroom.h"

#include "../sessionControlWindowBackend/sessionControlWindowBackend.h"
#include "../../helpers/classroomSessionHelper/classroomSessionHelper.h"
#include "../../helpers/timeConvertion/timeConvertion.h"
#include <iostream>

SCWSClassroom::SCWSClassroom(SessionControlWindowBackend* sessionControlWindowBackend) {
    sessionControlWindowBackend->startTimer();
    std::vector<ClassroomSessionRoadmapStep> oi = ClassroomSessionHelper::createSessionRoadmap(TimeConvertion::minutesToMiliseconds(450));
    for(ClassroomSessionRoadmapStep& o : oi) {
        int time = TimeConvertion::milisecondsToMinutes(o.durationMiliseconds);
        std::cout << time << " minutes x " << o.repetions << ". is pause: " << o.isRestStep << std::endl;
    }
}

void SCWSClassroom::intervalTimerFinish(SessionControlWindowBackend* sessionControlWindowBackend) {
    if(isSessionFinished(sessionControlWindowBackend->getCurrentImageIndex(), sessionControlWindowBackend->getImagesCount()))
        sessionControlWindowBackend->sessionFinish();

    sessionControlWindowBackend->setCurrentImageIndex(sessionControlWindowBackend->getCurrentImageIndex()+1);
    sessionControlWindowBackend->goToNextImage();
}