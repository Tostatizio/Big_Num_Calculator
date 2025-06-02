#include <QApplication>
#include <QQmlApplicationEngine>
#include "Modules/backhelper.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<BackHelper>("BigNumCalculator.Modules", 1, 0, "BackHelper");

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
