/*
 * SPDX-FileCopyrightText: 2026 luankaike-code <https://github.com/luankaike-code>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef SCWMNORMAL_H
#define SCWMNORMAL_H

#include "../sessionControlWindowMode/sessionControlWindowMode.h"

class SessionControlWindowBackend;

class SCWMNormal : public SessionControlWindowMode {
public:
    SCWMNormal(SessionControlWindowBackend* sessionControlWindowBackend);

    void startSession(SessionControlWindowBackend* sessionControlWindowBackend) override;
};

#endif // SCWMNORMAL_H
