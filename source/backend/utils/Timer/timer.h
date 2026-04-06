#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QQmlEngine>

class Timer : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit Timer(QObject *parent = nullptr);
    Q_INVOKABLE void hello_world();
};

#endif // TIMER_H
