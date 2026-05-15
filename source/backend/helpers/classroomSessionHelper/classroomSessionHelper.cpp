#include "classroomSessionHelper.h"

#include "../timeConvertion/timeConvertion.h"

ClassroomSessionRoadmapStep ClassroomSessionHelper::roadMapData[19] = {
    ClassroomSessionRoadmapStep(TimeConvertion::minutesToMiliseconds(0.5), 10, false),
    ClassroomSessionRoadmapStep(TimeConvertion::minutesToMiliseconds(1), 5, false),
    ClassroomSessionRoadmapStep(TimeConvertion::minutesToMiliseconds(5), 2, false),
    ClassroomSessionRoadmapStep(TimeConvertion::minutesToMiliseconds(10), 1, false),
    ClassroomSessionRoadmapStep(TimeConvertion::minutesToMiliseconds(20), 1, false),
    ClassroomSessionRoadmapStep(TimeConvertion::minutesToMiliseconds(10), 1, true),
    ClassroomSessionRoadmapStep(TimeConvertion::minutesToMiliseconds(30), 2, false),
    ClassroomSessionRoadmapStep(TimeConvertion::minutesToMiliseconds(10), 1, true),
    ClassroomSessionRoadmapStep(TimeConvertion::minutesToMiliseconds(50), 1, false),
    ClassroomSessionRoadmapStep(TimeConvertion::minutesToMiliseconds(45), 1, true),
    ClassroomSessionRoadmapStep(TimeConvertion::minutesToMiliseconds(0.5), 6, false),
    ClassroomSessionRoadmapStep(TimeConvertion::minutesToMiliseconds(1), 4, false),
    ClassroomSessionRoadmapStep(TimeConvertion::minutesToMiliseconds(5), 3, false),
    ClassroomSessionRoadmapStep(TimeConvertion::minutesToMiliseconds(10), 1, true),
    ClassroomSessionRoadmapStep(TimeConvertion::minutesToMiliseconds(45), 1, false),
    ClassroomSessionRoadmapStep(TimeConvertion::minutesToMiliseconds(10), 1, true),
    ClassroomSessionRoadmapStep(TimeConvertion::minutesToMiliseconds(110), 1, false),
    ClassroomSessionRoadmapStep(TimeConvertion::minutesToMiliseconds(45), 1, false),
    ClassroomSessionRoadmapStep(TimeConvertion::minutesToMiliseconds(20), 1, true),
};

ClassroomSessionHelper::ClassroomSessionHelper() {}

std::vector<ClassroomSessionRoadmapStep> ClassroomSessionHelper::createSessionRoadmap(const int& durationMiliseconds) {
    std::vector<ClassroomSessionRoadmapStep> sessionRoadmap;

    bool loop = true;
    int remainingTime = durationMiliseconds;
    while(loop) {
        for(ClassroomSessionRoadmapStep& rpData : ClassroomSessionHelper::roadMapData) {
            if(rpData.durationMiliseconds > remainingTime) {
                loop = remainingTime > ClassroomSessionHelper::roadMapData[0].durationMiliseconds;
                break;
            }

            ClassroomSessionRoadmapStep currentRpData = rpData.totalDurationMiliseconds < remainingTime ?
                ClassroomSessionRoadmapStep(rpData) :
                ClassroomSessionRoadmapStep(rpData.durationMiliseconds, remainingTime / rpData.durationMiliseconds, rpData.isRestStep);

            remainingTime -= currentRpData.totalDurationMiliseconds;
            sessionRoadmap.push_back(currentRpData);
        }
    }

    return sessionRoadmap;
}