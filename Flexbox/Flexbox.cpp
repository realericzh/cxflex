#include "Flexbox.h"
#include "Flexbox_p.h"

#include <private/qquickitem_p.h>

#include "yoga/YGNodeStyle.h"
#include "yoga/YGNodeLayout.h"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(lcFlexbox, "Flexbox")

// FlexboxInternals

namespace FlexboxInlines {

inline QJSValue toJSValue(YGValue value)
{
    switch (value.unit) {
    case YGUnitUndefined:
        return {};
    case YGUnitPoint:
        return value.value;
    case YGUnitPercent:
        return QStringLiteral("%1%").arg(value.value);
    case YGUnitAuto:
        return QStringLiteral("auto");
    default:
        Q_UNREACHABLE();
    }
}

inline QJSValue toJSValue(float value)
{
    if (!YGFloatIsUndefined(value)) {
        return value;
    }

    return {};
}

} // namespace FlexboxInlines

// class Flexbox

FlexboxAttached *Flexbox::qmlAttachedProperties(QObject *attachee)
{
    return new FlexboxAttached(attachee);
}

// class FlexboxAttached

FlexboxAttached::FlexboxAttached(QObject *parent)
    : QObject{parent}
    , d_ptr{new FlexboxAttachedPrivate{}}
{
    d_ptr->q_ptr = this;

    Q_D(FlexboxAttached);

    d->node = YGNodeNewWithConfig(YGConfigGetDefault());
    if (d->node) {
        YGNodeSetContext(d->node, d);

        YGNodeSetDirtiedFunc(d->node, &FlexboxAttachedPrivate::onDirtied);
    }

    d->item = qobject_cast<QQuickItem *>(parent);
    if (d->item) {
        QQuickItemPrivate *itemd = QQuickItemPrivate::get(d->item);

        itemd->addItemChangeListener(d, QQuickItemPrivate::Geometry | QQuickItemPrivate::Visibility | QQuickItemPrivate::Children);

        for (QQuickItem *childItem : d->item->childItems()) {
            FlexboxAttached *attached = qobject_cast<FlexboxAttached *>(qmlAttachedPropertiesObject<Flexbox>(childItem, false));
            if (attached) {
                YGNodeRef childNode = attached->d_func()->node;
                if (childNode) {
                    const size_t index = YGNodeGetChildCount(d->node);
                    YGNodeInsertChild(d->node, childNode, index);
                }
            }
        }
    }
}

FlexboxAttached::~FlexboxAttached()
{
    Q_D(FlexboxAttached);

    if (d->item) {
        QQuickItemPrivate *itemd = QQuickItemPrivate::get(d->item);

        itemd->removeItemChangeListener(d, QQuickItemPrivate::Geometry | QQuickItemPrivate::Visibility | QQuickItemPrivate::Children);
    }

    if (d->node) {
        auto parentNode = YGNodeGetParent(d->node);
        if (parentNode) {
            YGNodeRemoveChild(parentNode, d->node);
        }

        YGNodeFree(d->node);
        d->node = nullptr;
    }
}

void FlexboxAttached::setDirection(Flexbox::Generic value)
{
    // https://www.yogalayout.dev/docs/styling/layout-direction

    Q_D(FlexboxAttached);

    const auto oldValue = YGNodeStyleGetDirection(d->node);

    switch (value) {
    case Flexbox::Inherit:
        YGNodeStyleSetDirection(d->node, YGDirectionInherit);
        break;
    case Flexbox::LTR:
        YGNodeStyleSetDirection(d->node, YGDirectionLTR);
        break;
    case Flexbox::RTL:
        YGNodeStyleSetDirection(d->node, YGDirectionRTL);
        break;
    default:
        qCWarning(lcFlexbox) << "Flexbox.direction: invalid value:" << value;
        Q_ASSERT_X(false, "Flexbox.direction", "invalid value");
        return;
    }

    if (oldValue != YGNodeStyleGetDirection(d->node)) {
        emit directionChanged();
    }
}

void FlexboxAttached::setPosition(Flexbox::Generic value)
{
    // https://www.yogalayout.dev/docs/styling/position

    Q_D(FlexboxAttached);

    const auto oldValue = YGNodeStyleGetPositionType(d->node);

    switch (value) {
    case Flexbox::Static:
        YGNodeStyleSetPositionType(d->node, YGPositionTypeStatic);
        break;
    case Flexbox::Relative:
        YGNodeStyleSetPositionType(d->node, YGPositionTypeRelative);
        break;
    case Flexbox::Absolute:
        YGNodeStyleSetPositionType(d->node, YGPositionTypeAbsolute);
        break;
    default:
        qCWarning(lcFlexbox) << "Flexbox.position: invalid value:" << value;
        Q_ASSERT_X(false, "Flexbox.position", "invalid value");
        return;
    }

    if (oldValue != YGNodeStyleGetPositionType(d->node)) {
        emit positionChanged();
    }
}

void FlexboxAttached::setDisplay(Flexbox::Generic value)
{
    // https://www.yogalayout.dev/docs/styling/display

    Q_D(FlexboxAttached);

    const auto oldValue = YGNodeStyleGetDisplay(d->node);

    switch (value) {
    case Flexbox::Flex:
        YGNodeStyleSetDisplay(d->node, YGDisplayFlex);
        break;
    case Flexbox::None:
        YGNodeStyleSetDisplay(d->node, YGDisplayNone);
        break;
    case Flexbox::Contents:
        YGNodeStyleSetDisplay(d->node, YGDisplayContents);
        break;
    default:
        qCWarning(lcFlexbox) << "Flexbox.display: invalid value:" << value;
        Q_ASSERT_X(false, "Flexbox.display", "invalid value");
        return;
    }

    if (oldValue != YGNodeStyleGetDisplay(d->node)) {
        emit displayChanged();
    }
}

void FlexboxAttached::setOverflow(Flexbox::Generic value)
{
    // no document

    Q_D(FlexboxAttached);

    const auto oldValue = YGNodeStyleGetOverflow(d->node);

    switch (value) {
    case Flexbox::Visible:
        YGNodeStyleSetOverflow(d->node, YGOverflowVisible);
        break;
    case Flexbox::Hidden:
        YGNodeStyleSetOverflow(d->node, YGOverflowHidden);
        break;
    case Flexbox::Scroll:
        YGNodeStyleSetOverflow(d->node, YGOverflowScroll);
        break;
    default:
        qCWarning(lcFlexbox) << "Flexbox.overflow: invalid value:" << value;
        Q_ASSERT_X(false, "Flexbox.overflow", "invalid value");
        return;
    }

    if (oldValue != YGNodeStyleGetOverflow(d->node)) {
        emit overflowChanged();
    }
}

