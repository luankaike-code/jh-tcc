#ifndef APPLICATIONBACKEND_HPP
#define APPLICATIONBACKEND_HPP

#include <QGuiApplication>
#include <QQmlApplicationEngine>

class ApplicationBackend {

    QQmlApplicationEngine engine;

protected:
    ApplicationBackend();

    static ApplicationBackend* instance;
public:
    ApplicationBackend(ApplicationBackend& other) = delete;
    void operator=(const ApplicationBackend& other) = delete;

    static ApplicationBackend* getInstance();
    QQmlApplicationEngine* getEngine();
};

#endif // APPLICATIONBACKEND_HPP
