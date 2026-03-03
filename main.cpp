#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QFontDatabase::addApplicationFont(":/qt/qml/Flexbox/fonts/FiraCode-Regular.ttf");

    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
                     &app, [] { QCoreApplication::exit(-1); },
                     Qt::QueuedConnection);
    engine.loadFromModule("Flexbox", "Main");

    return app.exec();
}