void FlexboxAttached::setBoxSizing(Flexbox::Generic value)
{
    // https://www.yogalayout.dev/blog/announcing-yoga-3.2

    Q_D(FlexboxAttached);

    const auto oldValue = YGNodeStyleGetBoxSizing(d->node);

    switch (value) {
    case Flexbox::BorderBox:
        YGNodeStyleSetBoxSizing(d->node, YGBoxSizingBorderBox);
        break;
    case Flexbox::ContentBox:
        YGNodeStyleSetBoxSizing(d->node, YGBoxSizingContentBox);
        break;
    default:
        qCWarning(lcFlexbox) << "Flexbox.boxSizing: invalid value:" << value;
        Q_ASSERT_X(false, "Flexbox.boxSizing", "invalid value");
        return;
    }

    if (oldValue != YGNodeStyleGetBoxSizing(d->node)) {
        emit boxSizingChanged();
    }
}

Flexbox::Generic FlexboxAttached::direction() const
{
    switch (YGNodeStyleGetDirection(d_func()->node)) {
    case YGDirectionInherit:
        return Flexbox::Inherit;
    case YGDirectionLTR:
        return Flexbox::LTR;
    case YGDirectionRTL:
        return Flexbox::RTL;
    default:
        Q_UNREACHABLE();
    }
}

Flexbox::Generic FlexboxAttached::position() const
{
    switch (YGNodeStyleGetPositionType(d_func()->node)) {
    case YGPositionTypeStatic:
        return Flexbox::Static;
    case YGPositionTypeRelative:
        return Flexbox::Relative;
    case YGPositionTypeAbsolute:
        return Flexbox::Absolute;
    default:
        Q_UNREACHABLE();
    }
}

Flexbox::Generic FlexboxAttached::display() const
{
    switch (YGNodeStyleGetDisplay(d_func()->node)) {
    case YGDisplayFlex:
        return Flexbox::Flex;
    case YGDisplayNone:
        return Flexbox::None;
    case YGDisplayContents:
        return Flexbox::Contents;
    default:
        Q_UNREACHABLE();
    }
}

Flexbox::Generic FlexboxAttached::overflow() const
{
    switch (YGNodeStyleGetOverflow(d_func()->node)) {
    case YGOverflowVisible:
        return Flexbox::Visible;
    case YGOverflowHidden:
        return Flexbox::Hidden;
    case YGOverflowScroll:
        return Flexbox::Scroll;
    default:
        Q_UNREACHABLE();
    }
}

Flexbox::Generic FlexboxAttached::boxSizing() const
{
    switch (YGNodeStyleGetBoxSizing(d_func()->node)) {
    case YGBoxSizingBorderBox:
        return Flexbox::BorderBox;
    case YGBoxSizingContentBox:
        return Flexbox::ContentBox;
    default:
        Q_UNREACHABLE();
    }
}

void FlexboxAttached::setJustifyContent(Flexbox::Generic value)
{
    // https://www.yogalayout.dev/docs/styling/justify-content

    Q_D(FlexboxAttached);

    const auto oldValue = YGNodeStyleGetJustifyContent(d->node);

    switch (value) {
    case Flexbox::FlexStart:
        YGNodeStyleSetJustifyContent(d->node, YGJustifyFlexStart);
        break;
    case Flexbox::Center:
        YGNodeStyleSetJustifyContent(d->node, YGJustifyCenter);
        break;
    case Flexbox::FlexEnd:
        YGNodeStyleSetJustifyContent(d->node, YGJustifyFlexEnd);
        break;
    case Flexbox::SpaceBetween:
        YGNodeStyleSetJustifyContent(d->node, YGJustifySpaceBetween);
        break;
    case Flexbox::SpaceAround:
        YGNodeStyleSetJustifyContent(d->node, YGJustifySpaceAround);
        break;
    case Flexbox::SpaceEvenly:
        YGNodeStyleSetJustifyContent(d->node, YGJustifySpaceEvenly);
        break;
    default:
        qCWarning(lcFlexbox) << "Flexbox.justifyContent: invalid value:" << value;
        Q_ASSERT_X(false, "Flexbox.justifyContent", "invalid value");
        return;
    }

    if (oldValue != YGNodeStyleGetJustifyContent(d->node)) {
        emit justifyContentChanged();
    }
}

void FlexboxAttached::setFlexDirection(Flexbox::Generic value)
{
    // https://www.yogalayout.dev/docs/styling/flex-direction

    Q_D(FlexboxAttached);

    const auto oldValue = YGNodeStyleGetFlexDirection(d->node);

    switch (value) {
    case Flexbox::Column:
        YGNodeStyleSetFlexDirection(d->node, YGFlexDirectionColumn);
        break;
    case Flexbox::ColumnReverse:
        YGNodeStyleSetFlexDirection(d->node, YGFlexDirectionColumnReverse);
        break;
    case Flexbox::Row:
        YGNodeStyleSetFlexDirection(d->node, YGFlexDirectionRow);
        break;
    case Flexbox::RowReverse:
        YGNodeStyleSetFlexDirection(d->node, YGFlexDirectionRowReverse);
        break;
    default:
        qCWarning(lcFlexbox) << "Flexbox.flexDirection: invalid value:" << value;
        Q_ASSERT_X(false, "Flexbox.flexDirection", "invalid value");
        return;
    }

    if (oldValue != YGNodeStyleGetFlexDirection(d->node)) {
        emit flexDirectionChanged();
    }
}

void FlexboxAttached::setAlignContent(Flexbox::Generic value)
{
    // https://www.yogalayout.dev/docs/styling/align-content

    Q_D(FlexboxAttached);

    const auto oldValue = YGNodeStyleGetAlignContent(d->node);

    switch (value) {
    case Flexbox::Auto:
        YGNodeStyleSetAlignContent(d->node, YGAlignAuto);
        break;
    case Flexbox::FlexStart:
        YGNodeStyleSetAlignContent(d->node, YGAlignFlexStart);
        break;
    case Flexbox::Center:
        YGNodeStyleSetAlignContent(d->node, YGAlignCenter);
        break;
    case Flexbox::FlexEnd:
        YGNodeStyleSetAlignContent(d->node, YGAlignFlexEnd);
        break;
    case Flexbox::Stretch:
        YGNodeStyleSetAlignContent(d->node, YGAlignStretch);
        break;
    case Flexbox::Baseline:
        YGNodeStyleSetAlignContent(d->node, YGAlignBaseline);
        break;
    case Flexbox::SpaceBetween:
        YGNodeStyleSetAlignContent(d->node, YGAlignSpaceBetween);
        break;
    case Flexbox::SpaceAround:
        YGNodeStyleSetAlignContent(d->node, YGAlignSpaceAround);
        break;
    case Flexbox::SpaceEvenly:
        YGNodeStyleSetAlignContent(d->node, YGAlignSpaceEvenly);
        break;
    default:
        qCWarning(lcFlexbox) << "Flexbox.alignContent: invalid value:" << value;
        Q_ASSERT_X(false, "Flexbox.alignContent", "invalid value");
        return;
    }

    if (oldValue != YGNodeStyleGetAlignContent(d->node)) {
        emit alignContentChanged();
    }
}

