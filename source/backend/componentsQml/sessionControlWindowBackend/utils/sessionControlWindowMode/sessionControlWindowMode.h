/*
 * SPDX-FileCopyrightText: 2026 luankaike-code <https://github.com/luankaike-code>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef SESSIONCONTROLWINDOWSTATE_H
#define SESSIONCONTROLWINDOWSTATE_H

#include <QObject>

class SessionControlWindowBackend;

class SessionControlWindowMode : public QObject {
    Q_OBJECT

public:
    SessionControlWindowMode(SessionControlWindowBackend* sessionControlWindowBackend = nullptr);
    virtual ~SessionControlWindowMode() = default;

    virtual void pressNextButton(SessionControlWindowBackend* sessionControlWindowBackend);
    virtual void pressPreventButton(SessionControlWindowBackend* sessionControlWindowBackend);
    virtual void intervalTimerFinish(SessionControlWindowBackend* sessionControlWindowBackend);
    virtual const bool isSessionFinished(SessionControlWindowBackend* sessionControlWindowBackend) const;

    virtual void startSession(SessionControlWindowBackend* sessionControlWindowBackend);
};

#endif // SESSIONCONTROLWINDOWSTATE_H
