/*
 * SPDX-FileCopyrightText: 2026 luankaike-code <https://github.com/luankaike-code>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef SCWMINFINITYIMAGES_H
#define SCWMINFINITYIMAGES_H

#include "../sessionControlWindowMode/sessionControlWindowMode.h"

class SessionControlWindowBackend;

class SCWMInfinityImages : public SessionControlWindowMode {
public:
    SCWMInfinityImages(SessionControlWindowBackend* sessionControlWindowBackend);

    const bool isSessionFinished(SessionControlWindowBackend* sessionControlWindowBackend) const override;
    void startSession(SessionControlWindowBackend* sessionControlWindowBackend) override;
};

#endif // SCWMINFINITYIMAGES_H
