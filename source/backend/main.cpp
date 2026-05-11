#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "applicationBackend/applicationBackend.hpp"
#include "enums/sessionModes.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    ApplicationBackend* applicationBackend = ApplicationBackend::getInstance();
    QQmlApplicationEngine* engine = applicationBackend->getEngine();

    qmlRegisterUncreatableType<SessionModes>("flashdraws.enums", 1, 0, "SessionModes", "Enums dont instanted");

    QObject::connect(
        engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine->loadFromModule("flashdraws", "Main");

    return QCoreApplication::exec();
}
