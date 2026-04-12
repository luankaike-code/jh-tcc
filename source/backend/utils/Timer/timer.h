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
    Q_PROPERTY(const int intervalCount READ getIntervalCount NOTIFY intervalCountChanged)
    Q_PROPERTY(const int currentInterval READ getCurrentInterval NOTIFY currentIntervalChanged)

    QTimer qTimer;
    QTimer qTimerElapsed;

    void emitTimeElapsed(int customRemainingTime=-1);
    void intervalTimeout();

    int timeElapsedDelay;
    int intervalDelay;

    int m_remainingTime;
    int m_intervalCount;
    int m_currentInterval;
public:
    explicit Timer(QObject *parent = nullptr, int timeElapsedDelay = 50);

    void setIntervalCount(int value);
    void setCurrentInterval(int value);

    const int getRemainingTime();
    const int getIntervalCount();
    const int getCurrentInterval();

    Q_INVOKABLE void startRhythmIntervals(const int& delay, const int& count);
    Q_INVOKABLE void play(bool resetTimer=false);
    Q_INVOKABLE void stop();
signals:
    void finishInterval();
    void finishAllIntervals();

    void timeElapsed();
    void intervalCountChanged();
    void currentIntervalChanged();
};

#endif // TIMER_H