#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Modules/backend.h"
#include "Modules/fileopener.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<Backend>("BigNumCalculator.Modules", 1, 0, "Backend");
    qmlRegisterType<FileOpener>("BigNumCalculator.Modules", 1, 0, "FileOpener");

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("BigNumCalculator", "Main");

    return app.exec();
}
