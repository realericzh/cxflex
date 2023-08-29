#ifndef CXFLEX_P_H
#define CXFLEX_P_H

#include "yoga/Yoga.h"

#include "CxFlex.h"

class CxYogaNode
{
public:
    CxYogaNode();
    virtual ~CxYogaNode();

public:
    virtual const QLoggingCategory &loggingCategory() const = 0;

public:
    YGNodeRef makeNode();
    void cleanupNode();
public:
    virtual void initNode(YGNodeRef node);
    static CxYogaNode *context(YGNodeRef node);
    static void onDirtied(YGNodeRef node);
public:
    YGNodeRef node = nullptr;

public:
    virtual void buildLayout();
    virtual void applyLayout();

public:
    bool setPreferredWidth(const QJSValue &value);
    bool setPreferredHeight(const QJSValue &value);
public:
    QJSValue preferredWidth() const;
    QJSValue preferredHeight() const;

public:
    bool setMinimumWidth(const QJSValue &value);
    bool setMinimumHeight(const QJSValue &value);
    bool setMaximumWidth(const QJSValue &value);
    bool setMaximumHeight(const QJSValue &value);
public:
    QJSValue minimumWidth() const;
    QJSValue minimumHeight() const;
    QJSValue maximumWidth() const;
    QJSValue maximumHeight() const;

public:
    bool setMargin(YGEdge edge, const QJSValue &value);
    bool setPadding(YGEdge edge, const QJSValue &value);
    bool setBorder(YGEdge edge, const QJSValue &value);
public:
    QJSValue margin(YGEdge edge) const;
    QJSValue padding(YGEdge edge) const;
    QJSValue border(YGEdge edge) const;

public:
    bool setDirection(CxFlex::Direction value);
    bool setPosition(CxFlex::Position value);
    bool setDisplay(CxFlex::Display value);
    bool setOverflow(CxFlex::Overflow value);
public:
    CxFlex::Direction direction() const;
    CxFlex::Position position() const;
    CxFlex::Display display() const;
    CxFlex::Overflow overflow() const;

public:
    bool setPosition(YGEdge edge, const QJSValue &value);
public:
    QJSValue position(YGEdge edge) const;

public:
    bool setFlexDirection(CxFlex::FlexDirection value);
    bool setJustifyContent(CxFlex::Justify value);
    bool setAlignContent(CxFlex::Align value);
    bool setAlignItems(CxFlex::Align value);
    bool setAlignSelf(CxFlex::Align value);
    bool setFlexWrap(CxFlex::Wrap value);
public:
    CxFlex::FlexDirection flexDirection() const;
    CxFlex::Justify justifyContent() const;
    CxFlex::Align alignContent() const;
    CxFlex::Align alignItems() const;
    CxFlex::Align alignSelf() const;
    CxFlex::Wrap flexWrap() const;

public:
    bool setGap(YGGutter gutter, const QJSValue &value);
public:
    QJSValue gap(YGGutter gutter) const;

public:
    bool setFlex(const QJSValue &value);
    bool setFlexGrow(const QJSValue &value);
    bool setFlexBasis(const QJSValue &value);
    bool setFlexShrink(const QJSValue &value);
public:
    QJSValue flex() const;
    QJSValue flexGrow() const;
    QJSValue flexBasis() const;
    QJSValue flexShrink() const;

public:
    bool setAspectRatio(const QJSValue &value);
public:
    QJSValue aspectRatio() const;
};

#endif // CXFLEX_P_H
