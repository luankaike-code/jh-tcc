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
    Q_PROPERTY(const bool isRunning READ getIsRunning NOTIFY isRunningChanged)

    QTimer qTimer;
    QTimer qTimerElapsed;

    void emitTimeElapsed(int customRemainingTime=-1);
    void intervalTimeout();

    int timeElapsedDelay;
    int intervalDelay;

    int m_remainingTime;
public:
    explicit Timer(QObject *parent = nullptr, int timeElapsedDelay = 50);

    const int& getRemainingTime();
    const bool getIsRunning();

    Q_INVOKABLE void startInfinityIntervals(const int& delay);
    Q_INVOKABLE void play(bool resetTimer=false);
    Q_INVOKABLE void stop();
signals:
    void finishInterval();

    void timeElapsed();
    void isRunningChanged();
};

#endif // TIMER_H