void FlexboxAttached::setAlignItems(Flexbox::Generic value)
{
    // https://www.yogalayout.dev/docs/styling/align-items-self

    Q_D(FlexboxAttached);

    const auto oldValue = YGNodeStyleGetAlignItems(d->node);

    switch (value) {
        /*
    case Flexbox::Auto:
        YGNodeStyleSetAlignItems(d->node, YGAlignAuto);
        break;
        */
    case Flexbox::FlexStart:
        YGNodeStyleSetAlignItems(d->node, YGAlignFlexStart);
        break;
    case Flexbox::Center:
        YGNodeStyleSetAlignItems(d->node, YGAlignCenter);
        break;
    case Flexbox::FlexEnd:
        YGNodeStyleSetAlignItems(d->node, YGAlignFlexEnd);
        break;
    case Flexbox::Stretch:
        YGNodeStyleSetAlignItems(d->node, YGAlignStretch);
        break;
    case Flexbox::Baseline:
        YGNodeStyleSetAlignItems(d->node, YGAlignBaseline);
        break;
        /*
    case Flexbox::SpaceBetween:
        YGNodeStyleSetAlignItems(d->node, YGAlignSpaceBetween);
        break;
    case Flexbox::SpaceAround:
        YGNodeStyleSetAlignItems(d->node, YGAlignSpaceAround);
        break;
    case Flexbox::SpaceEvenly:
        YGNodeStyleSetAlignItems(d->node, YGAlignSpaceEvenly);
        break;
        */
    default:
        qCWarning(lcFlexbox) << "Flexbox.alignItems: invalid value:" << value;
        Q_ASSERT_X(false, "Flexbox.alignItems", "invalid value");
        return;
    }

    if (oldValue != YGNodeStyleGetAlignItems(d->node)) {
        emit alignItemsChanged();
    }
}

void FlexboxAttached::setAlignSelf(Flexbox::Generic value)
{
    // https://www.yogalayout.dev/docs/styling/align-items-self

    Q_D(FlexboxAttached);

    const auto oldValue = YGNodeStyleGetAlignSelf(d->node);

    switch (value) {
    case Flexbox::Auto:
        YGNodeStyleSetAlignSelf(d->node, YGAlignAuto);
        break;
    case Flexbox::FlexStart:
        YGNodeStyleSetAlignSelf(d->node, YGAlignFlexStart);
        break;
    case Flexbox::Center:
        YGNodeStyleSetAlignSelf(d->node, YGAlignCenter);
        break;
    case Flexbox::FlexEnd:
        YGNodeStyleSetAlignSelf(d->node, YGAlignFlexEnd);
        break;
    case Flexbox::Stretch:
        YGNodeStyleSetAlignSelf(d->node, YGAlignStretch);
        break;
    case Flexbox::Baseline:
        YGNodeStyleSetAlignSelf(d->node, YGAlignBaseline);
        break;
    case Flexbox::SpaceBetween:
        YGNodeStyleSetAlignSelf(d->node, YGAlignSpaceBetween);
        break;
    case Flexbox::SpaceAround:
        YGNodeStyleSetAlignSelf(d->node, YGAlignSpaceAround);
        break;
    case Flexbox::SpaceEvenly:
        YGNodeStyleSetAlignSelf(d->node, YGAlignSpaceEvenly);
        break;
    default:
        qCWarning(lcFlexbox) << "Flexbox.alignSelf: invalid value:" << value;
        Q_ASSERT_X(false, "Flexbox.alignSelf", "invalid value");
        return;
    }

    if (oldValue != YGNodeStyleGetAlignSelf(d->node)) {
        emit alignSelfChanged();
    }
}

void FlexboxAttached::setFlexWrap(Flexbox::Generic value)
{
    // https://www.yogalayout.dev/docs/styling/flex-wrap

    Q_D(FlexboxAttached);

    const auto oldValue = YGNodeStyleGetFlexWrap(d->node);

    switch (value) {
    case Flexbox::NoWrap:
        YGNodeStyleSetFlexWrap(d->node, YGWrapNoWrap);
        break;
    case Flexbox::Wrap:
        YGNodeStyleSetFlexWrap(d->node, YGWrapWrap);
        break;
    case Flexbox::WrapReverse:
        YGNodeStyleSetFlexWrap(d->node, YGWrapWrapReverse);
        break;
    default:
        qCWarning(lcFlexbox) << "Flexbox.flexWrap: invalid value:" << value;
        Q_ASSERT_X(false, "Flexbox.flexWrap", "invalid value");
        return;
    }

    if (oldValue != YGNodeStyleGetFlexWrap(d->node)) {
        emit flexWrapChanged();
    }
}

Flexbox::Generic FlexboxAttached::justifyContent() const
{
    switch (YGNodeStyleGetJustifyContent(d_func()->node)) {
    case YGJustifyFlexStart:
        return Flexbox::FlexStart;
    case YGJustifyCenter:
        return Flexbox::Center;
    case YGJustifyFlexEnd:
        return Flexbox::FlexEnd;
    case YGJustifySpaceBetween:
        return Flexbox::SpaceBetween;
    case YGJustifySpaceAround:
        return Flexbox::SpaceAround;
    case YGJustifySpaceEvenly:
        return Flexbox::SpaceEvenly;
    default:
        Q_UNREACHABLE();
    }
}

Flexbox::Generic FlexboxAttached::flexDirection() const
{
    switch (YGNodeStyleGetFlexDirection(d_func()->node)) {
    case YGFlexDirectionColumn:
        return Flexbox::Column;
    case YGFlexDirectionColumnReverse:
        return Flexbox::ColumnReverse;
    case YGFlexDirectionRow:
        return Flexbox::Row;
    case YGFlexDirectionRowReverse:
        return Flexbox::RowReverse;
    default:
        Q_UNREACHABLE();
    }
}

Flexbox::Generic FlexboxAttached::alignContent() const
{
    switch (YGNodeStyleGetAlignContent(d_func()->node)) {
    case YGAlignAuto:
        return Flexbox::Auto;
    case YGAlignFlexStart:
        return Flexbox::FlexStart;
    case YGAlignCenter:
        return Flexbox::Center;
    case YGAlignFlexEnd:
        return Flexbox::FlexEnd;
    case YGAlignStretch:
        return Flexbox::Stretch;
    case YGAlignBaseline:
        return Flexbox::Baseline;
    case YGAlignSpaceBetween:
        return Flexbox::SpaceBetween;
    case YGAlignSpaceAround:
        return Flexbox::SpaceAround;
    case YGAlignSpaceEvenly:
        return Flexbox::SpaceEvenly;
    default:
        Q_UNREACHABLE();
    }
}

Flexbox::Generic FlexboxAttached::alignItems() const
{
    switch (YGNodeStyleGetAlignItems(d_func()->node)) {
        /*
    case YGAlignAuto:
        return Flexbox::Auto;
        */
    case YGAlignFlexStart:
        return Flexbox::FlexStart;
    case YGAlignCenter:
        return Flexbox::Center;
    case YGAlignFlexEnd:
        return Flexbox::FlexEnd;
    case YGAlignStretch:
        return Flexbox::Stretch;
    case YGAlignBaseline:
        return Flexbox::Baseline;
        /*
    case YGAlignSpaceBetween:
        return Flexbox::SpaceBetween;
    case YGAlignSpaceAround:
        return Flexbox::SpaceAround;
    case YGAlignSpaceEvenly:
        return Flexbox::SpaceEvenly;
        */
    default:
        Q_UNREACHABLE();
    }
}

