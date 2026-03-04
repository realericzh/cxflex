#ifndef FLEXBOXAPP_H
#define FLEXBOXAPP_H

#include <QObject>
#include <QtQmlIntegration>

class FlexboxAppPrivate;
class FlexboxApp : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
    Q_DECLARE_PRIVATE(FlexboxApp)

public:
    explicit FlexboxApp(QObject *parent = nullptr);
    ~FlexboxApp() override;
protected:
    QScopedPointer<FlexboxAppPrivate> d_ptr;

public:
    Q_INVOKABLE QString readFile(const QString &fileName) const;
};

#endif // FLEXBOXAPP_H
