#ifndef REALERICZH_FLEXBOX_P_H
#define REALERICZH_FLEXBOX_P_H

#include <private/qquickitemchangelistener_p.h>

#include "yoga/YGNode.h"

#include "Flexbox.h"

class FlexboxAttachedPrivate : public QQuickItemChangeListener
{
    Q_DECLARE_PUBLIC(FlexboxAttached)

protected:
    FlexboxAttached *q_ptr = nullptr;

protected:
    void buildLayout();
    void applyLayout();
protected:
    YGNodeRef node = nullptr;

protected:
    void setPosition(YGEdge edge, QJSValue value);

    void setMargin(YGEdge edge, QJSValue value);
    void setPadding(YGEdge edge, QJSValue value);
    void setBorder(YGEdge edge, QJSValue value);

    void setGap(YGGutter gutter, QJSValue value);

protected:
    void itemGeometryChanged(QQuickItem *, QQuickGeometryChange, const QRectF &) final;

    void itemChildAdded(QQuickItem *, QQuickItem *child) final;
    void itemChildRemoved(QQuickItem *, QQuickItem *child) final;

    void itemVisibilityChanged(QQuickItem *) final;
    void itemOpacityChanged(QQuickItem *) final;
protected:
    QQuickItem *item = nullptr;

protected:
    enum SizeType {
        UnknownSize,
        GeometrySize,
        ImplicitSize,
    };
protected:
    SizeType sizeType = UnknownSize;

protected:
    void updateDisplay();
protected:
    bool autoDisplay = true;
};

#endif // REALERICZH_FLEXBOX_P_H
