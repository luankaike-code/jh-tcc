#include "SCWSClassroom.h"

#include "../sessionControlWindowBackend/sessionControlWindowBackend.h"
#include "../../helpers/timeConvertion/timeConvertion.h"
#include <iostream>
#include <stdexcept>

SCWSClassroom::SCWSClassroom(SessionControlWindowBackend* sessionControlWindowBackend) :
    SessionControlWindowState(sessionControlWindowBackend), currentRoadmapStepIndex(0) {}

void SCWSClassroom::configureCurrentRoadmapStep(SessionControlWindowBackend* sessionControlWindowBackend) {
    if(currentRoadmapStepIndex >= roadmap.size())
        return;

    ClassroomSessionRoadmapStep& currentStep = roadmap[currentRoadmapStepIndex];
    ClassroomSessionHelper::printRoadmap(roadmap);

    sessionControlWindowBackend->setCurrentImageIndex(1);
    sessionControlWindowBackend->setIsRestPause(currentStep.isRestStep);
    sessionControlWindowBackend->setDelayImage(currentStep.durationMiliseconds);
    sessionControlWindowBackend->setImageCount(currentStep.repetions);
    sessionControlWindowBackend->startTimer();
}

bool SCWSClassroom::isCurrentRoadmapStepFinished(SessionControlWindowBackend* sessionControlWindowBackend) {
    return sessionControlWindowBackend->getCurrentImageIndex() > sessionControlWindowBackend->getImageCount();
}

void SCWSClassroom::intervalTimerFinish(SessionControlWindowBackend* sessionControlWindowBackend) {
    sessionControlWindowBackend->setCurrentImageIndex(sessionControlWindowBackend->getCurrentImageIndex()+1);
    if(!sessionControlWindowBackend->getIsRestPause())
        sessionControlWindowBackend->goToNextImage();

    if(isCurrentRoadmapStepFinished(sessionControlWindowBackend)) {
        currentRoadmapStepIndex++;
        configureCurrentRoadmapStep(sessionControlWindowBackend);
    }
    if(isSessionFinished(sessionControlWindowBackend))
        sessionControlWindowBackend->sessionFinished();
}

const bool SCWSClassroom::isSessionFinished(SessionControlWindowBackend* sessionControlWindowBackend) const {
    return currentRoadmapStepIndex >= roadmap.size();
}
