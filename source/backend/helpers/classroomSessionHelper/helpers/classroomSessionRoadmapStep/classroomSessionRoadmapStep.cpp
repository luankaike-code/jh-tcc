#include "classroomSessionRoadmapStep.h"

ClassroomSessionRoadmapStep::ClassroomSessionRoadmapStep(const int& durationMiliseconds, const int& repetions, const bool& isRestStep)
    : durationMiliseconds(durationMiliseconds), repetions(repetions), totalDurationMiliseconds(durationMiliseconds*repetions), isRestStep(isRestStep) {}