Flexbox::Generic FlexboxAttached::alignSelf() const
{
    switch (YGNodeStyleGetAlignSelf(d_func()->node)) {
    case YGAlignAuto:
        return Flexbox::Auto;
    case YGAlignFlexStart:
        return Flexbox::FlexStart;
    case YGAlignCenter:
        return Flexbox::Center;
    case YGAlignFlexEnd:
        return Flexbox::FlexEnd;
    case YGAlignStretch:
        return Flexbox::Stretch;
    case YGAlignBaseline:
        return Flexbox::Baseline;
    case YGAlignSpaceBetween:
        return Flexbox::SpaceBetween;
    case YGAlignSpaceAround:
        return Flexbox::SpaceAround;
    case YGAlignSpaceEvenly:
        return Flexbox::SpaceEvenly;
    default:
        Q_UNREACHABLE();
    }
}

Flexbox::Generic FlexboxAttached::flexWrap() const
{
    switch (YGNodeStyleGetFlexWrap(d_func()->node)) {
    case YGWrapNoWrap:
        return Flexbox::NoWrap;
    case YGWrapWrap:
        return Flexbox::Wrap;
    case YGWrapWrapReverse:
        return Flexbox::WrapReverse;
    default:
        Q_UNREACHABLE();
    }
}

void FlexboxAttached::setLeft(QJSValue value)
{
    d_func()->setPosition(YGEdgeLeft, value);
}

void FlexboxAttached::setTop(QJSValue value)
{
    d_func()->setPosition(YGEdgeTop, value);
}

void FlexboxAttached::setRight(QJSValue value)
{
    d_func()->setPosition(YGEdgeRight, value);
}

void FlexboxAttached::setBottom(QJSValue value)
{
    d_func()->setPosition(YGEdgeBottom, value);
}

void FlexboxAttached::setStart(QJSValue value)
{
    d_func()->setPosition(YGEdgeStart, value);
}

void FlexboxAttached::setEnd(QJSValue value)
{
    d_func()->setPosition(YGEdgeEnd, value);
}

QJSValue FlexboxAttached::left() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetPosition(d_func()->node, YGEdgeLeft));
}

QJSValue FlexboxAttached::top() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetPosition(d_func()->node, YGEdgeTop));
}

QJSValue FlexboxAttached::right() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetPosition(d_func()->node, YGEdgeRight));
}

QJSValue FlexboxAttached::bottom() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetPosition(d_func()->node, YGEdgeBottom));
}

QJSValue FlexboxAttached::start() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetPosition(d_func()->node, YGEdgeStart));
}

QJSValue FlexboxAttached::end() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetPosition(d_func()->node, YGEdgeEnd));
}

void FlexboxAttached::setWidth(QJSValue value)
{
    // https://www.yogalayout.dev/docs/styling/width-height

    Q_D(FlexboxAttached);

    const auto oldValue = YGNodeStyleGetWidth(d->node);

    if (value.isUndefined()) {
        YGNodeStyleSetWidth(d->node, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetWidth(d->node, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();
        if (valStr == QStringLiteral("auto")) {
            YGNodeStyleSetWidthAuto(d->node);
        } else {
            bool percent = false;
            if (valStr.endsWith('%')) {
                percent = true;
                valStr.chop(1);
            }

            bool ok = false;
            const auto val = valStr.toFloat(&ok);
            if (!ok) {
                qWarning(lcFlexbox, "invalid String value: %s", qUtf8Printable(value.toString()));
                return;
            }

            if (percent) {
                YGNodeStyleSetWidthPercent(d->node, val);
            } else {
                YGNodeStyleSetWidth(d->node, val);
            }
        }
    } else {
        qWarning(lcFlexbox, "invalid value: %s", qUtf8Printable(value.toString()));
        return;
    }

    if (oldValue != YGNodeStyleGetWidth(d->node)) {
        emit widthChanged();
    }
}

void FlexboxAttached::setHeight(QJSValue value)
{
    // https://www.yogalayout.dev/docs/styling/width-height

    Q_D(FlexboxAttached);

    const auto oldValue = YGNodeStyleGetHeight(d->node);

    if (value.isUndefined()) {
        YGNodeStyleSetHeight(d->node, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetHeight(d->node, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();
        if (valStr == QStringLiteral("auto")) {
            YGNodeStyleSetHeightAuto(d->node);
        } else {
            bool percent = false;
            if (valStr.endsWith('%')) {
                percent = true;
                valStr.chop(1);
            }

            bool ok = false;
            const auto val = valStr.toFloat(&ok);
            if (!ok) {
                qWarning(lcFlexbox, "invalid String value: %s", qUtf8Printable(value.toString()));
                return;
            }

            if (percent) {
                YGNodeStyleSetHeightPercent(d->node, val);
            } else {
                YGNodeStyleSetHeight(d->node, val);
            }
        }
    } else {
        qWarning(lcFlexbox, "invalid value: %s", qUtf8Printable(value.toString()));
        return;
    }

    if (oldValue != YGNodeStyleGetHeight(d->node)) {
        emit heightChanged();
    }
}

QJSValue FlexboxAttached::width() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetWidth(d_func()->node));
}

QJSValue FlexboxAttached::height() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetHeight(d_func()->node));
}

