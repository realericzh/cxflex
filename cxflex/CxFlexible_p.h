#ifndef CXFLEXIBLE_P_H
#define CXFLEXIBLE_P_H

#include "CxFlex_p.h"
#include "CxFlexible.h"

class CxFlexiblePrivate : public CxYogaNode
{
    Q_DECLARE_PUBLIC(CxFlexible)

public:
    const QLoggingCategory &loggingCategory() const final;

public:
    CxFlexiblePrivate();
    virtual ~CxFlexiblePrivate();
protected:
    CxFlexible *q_ptr;

protected:
    enum SizeType {
        UnknownSize,
        GeometrySize,
        ImplicitSize,
    };
protected:
    SizeType sizeType = UnknownSize;

protected:
    void applyLayout() override;
};

#endif // CXFLEXIBLE_P_H
