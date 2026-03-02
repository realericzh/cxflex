#ifndef FLEXSETTINGS_H
#define FLEXSETTINGS_H

#include <QObject>

class FlexSettingsPrivate;
class FlexSettings : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(FlexSettings)

public:
    explicit FlexSettings(QObject *parent = nullptr);
protected:
    QScopedPointer<FlexSettingsPrivate> d_ptr;
public:
    static FlexSettings *instance();
public:
    virtual ~FlexSettings();
};

#endif // FLEXSETTINGS_H
