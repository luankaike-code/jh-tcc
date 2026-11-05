/*
 * SPDX-FileCopyrightText: 2026 luankaike-code <https://github.com/luankaike-code>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef SCWMINFINITYTIME_H
#define SCWMINFINITYTIME_H

#include "../sessionControlWindowMode/sessionControlWindowMode.h"

class SCWMInfinityTime : public SessionControlWindowMode {
public:
    SCWMInfinityTime(SessionControlWindowBackend* sessionControlWindowBackend);

    void pressNextButton(SessionControlWindowBackend* sessionControlWindowBackend) override;
    void pressPreventButton(SessionControlWindowBackend* sessionControlWindowBackend) override;
    void intervalTimerFinish(SessionControlWindowBackend* sessionControlWindowBackend) override;
};

#endif // SCWMINFINITYTIME_H
