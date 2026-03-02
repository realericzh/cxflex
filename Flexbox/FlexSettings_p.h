#ifndef FLEXSETTINGS_P_H
#define FLEXSETTINGS_P_H

#include "yoga/YGConfig.h"

#include "FlexSettings.h"

class FlexSettingsPrivate
{
    Q_DECLARE_PUBLIC(FlexSettings)

protected:
    FlexSettings *q_ptr = nullptr;

public:
    static FlexSettingsPrivate *get(FlexSettings *o) { return o ? o->d_func() : nullptr; }
    static const FlexSettingsPrivate *get(const FlexSettings *o) { return o ? o->d_func() : nullptr; }

public:
    YGConfigRef makeConfig() { return config; }
    static YGConfigConstRef defaultConfig();
protected:
    YGConfigRef config = nullptr;

protected:
    static int logger(YGConfigConstRef config, YGNodeConstRef node, YGLogLevel level, const char *format, va_list args);
};

#endif // FLEXSETTINGS_P_H
