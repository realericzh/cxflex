#include "FlexSettings.h"
#include "FlexSettings_p.h"

// class FlexSettings

Q_GLOBAL_STATIC(FlexSettings, staticFlexSettings)

FlexSettings::FlexSettings(QObject *parent)
    : QObject(parent)
    , d_ptr(new FlexSettingsPrivate())
{
    d_ptr->q_ptr = this;

    Q_D(FlexSettings);

    d->config = YGConfigNew();
    if (d->config) {
        YGConfigSetContext(d->config, this);
        YGConfigSetLogger(d->config, &FlexSettingsPrivate::logger);
    }

    // YGConfigSetPrintTreeFlag(d->config, true);
}

FlexSettings *FlexSettings::instance()
{
    return staticFlexSettings;
}

FlexSettings::~FlexSettings()
{
    Q_D(FlexSettings);

    if (d->config) {
        YGConfigFree(d->config);
        d->config = nullptr;
    }
}

// class FlexSettingsPrivate

YGConfigConstRef FlexSettingsPrivate::defaultConfig()
{
    FlexSettings *settings = staticFlexSettings;
    if (settings) {
        return settings->d_func()->config;
    }

    return YGConfigGetDefault();
}

int FlexSettingsPrivate::logger(YGConfigConstRef config, YGNodeConstRef node, YGLogLevel level, const char *format, va_list args)
{
    Q_UNUSED(config);
    Q_UNUSED(node);
    Q_UNUSED(args);

    switch (level) {
    case YGLogLevelFatal:
        qFatal("%s", format);
        break;
    case YGLogLevelError:
        qCritical("%s", format);
        break;
    case YGLogLevelWarn:
        qWarning("%s", format);
        break;
    case YGLogLevelInfo:
        qInfo("%s", format);
        break;
    case YGLogLevelDebug:
        qDebug("%s", format);
        break;
    case YGLogLevelVerbose:
        qDebug("%s", format);
        break;
    default:
        Q_UNREACHABLE();
    }

    return 0;
}
