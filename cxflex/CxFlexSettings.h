#ifndef CXFLEXSETTINGS_H
#define CXFLEXSETTINGS_H

#include <QObject>

class CxFlexSettingsPrivate;
class CxFlexSettings : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(CxFlexSettings)

public:
    explicit CxFlexSettings(QObject *parent = nullptr);
protected:
    QScopedPointer<CxFlexSettingsPrivate> d_ptr;
public:
    static CxFlexSettings *instance();
public:
    virtual ~CxFlexSettings();
};

#endif // CXFLEXSETTINGS_H