void FlexboxAttached::setMinimumWidth(QJSValue value)
{
    // https://www.yogalayout.dev/docs/styling/min-max-width-height

    Q_D(FlexboxAttached);

    const auto oldValue = YGNodeStyleGetMinWidth(d->node);

    if (value.isUndefined()) {
        YGNodeStyleSetMinWidth(d->node, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetMinWidth(d->node, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();

        bool percent = false;
        if (valStr.endsWith('%')) {
            percent = true;
            valStr.chop(1);
        }

        bool ok = false;
        const auto val = valStr.toFloat(&ok);
        if (!ok) {
            qWarning(lcFlexbox, "invalid String value: %s", qUtf8Printable(value.toString()));
            return;
        }

        if (percent) {
            YGNodeStyleSetMinWidthPercent(d->node, val);
        } else {
            YGNodeStyleSetMinWidth(d->node, val);
        }
    } else {
        qWarning(lcFlexbox, "invalid value: %s", qUtf8Printable(value.toString()));
        return;
    }

    if (oldValue != YGNodeStyleGetMinWidth(d->node)) {
        emit minimumWidthChanged();
    }
}

void FlexboxAttached::setMinimumHeight(QJSValue value)
{
    // https://www.yogalayout.dev/docs/styling/min-max-width-height

    Q_D(FlexboxAttached);

    const auto oldValue = YGNodeStyleGetMinHeight(d->node);

    if (value.isUndefined()) {
        YGNodeStyleSetMinHeight(d->node, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetMinHeight(d->node, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();

        bool percent = false;
        if (valStr.endsWith('%')) {
            percent = true;
            valStr.chop(1);
        }

        bool ok = false;
        const auto val = valStr.toFloat(&ok);
        if (!ok) {
            qWarning(lcFlexbox, "invalid String value: %s", qUtf8Printable(value.toString()));
            return;
        }

        if (percent) {
            YGNodeStyleSetMinHeightPercent(d->node, val);
        } else {
            YGNodeStyleSetMinHeight(d->node, val);
        }
    } else {
        qWarning(lcFlexbox, "invalid value: %s", qUtf8Printable(value.toString()));
        return;
    }

    if (oldValue != YGNodeStyleGetMinHeight(d->node)) {
        emit minimumHeightChanged();
    }
}

void FlexboxAttached::setMaximumWidth(QJSValue value)
{
    // https://www.yogalayout.dev/docs/styling/min-max-width-height

    Q_D(FlexboxAttached);

    const auto oldValue = YGNodeStyleGetMaxWidth(d->node);

    if (value.isUndefined()) {
        YGNodeStyleSetMaxWidth(d->node, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetMaxWidth(d->node, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();

        bool percent = false;
        if (valStr.endsWith('%')) {
            percent = true;
            valStr.chop(1);
        }

        bool ok = false;
        const auto val = valStr.toFloat(&ok);
        if (!ok) {
            qWarning(lcFlexbox, "invalid String value: %s", qUtf8Printable(value.toString()));
            return;
        }

        if (percent) {
            YGNodeStyleSetMaxWidthPercent(d->node, val);
        } else {
            YGNodeStyleSetMaxWidth(d->node, val);
        }
    } else {
        qWarning(lcFlexbox, "invalid value: %s", qUtf8Printable(value.toString()));
        return;
    }

    if (oldValue != YGNodeStyleGetMaxWidth(d->node)) {
        emit maximumWidthChanged();
    }
}

void FlexboxAttached::setMaximumHeight(QJSValue value)
{
    // https://www.yogalayout.dev/docs/styling/min-max-width-height

    Q_D(FlexboxAttached);

    const auto oldValue = YGNodeStyleGetMaxHeight(d->node);

    if (value.isUndefined()) {
        YGNodeStyleSetMaxHeight(d->node, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetMaxHeight(d->node, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();

        bool percent = false;
        if (valStr.endsWith('%')) {
            percent = true;
            valStr.chop(1);
        }

        bool ok = false;
        const auto val = valStr.toFloat(&ok);
        if (!ok) {
            qWarning(lcFlexbox, "invalid String value: %s", qUtf8Printable(value.toString()));
            return;
        }

        if (percent) {
            YGNodeStyleSetMaxHeightPercent(d->node, val);
        } else {
            YGNodeStyleSetMaxHeight(d->node, val);
        }
    } else {
        qWarning(lcFlexbox, "invalid value: %s", qUtf8Printable(value.toString()));
        return;
    }

    if (oldValue != YGNodeStyleGetMaxHeight(d->node)) {
        emit maximumHeightChanged();
    }
}

QJSValue FlexboxAttached::minimumWidth() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetMinWidth(d_func()->node));
}

QJSValue FlexboxAttached::minimumHeight() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetMinHeight(d_func()->node));
}

QJSValue FlexboxAttached::maximumWidth() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetMaxWidth(d_func()->node));
}

QJSValue FlexboxAttached::maximumHeight() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetMaxHeight(d_func()->node));
}

void FlexboxAttached::setLeftMargin(QJSValue value)
{
    d_func()->setMargin(YGEdgeLeft, value);
}

void FlexboxAttached::setTopMargin(QJSValue value)
{
    d_func()->setMargin(YGEdgeTop, value);
}

void FlexboxAttached::setRightMargin(QJSValue value)
{
    d_func()->setMargin(YGEdgeRight, value);
}

void FlexboxAttached::setBottomMargin(QJSValue value)
{
    d_func()->setMargin(YGEdgeBottom, value);
}

void FlexboxAttached::setStartMargin(QJSValue value)
{
    d_func()->setMargin(YGEdgeStart, value);
}

void FlexboxAttached::setEndMargin(QJSValue value)
{
    d_func()->setMargin(YGEdgeEnd, value);
}

void FlexboxAttached::setHorizontalMargin(QJSValue value)
{
    d_func()->setMargin(YGEdgeHorizontal, value);
}

void FlexboxAttached::setVerticalMargin(QJSValue value)
{
    d_func()->setMargin(YGEdgeVertical, value);
}

void FlexboxAttached::setMargins(QJSValue value)
{
    d_func()->setMargin(YGEdgeAll, value);
}

QJSValue FlexboxAttached::leftMargin() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetMargin(d_func()->node, YGEdgeLeft));
}

QJSValue FlexboxAttached::topMargin() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetMargin(d_func()->node, YGEdgeTop));
}

QJSValue FlexboxAttached::rightMargin() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetMargin(d_func()->node, YGEdgeRight));
}

QJSValue FlexboxAttached::bottomMargin() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetMargin(d_func()->node, YGEdgeBottom));
}

QJSValue FlexboxAttached::startMargin() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetMargin(d_func()->node, YGEdgeStart));
}

QJSValue FlexboxAttached::endMargin() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetMargin(d_func()->node, YGEdgeEnd));
}

QJSValue FlexboxAttached::horizontalMargin() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetMargin(d_func()->node, YGEdgeHorizontal));
}

QJSValue FlexboxAttached::verticalMargin() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetMargin(d_func()->node, YGEdgeVertical));
}

QJSValue FlexboxAttached::margins() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetMargin(d_func()->node, YGEdgeAll));
}

void FlexboxAttached::setLeftPadding(QJSValue value)
{
    d_func()->setPadding(YGEdgeLeft, value);
}

void FlexboxAttached::setTopPadding(QJSValue value)
{
    d_func()->setPadding(YGEdgeTop, value);
}

void FlexboxAttached::setRightPadding(QJSValue value)
{
    d_func()->setPadding(YGEdgeRight, value);
}

void FlexboxAttached::setBottomPadding(QJSValue value)
{
    d_func()->setPadding(YGEdgeBottom, value);
}

void FlexboxAttached::setStartPadding(QJSValue value)
{
    d_func()->setPadding(YGEdgeStart, value);
}

void FlexboxAttached::setEndPadding(QJSValue value)
{
    d_func()->setPadding(YGEdgeEnd, value);
}

void FlexboxAttached::setHorizontalPadding(QJSValue value)
{
    d_func()->setPadding(YGEdgeHorizontal, value);
}

void FlexboxAttached::setVerticalPadding(QJSValue value)
{
    d_func()->setPadding(YGEdgeVertical, value);
}

void FlexboxAttached::setPadding(QJSValue value)
{
    d_func()->setPadding(YGEdgeAll, value);
}

QJSValue FlexboxAttached::leftPadding() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetPadding(d_func()->node, YGEdgeLeft));
}

QJSValue FlexboxAttached::topPadding() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetPadding(d_func()->node, YGEdgeTop));
}

QJSValue FlexboxAttached::rightPadding() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetPadding(d_func()->node, YGEdgeRight));
}

