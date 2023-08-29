#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "CxFlexible.h"
#include "CxFlexItem.h"

void registerTypes(const char *uri, int majorVersion, int minorVersion)
{
    // @uri CxFlex

    qmlRegisterUncreatableType<CxFlex>(uri, majorVersion, minorVersion, "CxFlex", "Internal");

    qmlRegisterUncreatableType<CxFlexibleRegister>(uri, majorVersion, minorVersion, "CxFlexible", "Internal");

    qmlRegisterType<CxFlexItem>(uri, majorVersion, minorVersion, "CxFlexItem");

    qmlRegisterType<CxFlexColumn>(uri, majorVersion, minorVersion, "CxFlexColumn");
    qmlRegisterType<CxFlexColumnReverse>(uri, majorVersion, minorVersion, "CxFlexColumnReverse");
    qmlRegisterType<CxFlexRow>(uri, majorVersion, minorVersion, "CxFlexRow");
    qmlRegisterType<CxFlexRowReverse>(uri, majorVersion, minorVersion, "CxFlexRowReverse");
}


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    registerTypes("CxFlex", 1, 0);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
