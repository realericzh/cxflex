#ifndef CXFLEXITEM_P_H
#define CXFLEXITEM_P_H

#include "CxFlex_p.h"
#include "CxFlexItem.h"

// class CxFlexItemPrivate

class CxFlexItemPrivate : public CxYogaNode
{
    Q_DECLARE_PUBLIC(CxFlexItem)

public:
    const QLoggingCategory &loggingCategory() const override;

public:
    CxFlexItemPrivate();
    virtual ~CxFlexItemPrivate();
protected:
    CxFlexItem *q_ptr;

protected:
    void buildLayout() override;
    void calculateLayout();
    void applyLayout() override;
protected:
    bool root = false;
    QAtomicInt pending;
};

// class CxFlexColumnPrivate

class CxFlexColumnPrivate : public CxFlexItemPrivate
{
    Q_DECLARE_PUBLIC(CxFlexColumn)

public:
    const QLoggingCategory &loggingCategory() const final;

protected:
    void initNode(YGNodeRef node) override;
};

// class CxFlexColumnReversePrivate

class CxFlexColumnReversePrivate : public CxFlexItemPrivate
{
    Q_DECLARE_PUBLIC(CxFlexColumnReverse)

public:
    const QLoggingCategory &loggingCategory() const final;

protected:
    void initNode(YGNodeRef node) override;
};

// class CxFlexRowPrivate

class CxFlexRowPrivate : public CxFlexItemPrivate
{
    Q_DECLARE_PUBLIC(CxFlexRow)

public:
    const QLoggingCategory &loggingCategory() const final;

protected:
    void initNode(YGNodeRef node) override;
};

// class CxFlexRowReversePrivate

class CxFlexRowReversePrivate : public CxFlexItemPrivate
{
    Q_DECLARE_PUBLIC(CxFlexRowReverse)

public:
    const QLoggingCategory &loggingCategory() const final;

protected:
    void initNode(YGNodeRef node) override;
};

#endif // CXFLEXITEM_P_H
