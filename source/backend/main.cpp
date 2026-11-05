// SPDX-FileCopyrightText: 2026 luankaike-code <https://github.com/luankaike-code>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <QApplication>
#include <QQmlApplicationEngine>
#include <qicon.h>
#include "applicationBackend/applicationBackend.hpp"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

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
