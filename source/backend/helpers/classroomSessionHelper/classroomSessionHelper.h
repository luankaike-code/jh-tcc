#ifndef CLASSROOMSESSIONHELPER_H
#define CLASSROOMSESSIONHELPER_H

#include <vector>
#include "./utils/classroomSessionRoadmapStep/classroomSessionRoadmapStep.h"

class ClassroomSessionHelper {
protected:
    static ClassroomSessionRoadmapStep roadMapData[19];
public:
    ClassroomSessionHelper();

    static void printRoadmap(const std::vector<ClassroomSessionRoadmapStep>& roadmap);
    static std::vector<ClassroomSessionRoadmapStep> createSessionRoadmap(const int& durationMiliseconds);
};

#endif // CLASSROOMSESSIONHELPER_H
