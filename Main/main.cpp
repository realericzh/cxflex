#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QFontDatabase::addApplicationFont(":/qt/qml/Flexbox/Main/Fonts/Rubik-VariableFont_wght.ttf");
    QFontDatabase::addApplicationFont(":/qt/qml/Flexbox/Main/Fonts/CascadiaMono-VariableFont_wght.ttf");

    QFont defaultFont = app.font();
    defaultFont.setFamily("Rubik");
    app.setFont(defaultFont);

    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
                     &app, [] { QCoreApplication::exit(-1); },
                     Qt::QueuedConnection);
    engine.loadFromModule("Flexbox", "Main");

    return app.exec();
}
