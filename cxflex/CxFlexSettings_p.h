#ifndef CXFLEXSETTINGS_P_H
#define CXFLEXSETTINGS_P_H

#include "yoga/Yoga.h"

#include "CxFlexSettings.h"

class CxFlexSettingsPrivate
{
    Q_DECLARE_PUBLIC(CxFlexSettings)

public:
    CxFlexSettingsPrivate();
    virtual ~CxFlexSettingsPrivate();
protected:
    CxFlexSettings *q_ptr;

public:
    static CxFlexSettingsPrivate *get(CxFlexSettings *o) { return o ? o->d_func() : nullptr; }
    static const CxFlexSettingsPrivate *get(const CxFlexSettings *o) { return o ? o->d_func() : nullptr; }

public:
    YGConfigRef makeConfig() { return config; }
    static YGConfigRef defaultConfig();
protected:
    YGConfigRef config = nullptr;

protected:
    static int logger(YGConfigRef config, YGNodeRef node, YGLogLevel level, const char* format, va_list args);
};

#endif // CXFLEXSETTINGS_P_H
