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
    Q_PROPERTY(const int remainingTime READ getRemainingTime NOTIFY timeElapsed)

    QTimer qTimer;
    QTimer qTimerElapsed;
    int intervalCount;
    int currentInterval;

    void emitTimeElapsed();
    void intervalTimeout();

    int timeElapsedDelay;
public:
    explicit Timer(QObject *parent = nullptr, int timeElapsedDelay = 50);

    const int getRemainingTime();

    Q_INVOKABLE void startRhythmIntervals(const int& delay, const int& count);
    Q_INVOKABLE void play();
    Q_INVOKABLE void stop();
signals:
    void finishInterval();
    void finishAllIntervals();
    void timeElapsed();
};

#endif // TIMER_H