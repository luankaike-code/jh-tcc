/*
 * SPDX-FileCopyrightText: 2026 luankaike-code <https://github.com/luankaike-code>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef SESSIONMODES_H
#define SESSIONMODES_H

#include <QObject>
#include <qqmlintegration.h>

namespace SessionModes {
    Q_NAMESPACE
    QML_ELEMENT

    enum Enum {
        Normal,
        Classroom,
        InfinityTime,
        InfinityImages,
        Sandbox
    };
    Q_ENUM_NS(Enum)
}

#endif // SESSIONMODES_H
