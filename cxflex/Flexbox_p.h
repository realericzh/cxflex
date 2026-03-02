#ifndef REALERICZH_FLEXBOX_P_H
#define REALERICZH_FLEXBOX_P_H

#include <private/qquickitemchangelistener_p.h>

#include "yoga/Yoga.h"

#include "Flexbox.h"

class FlexboxAttachedPrivate : public QQuickItemChangeListener
{
    Q_DECLARE_PUBLIC(FlexboxAttached)

public:
    FlexboxAttachedPrivate();
    virtual ~FlexboxAttachedPrivate();
protected:
    FlexboxAttached *q_ptr;

protected:
    QQuickItem *item = nullptr;
    QQuickItemPrivate *itemd = nullptr;

protected:
    enum SizeType {
        UnknownSize,
        GeometrySize,
        ImplicitSize,
    };
protected:
    SizeType sizeType = UnknownSize;

protected:
    void itemGeometryChanged(QQuickItem *, QQuickGeometryChange, const QRectF & /* oldGeometry */) final;

    void itemChildAdded(QQuickItem *, QQuickItem *child) final;
    void itemChildRemoved(QQuickItem *, QQuickItem *child) final;
    void itemParentChanged(QQuickItem *, QQuickItem *parent) final;

    void itemVisibilityChanged(QQuickItem *item) final;
    void itemOpacityChanged(QQuickItem *) final;

    QAtomicInt pending;

    bool debug = false;

public:
    static FlexboxAttachedPrivate *context(YGNodeConstRef node);
    static void onDirtied(YGNodeConstRef node);
public:
    YGNodeRef node = nullptr;

public:
    void buildLayout();
    void calculateLayout();
    void applyLayout();

public:
    bool setMargin(YGEdge edge, QJSValue value);
    bool setPadding(YGEdge edge, QJSValue value);
    bool setBorder(YGEdge edge, QJSValue value);
public:
    QJSValue margin(YGEdge edge) const;
    QJSValue padding(YGEdge edge) const;
    QJSValue border(YGEdge edge) const;

public:
    bool setPosition(YGEdge edge, QJSValue value);
public:
    QJSValue position(YGEdge edge) const;

public:
    bool setGap(YGGutter gutter, QJSValue value);
public:
    QJSValue gap(YGGutter gutter) const;
};

#endif // REALERICZH_FLEXBOX_P_H