QJSValue FlexboxAttached::bottomPadding() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetPadding(d_func()->node, YGEdgeBottom));
}

QJSValue FlexboxAttached::startPadding() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetPadding(d_func()->node, YGEdgeStart));
}

QJSValue FlexboxAttached::endPadding() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetPadding(d_func()->node, YGEdgeEnd));
}

QJSValue FlexboxAttached::horizontalPadding() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetPadding(d_func()->node, YGEdgeHorizontal));
}

QJSValue FlexboxAttached::verticalPadding() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetPadding(d_func()->node, YGEdgeVertical));
}

QJSValue FlexboxAttached::padding() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetPadding(d_func()->node, YGEdgeAll));
}

void FlexboxAttached::setLeftBorder(QJSValue value)
{
    d_func()->setBorder(YGEdgeLeft, value);
}

void FlexboxAttached::setTopBorder(QJSValue value)
{
    d_func()->setBorder(YGEdgeTop, value);
}

void FlexboxAttached::setRightBorder(QJSValue value)
{
    d_func()->setBorder(YGEdgeRight, value);
}

void FlexboxAttached::setBottomBorder(QJSValue value)
{
    d_func()->setBorder(YGEdgeBottom, value);
}

void FlexboxAttached::setStartBorder(QJSValue value)
{
    d_func()->setBorder(YGEdgeStart, value);
}

void FlexboxAttached::setEndBorder(QJSValue value)
{
    d_func()->setBorder(YGEdgeEnd, value);
}

void FlexboxAttached::setHorizontalBorder(QJSValue value)
{
    d_func()->setBorder(YGEdgeHorizontal, value);
}

void FlexboxAttached::setVerticalBorder(QJSValue value)
{
    d_func()->setBorder(YGEdgeVertical, value);
}

void FlexboxAttached::setBorders(QJSValue value)
{
    d_func()->setBorder(YGEdgeAll, value);
}

QJSValue FlexboxAttached::leftBorder() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetBorder(d_func()->node, YGEdgeLeft));
}

QJSValue FlexboxAttached::topBorder() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetBorder(d_func()->node, YGEdgeTop));
}

QJSValue FlexboxAttached::rightBorder() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetBorder(d_func()->node, YGEdgeRight));
}

QJSValue FlexboxAttached::bottomBorder() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetBorder(d_func()->node, YGEdgeBottom));
}

QJSValue FlexboxAttached::startBorder() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetBorder(d_func()->node, YGEdgeStart));
}

QJSValue FlexboxAttached::endBorder() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetBorder(d_func()->node, YGEdgeEnd));
}

QJSValue FlexboxAttached::horizontalBorder() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetBorder(d_func()->node, YGEdgeHorizontal));
}

QJSValue FlexboxAttached::verticalBorder() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetBorder(d_func()->node, YGEdgeVertical));
}

QJSValue FlexboxAttached::borders() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetBorder(d_func()->node, YGEdgeAll));
}

void FlexboxAttached::setColumnGap(QJSValue value)
{
    d_func()->setGap(YGGutterColumn, value);
}

void FlexboxAttached::setRowGap(QJSValue value)
{
    d_func()->setGap(YGGutterRow, value);
}

void FlexboxAttached::setGap(QJSValue value)
{
    d_func()->setGap(YGGutterAll, value);
}

QJSValue FlexboxAttached::columnGap() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetGap(d_func()->node, YGGutterColumn));
}

QJSValue FlexboxAttached::rowGap() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetGap(d_func()->node, YGGutterRow));
}

QJSValue FlexboxAttached::gap() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetGap(d_func()->node, YGGutterAll));
}

void FlexboxAttached::setFlex(QJSValue value)
{
    // https://www.yogalayout.dev/docs/styling/flex-basis-grow-shrink

    Q_D(FlexboxAttached);

    const auto oldValue = YGNodeStyleGetFlex(d->node);

    if (value.isUndefined()) {
        YGNodeStyleSetFlex(d->node, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetFlex(d->node, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();

        bool ok = false;
        const auto val = valStr.toFloat(&ok);
        if (!ok) {
            qWarning(lcFlexbox, "invalid String value: %s", qUtf8Printable(value.toString()));
            return;
        }

        YGNodeStyleSetFlex(d->node, val);
    } else {
        qWarning(lcFlexbox, "invalid value: %s", qUtf8Printable(value.toString()));
        return;
    }

    if (oldValue != YGNodeStyleGetFlex(d->node)) {
        emit flexChanged();
    }
}

void FlexboxAttached::setFlexGrow(QJSValue value)
{
    // https://www.yogalayout.dev/docs/styling/flex-basis-grow-shrink

    Q_D(FlexboxAttached);

    const auto oldValue = YGNodeStyleGetFlexGrow(d->node);

    if (value.isUndefined()) {
        YGNodeStyleSetFlexGrow(d->node, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetFlexGrow(d->node, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();

        bool ok = false;
        const auto val = valStr.toFloat(&ok);
        if (!ok) {
            qWarning(lcFlexbox, "invalid String value: %s", qUtf8Printable(value.toString()));
            return;
        }

        YGNodeStyleSetFlexGrow(d->node, val);
    } else {
        qWarning(lcFlexbox, "invalid value: %s", qUtf8Printable(value.toString()));
        return;
    }

    if (oldValue != YGNodeStyleGetFlexGrow(d->node)) {
        emit flexGrowChanged();
    }
}

void FlexboxAttached::setFlexBasis(QJSValue value)
{
    // https://www.yogalayout.dev/docs/styling/flex-basis-grow-shrink

    Q_D(FlexboxAttached);

    const auto oldValue = YGNodeStyleGetFlexBasis(d->node);

    if (value.isUndefined()) {
        YGNodeStyleSetFlexBasisAuto(d->node);
    } else if (value.isNumber()) {
        YGNodeStyleSetFlexBasis(d->node, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();

        if (valStr == QStringLiteral("auto")) {
            YGNodeStyleSetFlexBasisAuto(d->node);
        } else {
            bool percent = false;
            if (valStr.endsWith('%')) {
                percent = true;
                valStr.chop(1);
            }

            bool ok = false;
            const auto val = valStr.toFloat(&ok);
            if (!ok) {
                qWarning(lcFlexbox, "invalid String value: %s", qUtf8Printable(value.toString()));
                return;
            }

            if (percent) {
                YGNodeStyleSetFlexBasisPercent(d->node, val);
            } else {
                YGNodeStyleSetFlexBasis(d->node, val);
            }
        }
    } else {
        qWarning(lcFlexbox, "invalid value: %s", qUtf8Printable(value.toString()));
        return;
    }

    if (oldValue != YGNodeStyleGetFlexBasis(d->node)) {
        emit flexBasisChanged();
    }
}

void FlexboxAttached::setFlexShrink(QJSValue value)
{
    // https://www.yogalayout.dev/docs/styling/flex-basis-grow-shrink

    Q_D(FlexboxAttached);

    const auto oldValue = YGNodeStyleGetFlexShrink(d->node);

    if (value.isUndefined()) {
        YGNodeStyleSetFlexShrink(d->node, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetFlexShrink(d->node, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();

        bool ok = false;
        const auto val = valStr.toFloat(&ok);
        if (!ok) {
            qWarning(lcFlexbox, "invalid String value: %s", qUtf8Printable(value.toString()));
            return;
        }

        YGNodeStyleSetFlexShrink(d->node, val);
    } else {
        qWarning(lcFlexbox, "invalid value: %s", qUtf8Printable(value.toString()));
        return;
    }

    if (oldValue != YGNodeStyleGetFlexShrink(d->node)) {
        emit flexShrinkChanged();
    }
}

QJSValue FlexboxAttached::flex() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetFlex(d_func()->node));
}

QJSValue FlexboxAttached::flexGrow() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetFlexGrow(d_func()->node));
}

QJSValue FlexboxAttached::flexBasis() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetFlexBasis(d_func()->node));
}

QJSValue FlexboxAttached::flexShrink() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetFlexShrink(d_func()->node));
}

