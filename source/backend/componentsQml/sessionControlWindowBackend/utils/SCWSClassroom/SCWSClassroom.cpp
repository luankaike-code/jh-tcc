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
    sessionControlWindowBackend->setDelayImage(currentStep.durationMiliseconds);
    sessionControlWindowBackend->setImagesCount(currentStep.repetions);
    sessionControlWindowBackend->startTimer();
}

void SCWSClassroom::roadmapDurationChanged(SessionControlWindowBackend* sessionControlWindowBackend) {
    currentRoadmapStepIndex = 0;
    roadmap = ClassroomSessionHelper::createSessionRoadmap(sessionControlWindowBackend->getRoadmapDuration());

    configureCurrentRoadmapStep(sessionControlWindowBackend);
}

bool SCWSClassroom::isCurrentRoadmapStepFinished(SessionControlWindowBackend* sessionControlWindowBackend) {
    return sessionControlWindowBackend->getCurrentImageIndex() > sessionControlWindowBackend->getImagesCount();
}

void SCWSClassroom::intervalTimerFinish(SessionControlWindowBackend* sessionControlWindowBackend) {
    sessionControlWindowBackend->setCurrentImageIndex(sessionControlWindowBackend->getCurrentImageIndex()+1);
    sessionControlWindowBackend->goToNextImage();

    if(isCurrentRoadmapStepFinished(sessionControlWindowBackend)) {
        currentRoadmapStepIndex++;
        configureCurrentRoadmapStep(sessionControlWindowBackend);
    }
    if(isSessionFinished(sessionControlWindowBackend->getCurrentImageIndex(), sessionControlWindowBackend->getImagesCount()))
        sessionControlWindowBackend->sessionFinish();
}

bool SCWSClassroom::isSessionFinished(const int& currentImageIndex, const int& countImage) {
    return currentRoadmapStepIndex >= roadmap.size();
}
