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

    Q_INVOKABLE bool hasTimerLimit(const SessionModes::Enum& sessionModeValue) const;
    Q_INVOKABLE bool hasImagesLimit(const SessionModes::Enum& sessionModeValue) const;
};

#endif // SESSIONMODEREADER_H
