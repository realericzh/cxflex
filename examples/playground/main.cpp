#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "Flexbox.h"

void registerTypes(const char *uri, int majorVersion, int minorVersion)
{
    // @uri CxFlex

    qmlRegisterUncreatableType<Flexbox>(uri, majorVersion, minorVersion, "Flexbox", "Internal");
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    registerTypes("CxFlex", 1, 0);

    QQmlApplicationEngine engine;
    const QUrl url("qrc:/main.qml");
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
