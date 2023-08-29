#include "CxFlexSettings.h"
#include "CxFlexSettings_p.h"

// class CxFlexSettings

Q_GLOBAL_STATIC(CxFlexSettings, staticFlexSettings)

CxFlexSettings::CxFlexSettings(QObject *parent)
    : QObject(parent)
    , d_ptr(new CxFlexSettingsPrivate())
{
    d_ptr->q_ptr = this;

    Q_D(CxFlexSettings);

    d->config = YGConfigNew();
    YGConfigSetContext(d->config, this);
    YGConfigSetLogger(d->config, &CxFlexSettingsPrivate::logger);

    YGConfigSetPrintTreeFlag(d->config, true);
}

CxFlexSettings *CxFlexSettings::instance()
{
    return staticFlexSettings;
}

CxFlexSettings::~CxFlexSettings()
{
    Q_D(CxFlexSettings);

    YGConfigFree(d->config);
}

// class CxFlexSettingsPrivate

CxFlexSettingsPrivate::CxFlexSettingsPrivate()
    : q_ptr(nullptr)
{
}

CxFlexSettingsPrivate::~CxFlexSettingsPrivate()
{
}

YGConfigRef CxFlexSettingsPrivate::defaultConfig()
{
    CxFlexSettings *settings = staticFlexSettings;
    if (settings) {
        return settings->d_func()->config;
    }

    return YGConfigGetDefault();
}

int CxFlexSettingsPrivate::logger(YGConfigRef config, YGNodeRef node, YGLogLevel level, const char *format, va_list args)
{
    Q_UNUSED(config);
    Q_UNUSED(node);
    Q_UNUSED(level);
    Q_UNUSED(args);

    qInfo("print %s", format);
    return 0;
}
