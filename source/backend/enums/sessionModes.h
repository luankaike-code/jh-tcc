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
