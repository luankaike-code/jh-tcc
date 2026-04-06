#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QQmlEngine>
#include <QTimer>
#include <qobjectdefs.h>

class Timer : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    QTimer qTimer;
    int intervalCount;
    int currentInterval;

    void intervalTimeout();
public:
    explicit Timer(QObject *parent = nullptr);

    Q_INVOKABLE void startRhythmIntervals(const int& delay, const int& count);
signals:
    void finishInterval();
    void finishAllIntervals();
};

#endif // TIMER_H