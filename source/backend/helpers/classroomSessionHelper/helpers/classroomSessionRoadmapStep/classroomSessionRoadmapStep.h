#ifndef CLASSROOMSESSIONROADMAPSTEP_H
#define CLASSROOMSESSIONROADMAPSTEP_H

class ClassroomSessionRoadmapStep {
public:
    ClassroomSessionRoadmapStep(const int& durationMiliseconds, const int& repetions, const bool& isRestStep);

    const int durationMiliseconds;
    const int repetions;
    const int totalDurationMiliseconds;
    const bool isRestStep;
};

#endif // CLASSROOMSESSIONROADMAPSTEP_H
