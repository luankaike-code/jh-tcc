#include "SCWMClassroom.h"

#include "../sessionControlWindowBackend/sessionControlWindowBackend.h"

SCWMClassroom::SCWMClassroom(SessionControlWindowBackend* sessionControlWindowBackend) :
    SessionControlWindowMode(sessionControlWindowBackend), currentRoadmapStepIndex(0),
    roadmap(ClassroomSessionHelper::createSessionRoadmap(sessionControlWindowBackend->getRoadmapDuration())) {
}

void SCWMClassroom::startSession(SessionControlWindowBackend* sessionControlWindowBackend) {
    configureCurrentRoadmapStep(sessionControlWindowBackend);
}

void SCWMClassroom::configureCurrentRoadmapStep(SessionControlWindowBackend* sessionControlWindowBackend) {
    if(currentRoadmapStepIndex >= roadmap.size() && roadmap.size() > 0)
        return;
    ClassroomSessionRoadmapStep& currentStep = roadmap[currentRoadmapStepIndex];
    ClassroomSessionHelper::printRoadmap(roadmap);

    sessionControlWindowBackend->setCurrentImageIndex(1);
    sessionControlWindowBackend->setIsRestPause(currentStep.isRestStep);
    sessionControlWindowBackend->setDelayImage(currentStep.durationMiliseconds);
    sessionControlWindowBackend->setImageCount(currentStep.repetions);
    sessionControlWindowBackend->startTimer();
}

bool SCWMClassroom::isCurrentRoadmapStepFinished(SessionControlWindowBackend* sessionControlWindowBackend) {
    return sessionControlWindowBackend->getCurrentImageIndex() > sessionControlWindowBackend->getImageCount();
}

void SCWMClassroom::intervalTimerFinish(SessionControlWindowBackend* sessionControlWindowBackend) {
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

const bool SCWMClassroom::isSessionFinished(SessionControlWindowBackend* sessionControlWindowBackend) const {
    return currentRoadmapStepIndex >= roadmap.size();
}
