// SPDX-FileCopyrightText: 2026 luankaike-code <https://github.com/luankaike-code>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "SCWMInfinityImages.h"

#include "../../sessionControlWindowBackend.h"

SCWMInfinityImages::SCWMInfinityImages(SessionControlWindowBackend* sessionControlWindowBackend) : SessionControlWindowMode(sessionControlWindowBackend) {}

const bool SCWMInfinityImages::isSessionFinished(SessionControlWindowBackend* sessionControlWindowBackend) const {
    return false;
}

void SCWMInfinityImages::startSession(SessionControlWindowBackend* sessionControlWindowBackend) {
    sessionControlWindowBackend->startTimer();
};