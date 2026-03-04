#include "FlexboxApp.h"
#include "FlexboxApp_p.h"

#include <QFile>

// class FlexboxApp

FlexboxApp::FlexboxApp(QObject *parent)
    : QObject{parent}
    , d_ptr{new FlexboxAppPrivate{}}
{
    d_ptr->q_ptr = this;
}

FlexboxApp::~FlexboxApp() = default;

QString FlexboxApp::readFile(const QString &fileName) const
{
    QFile file{QStringLiteral(":/qt/qml/Flexbox/Main/") % fileName};
    if (file.open(QFile::ReadOnly)) {
        return QString::fromUtf8(file.readAll());
    }

    return {};
}

// class FlexboxAppPrivate
