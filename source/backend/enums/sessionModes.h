#ifndef SESSIONMODES_H
#define SESSIONMODES_H

#include <QObject>
#include <QQmlEngine>
#include <QTimer>
#include <qobjectdefs.h>

class SessionModes : public QObject {
    Q_OBJECT
    QML_ELEMENT

public:

    enum Modes {
        Normal,
        Classroom,
        InfinityTime,
        InfinityImages,
        Sandbox
    };

    Q_ENUM(Modes)
};

#endif // SESSIONMODES_H
