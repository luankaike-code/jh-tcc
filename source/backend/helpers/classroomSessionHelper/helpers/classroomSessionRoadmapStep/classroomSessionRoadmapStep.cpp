// SPDX-FileCopyrightText: 2026 luankaike-code <https://github.com/luankaike-code>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "classroomSessionRoadmapStep.h"

ClassroomSessionRoadmapStep::ClassroomSessionRoadmapStep(const int& durationMiliseconds, const int& repetions, const bool& isRestStep)
    : durationMiliseconds(durationMiliseconds), repetions(repetions), totalDurationMiliseconds(durationMiliseconds*repetions), isRestStep(isRestStep) {}