void FlexboxAttached::setAspectRatio(QJSValue value)
{
    // https://www.yogalayout.dev/docs/styling/aspect-ratio

    Q_D(FlexboxAttached);

    const auto oldValue = YGNodeStyleGetAspectRatio(d->node);

    if (value.isUndefined()) {
        YGNodeStyleSetAspectRatio(d->node, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetAspectRatio(d->node, value.toNumber());
    } else {
        qWarning(lcFlexbox, "invalid value: %s", qUtf8Printable(value.toString()));
        return;
    }

    if (oldValue != YGNodeStyleGetAspectRatio(d->node)) {
        emit aspectRatioChanged();
    }
}

QJSValue FlexboxAttached::aspectRatio() const
{
    return FlexboxInlines::toJSValue(YGNodeStyleGetAspectRatio(d_func()->node));
}

// class FlexboxAttachedPrivate

void FlexboxAttachedPrivate::onDirtied(YGNodeConstRef node)
{
    static_cast<FlexboxAttachedPrivate *>(YGNodeGetContext(node))->buildLayout();
}

void FlexboxAttachedPrivate::buildLayout()
{
    if (YGNodeGetParent(node)) {
        return;
    }

    QQuickItemPrivate *itemd = QQuickItemPrivate::get(item);
    if (itemd->componentComplete) {
        YGNodeCalculateLayout(node,
                              itemd->widthValid() ? item->width() : YGUndefined,
                              itemd->heightValid() ? item->height() : YGUndefined,
                              YGDirectionInherit);

        applyLayout();
    }
}

void FlexboxAttachedPrivate::applyLayout()
{
    if (!YGNodeGetHasNewLayout(node)) {
        return;
    }
    YGNodeSetHasNewLayout(node, false);

    const auto x = YGNodeLayoutGetLeft(node);
    if (item->x() != x) {
        item->setProperty("x", x);
    }
    const auto y = YGNodeLayoutGetTop(node);
    if (item->y() != y) {
        item->setProperty("y", y);
    }

    if (sizeType == UnknownSize) {
        if (item->inherits("QQuickText")) {
            sizeType = GeometrySize;
        } else {
            sizeType = ImplicitSize;
        }
    }

    if (sizeType == GeometrySize) {
        const auto w = YGNodeLayoutGetWidth(node);
        if (item->width() != w) {
            item->setProperty("width", w);
        }
        const auto h = YGNodeLayoutGetHeight(node);
        if (item->height() != h) {
            item->setProperty("height", h);
        }
    } else {
        const auto w = YGNodeLayoutGetWidth(node);
        if (item->implicitWidth() != w) {
            item->setProperty("implicitWidth", w);
        }
        const auto h = YGNodeLayoutGetHeight(node);
        if (item->implicitHeight() != h) {
            item->setProperty("implicitHeight", h);
        }
    }

    const size_t count = YGNodeGetChildCount(node);
    for (size_t index = 0; index < count; ++index) {
        YGNodeRef childNode = YGNodeGetChild(node, index);
        static_cast<FlexboxAttachedPrivate *>(YGNodeGetContext(childNode))->applyLayout();
    }
}

void FlexboxAttachedPrivate::setPosition(YGEdge edge, QJSValue value)
{
    // https://www.yogalayout.dev/docs/styling/position

    Q_Q(FlexboxAttached);

    const auto oldValue = YGNodeStyleGetPosition(node, edge);

    if (value.isUndefined()) {
        YGNodeStyleSetPosition(node, edge, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetPosition(node, edge, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();
        if (valStr == QStringLiteral("auto")) {
            YGNodeStyleSetPositionAuto(node, edge);
        } else {
            bool percent = false;
            if (valStr.endsWith('%')) {
                percent = true;
                valStr.chop(1);
            }

            bool ok = false;
            const auto val = valStr.toFloat(&ok);
            if (!ok) {
                qWarning(lcFlexbox, "invalid String value: %s", qUtf8Printable(value.toString()));
                return;
            }

            if (percent) {
                YGNodeStyleSetPositionPercent(node, edge, val);
            } else {
                YGNodeStyleSetPosition(node, edge, val);
            }
        }
    } else {
        qWarning(lcFlexbox, "invalid value: %s", qUtf8Printable(value.toString()));
        return;
    }

    if (oldValue != YGNodeStyleGetPosition(node, edge)) {
        switch (edge) {
        case YGEdgeLeft:
            emit q->leftMarginChanged();
            break;
        case YGEdgeTop:
            emit q->topMarginChanged();
            break;
        case YGEdgeRight:
            emit q->rightMarginChanged();
            break;
        case YGEdgeBottom:
            emit q->bottomMarginChanged();
            break;
        case YGEdgeStart:
            emit q->startMarginChanged();
            break;
        case YGEdgeEnd:
            emit q->endMarginChanged();
            break;
        default:
            Q_UNREACHABLE();
        }
    }
}

void FlexboxAttachedPrivate::setMargin(YGEdge edge, QJSValue value)
{
    // https://www.yogalayout.dev/docs/styling/margin-padding-border

    Q_Q(FlexboxAttached);

    const auto oldValue = YGNodeStyleGetMargin(node, edge);

    if (value.isUndefined()) {
        YGNodeStyleSetMargin(node, edge, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetMargin(node, edge, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();
        if (valStr == QStringLiteral("auto")) {
            YGNodeStyleSetMarginAuto(node, edge);
        } else {
            bool percent = false;
            if (valStr.endsWith('%')) {
                percent = true;
                valStr.chop(1);
            }

            bool ok = false;
            const auto val = valStr.toFloat(&ok);
            if (!ok) {
                qWarning(lcFlexbox, "invalid String value: %s", qUtf8Printable(value.toString()));
                return;
            }

            if (percent) {
                YGNodeStyleSetMarginPercent(node, edge, val);
            } else {
                YGNodeStyleSetMargin(node, edge, val);
            }
        }
    } else {
        qWarning(lcFlexbox, "invalid value: %s", qUtf8Printable(value.toString()));
        return;
    }

    if (oldValue != YGNodeStyleGetMargin(node, edge)) {
        switch (edge) {
        case YGEdgeLeft:
            emit q->leftMarginChanged();
            break;
        case YGEdgeTop:
            emit q->topMarginChanged();
            break;
        case YGEdgeRight:
            emit q->rightMarginChanged();
            break;
        case YGEdgeBottom:
            emit q->bottomMarginChanged();
            break;
        case YGEdgeStart:
            emit q->startMarginChanged();
            break;
        case YGEdgeEnd:
            emit q->endMarginChanged();
            break;
        case YGEdgeHorizontal:
            emit q->horizontalMarginChanged();
            break;
        case YGEdgeVertical:
            emit q->verticalMarginChanged();
            break;
        case YGEdgeAll:
            emit q->marginsChanged();
            break;
        default:
            Q_UNREACHABLE();
        }
    }
}

void FlexboxAttachedPrivate::setPadding(YGEdge edge, QJSValue value)
{
    // https://www.yogalayout.dev/docs/styling/margin-padding-border

    Q_Q(FlexboxAttached);

    const auto oldValue = YGNodeStyleGetPadding(node, edge);

    if (value.isUndefined()) {
        YGNodeStyleSetPadding(node, edge, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetPadding(node, edge, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();

        bool percent = false;
        if (valStr.endsWith('%')) {
            percent = true;
            valStr.chop(1);
        }

        bool ok = false;
        const auto val = valStr.toFloat(&ok);
        if (!ok) {
            qWarning(lcFlexbox, "invalid String value: %s", qUtf8Printable(value.toString()));
            return;
        }

        if (percent) {
            YGNodeStyleSetPaddingPercent(node, edge, val);
        } else {
            YGNodeStyleSetPadding(node, edge, val);
        }
    } else {
        qWarning(lcFlexbox, "invalid value: %s", qUtf8Printable(value.toString()));
        return;
    }

    if (oldValue != YGNodeStyleGetPadding(node, edge)) {
        switch (edge) {
        case YGEdgeLeft:
            emit q->leftPaddingChanged();
            break;
        case YGEdgeTop:
            emit q->topPaddingChanged();
            break;
        case YGEdgeRight:
            emit q->rightPaddingChanged();
            break;
        case YGEdgeBottom:
            emit q->bottomPaddingChanged();
            break;
        case YGEdgeStart:
            emit q->startPaddingChanged();
            break;
        case YGEdgeEnd:
            emit q->endPaddingChanged();
            break;
        case YGEdgeHorizontal:
            emit q->horizontalPaddingChanged();
            break;
        case YGEdgeVertical:
            emit q->verticalPaddingChanged();
            break;
        case YGEdgeAll:
            emit q->paddingChanged();
            break;
        default:
            Q_UNREACHABLE();
        }
    }
}

void FlexboxAttachedPrivate::setBorder(YGEdge edge, QJSValue value)
{
    // https://www.yogalayout.dev/docs/styling/margin-padding-border

    Q_Q(FlexboxAttached);

    const auto oldValue = YGNodeStyleGetBorder(node, edge);

    if (value.isUndefined()) {
        YGNodeStyleSetBorder(node, edge, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetBorder(node, edge, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();

        bool ok = false;
        const auto val = valStr.toFloat(&ok);
        if (!ok) {
            qWarning(lcFlexbox, "invalid String value: %s", qUtf8Printable(value.toString()));
            return;
        }

        YGNodeStyleSetBorder(node, edge, val);
    } else {
        qWarning(lcFlexbox, "invalid value: %s", qUtf8Printable(value.toString()));
        return;
    }

    if (oldValue != YGNodeStyleGetBorder(node, edge)) {
        switch (edge) {
        case YGEdgeLeft:
            emit q->leftBorderChanged();
            break;
        case YGEdgeTop:
            emit q->topBorderChanged();
            break;
        case YGEdgeRight:
            emit q->rightBorderChanged();
            break;
        case YGEdgeBottom:
            emit q->bottomBorderChanged();
            break;
        case YGEdgeStart:
            emit q->startBorderChanged();
            break;
        case YGEdgeEnd:
            emit q->endBorderChanged();
            break;
        case YGEdgeHorizontal:
            emit q->horizontalBorderChanged();
            break;
        case YGEdgeVertical:
            emit q->verticalBorderChanged();
            break;
        case YGEdgeAll:
            emit q->bordersChanged();
            break;
        default:
            Q_UNREACHABLE();
        }
    }
}

void FlexboxAttachedPrivate::setGap(YGGutter gutter, QJSValue value)
{
    // no document

    Q_Q(FlexboxAttached);

    const auto oldValue = YGNodeStyleGetGap(node, gutter);

    if (value.isUndefined()) {
        YGNodeStyleSetGap(node, gutter, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetGap(node, gutter, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();

        bool percent = false;
        if (valStr.endsWith('%')) {
            percent = true;
            valStr.chop(1);
        }

        bool ok = false;
        const auto val = valStr.toFloat(&ok);
        if (!ok) {
            qWarning(lcFlexbox, "invalid String value: %s", qUtf8Printable(value.toString()));
            return;
        }

        if (percent) {
            YGNodeStyleSetGapPercent(node, gutter, val);
        } else {
            YGNodeStyleSetGap(node, gutter, val);
        }
    } else {
        qWarning(lcFlexbox, "invalid value: %s", qUtf8Printable(value.toString()));
        return;
    }

    if (oldValue != YGNodeStyleGetGap(node, gutter)) {
        switch (gutter) {
        case YGGutterColumn:
            emit q->columnGapChanged();
            break;
        case YGGutterRow:
            emit q->rowGapChanged();
            break;
        case YGGutterAll:
            emit q->gapChanged();
            break;
        default:
            Q_UNREACHABLE();
        }
    }
}

void FlexboxAttachedPrivate::itemGeometryChanged(QQuickItem *, QQuickGeometryChange, const QRectF &)
{
    buildLayout();
}

void FlexboxAttachedPrivate::itemChildAdded(QQuickItem *, QQuickItem *child)
{
    FlexboxAttached *attached = qobject_cast<FlexboxAttached *>(qmlAttachedPropertiesObject<Flexbox>(child, false));
    if (attached) {
        YGNodeRef childNode = attached->d_func()->node;
        if (childNode) {
            const size_t index = YGNodeGetChildCount(node);
            YGNodeInsertChild(node, childNode, index);
        }
    }
}

void FlexboxAttachedPrivate::itemChildRemoved(QQuickItem *, QQuickItem *child)
{
    FlexboxAttached *attached = qobject_cast<FlexboxAttached *>(qmlAttachedPropertiesObject<Flexbox>(child, false));
    if (attached) {
        YGNodeRef childNode = attached->d_func()->node;
        if (childNode) {
            YGNodeRemoveChild(node, childNode);
        }
    }
}

void FlexboxAttachedPrivate::itemVisibilityChanged(QQuickItem *)
{
    Q_Q(FlexboxAttached);

    if (item->isVisible()) {
        q->setDisplay(Flexbox::Flex);
    } else {
        q->setDisplay(Flexbox::None);
    }
}

void FlexboxAttachedPrivate::itemOpacityChanged(QQuickItem *)
{
}
