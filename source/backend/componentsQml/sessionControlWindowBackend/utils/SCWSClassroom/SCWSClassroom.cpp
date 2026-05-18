#include "SCWSClassroom.h"

#include "../sessionControlWindowBackend/sessionControlWindowBackend.h"
#include "../../helpers/timeConvertion/timeConvertion.h"
#include <iostream>

SCWSClassroom::SCWSClassroom(SessionControlWindowBackend* sessionControlWindowBackend) :
    currrentRoadMapStepIndex(0), currentStepRepetionIndex(0), roadmap(ClassroomSessionHelper::createSessionRoadmap(TimeConvertion::minutesToMiliseconds(450)))
{
    sessionControlWindowBackend->startTimer();
    for(ClassroomSessionRoadmapStep& o : roadmap) {
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