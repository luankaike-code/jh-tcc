/*
 * SPDX-FileCopyrightText: 2026 luankaike-code <https://github.com/luankaike-code>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef CLASSROOMSESSIONHELPER_H
#define CLASSROOMSESSIONHELPER_H

#include <vector>
#include "./helpers/classroomSessionRoadmapStep/classroomSessionRoadmapStep.h"

class ClassroomSessionHelper {
protected:
    static ClassroomSessionRoadmapStep roadMapData[19];
public:
    ClassroomSessionHelper();

    static void printRoadmap(const std::vector<ClassroomSessionRoadmapStep>& roadmap);
    static std::vector<ClassroomSessionRoadmapStep> createSessionRoadmap(const int& durationMiliseconds);
};

#endif // CLASSROOMSESSIONHELPER_H
