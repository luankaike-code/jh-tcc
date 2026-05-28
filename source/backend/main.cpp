#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <qicon.h>
#include "applicationBackend/applicationBackend.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    app.setWindowIcon(QIcon(":/assets/flashdraws.svg"));

    ApplicationBackend* applicationBackend = ApplicationBackend::getInstance();
    QQmlApplicationEngine* engine = applicationBackend->getEngine();

    QObject::connect(
        engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine->loadFromModule("flashdraws", "Main");

    return QCoreApplication::exec();
}
