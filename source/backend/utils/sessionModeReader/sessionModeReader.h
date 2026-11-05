/*
 * SPDX-FileCopyrightText: 2026 luankaike-code <https://github.com/luankaike-code>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef SESSIONMODEREADER_H
#define SESSIONMODEREADER_H

#include <QObject>
#include "../enums/sessionModes.h"

class SessionModeReader : public QObject {
    Q_OBJECT
    QML_SINGLETON
    QML_ELEMENT

public:
    SessionModeReader(QObject* parent = nullptr);

    Q_INVOKABLE static bool hasTimerLimit(const SessionModes::Enum& sessionModeValue);
    Q_INVOKABLE static bool hasImagesLimit(const SessionModes::Enum& sessionModeValue);
    Q_INVOKABLE static bool hasRoadmap(const SessionModes::Enum& sessionModeValue);
};

#endif // SESSIONMODEREADER_H
