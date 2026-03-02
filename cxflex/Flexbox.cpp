#include "Flexbox.h"
#include "Flexbox_p.h"

#include <QTimer>

#include <private/qquickitem_p.h>

#include "CxFlexSettings.h"
#include "CxFlexSettings_p.h"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(lcFlexbox, "Flexbox")

// class FlexboxAttached

FlexboxAttached::FlexboxAttached(QObject *parent)
    : QObject(parent)
    , d_ptr(new FlexboxAttachedPrivate())
{
    d_ptr->q_ptr = this;

    Q_D(FlexboxAttached);

    d->node = YGNodeNewWithConfig(CxFlexSettingsPrivate::defaultConfig());
    if (d->node) {
        YGNodeSetContext(d->node, d);

        YGNodeSetDirtiedFunc(d->node, &FlexboxAttachedPrivate::onDirtied);
    }

    d->item = qobject_cast<QQuickItem *>(parent);
    if (d->item) {
        d->itemd = QQuickItemPrivate::get(d->item);

        d->itemd->addItemChangeListener(d, QQuickItemPrivate::Geometry | QQuickItemPrivate::Visibility | QQuickItemPrivate::Children);

        for (QQuickItem *child : d->item->childItems()) {
            YGNodeRef childNode = nullptr;

            FlexboxAttached *attached = qobject_cast<FlexboxAttached *>(qmlAttachedPropertiesObject<Flexbox>(child, false));
            if (attached) {
                childNode = attached->d_func()->node;
            }

            if (childNode) {
                const size_t index = YGNodeGetChildCount(d->node);
                YGNodeInsertChild(d->node, childNode, index);
            }
        }
    }
}

FlexboxAttached::~FlexboxAttached()
{
    Q_D(FlexboxAttached);

    if (d->itemd) {
        d->itemd->removeItemChangeListener(d, QQuickItemPrivate::Geometry | QQuickItemPrivate::Visibility | QQuickItemPrivate::Children);
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

void FlexboxAttached::setWidth(QJSValue value)
{
    // https://www.yogalayout.dev/docs/styling/width-height

    Q_D(FlexboxAttached);

    const YGValue oldValue = YGNodeStyleGetWidth(d->node);

    if (value.isUndefined()) {
        YGNodeStyleSetWidthAuto(d->node);
    } else if (value.isNumber()) {
        YGNodeStyleSetWidth(d->node, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();
        if (valStr == QStringLiteral("auto")) {
            YGNodeStyleSetWidthAuto(d->node);
        } else {
            bool percent = false;
            if (valStr.endsWith('%')) {
                valStr.chop(1);
                percent = true;
            }

            bool ok = false;
            const float val = valStr.toFloat(&ok);
            if (ok) {
                if (percent) {
                    YGNodeStyleSetWidthPercent(d->node, val);
                } else {
                    YGNodeStyleSetWidth(d->node, val);
                }
            } else {
                qWarning(lcFlexbox, "invalid String value: %s", qUtf8Printable(value.toString()));
                return;
            }
        }
    } else {
        qWarning(lcFlexbox, "invalid value: %s", qUtf8Printable(value.toString()));
        return;
    }

    const YGValue newValue = YGNodeStyleGetWidth(d->node);
    if (oldValue != newValue) {
        emit widthChanged();
    }
}

void FlexboxAttached::setHeight(QJSValue value)
{
    // https://www.yogalayout.dev/docs/styling/width-height

    Q_D(FlexboxAttached);

    const YGValue oldValue = YGNodeStyleGetHeight(d->node);

    if (value.isUndefined()) {
        YGNodeStyleSetHeightAuto(d->node);
    } else if (value.isNumber()) {
        YGNodeStyleSetHeight(d->node, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();
        if (valStr == QStringLiteral("auto")) {
            YGNodeStyleSetHeightAuto(d->node);
        } else {
            bool percent = false;
            if (valStr.endsWith('%')) {
                valStr.chop(1);
                percent = true;
            }

            bool ok = false;
            const float val = valStr.toFloat(&ok);
            if (ok) {
                if (percent) {
                    YGNodeStyleSetHeightPercent(d->node, val);
                } else {
                    YGNodeStyleSetHeight(d->node, val);
                }
            } else {
                qWarning(lcFlexbox, "invalid String value: %s", qUtf8Printable(value.toString()));
                return;
            }
        }
    } else {
        qWarning(lcFlexbox, "invalid value: %s", qUtf8Printable(value.toString()));
        return;
    }

    const YGValue newValue = YGNodeStyleGetHeight(d->node);
    if (oldValue != newValue) {
        emit heightChanged();
    }
}

QJSValue FlexboxAttached::width() const
{
    // https://www.yogalayout.dev/docs/styling/width-height

    Q_D(const FlexboxAttached);

    const YGValue value = YGNodeStyleGetWidth(d->node);

    switch (value.unit) {
    case YGUnitUndefined:
        Q_ASSERT_X(false, "FlexboxAttached::width()", "unexpected unit: Undefined");
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

QJSValue FlexboxAttached::height() const
{
    // https://www.yogalayout.dev/docs/styling/width-height

    Q_D(const FlexboxAttached);

    const YGValue value = YGNodeStyleGetHeight(d->node);

    switch (value.unit) {
    case YGUnitUndefined:
        Q_ASSERT_X(false, "FlexboxAttached::height()", "unexpected unit: Undefined");
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

void FlexboxAttached::setMinimumWidth(QJSValue value)
{
    Q_D(FlexboxAttached);

    // https://www.yogalayout.dev/docs/styling/min-max-width-height

    const YGValue oldValue = YGNodeStyleGetMinWidth(d->node);

    if (value.isUndefined()) {
        YGNodeStyleSetMinWidth(d->node, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetMinWidth(d->node, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();

        bool percent = false;
        if (valStr.endsWith('%')) {
            valStr.chop(1);
            percent = true;
        }

        bool ok = false;
        const float val = valStr.toFloat(&ok);
        if (ok) {
            if (percent) {
                YGNodeStyleSetMinWidthPercent(d->node, val);
            } else {
                YGNodeStyleSetMinWidth(d->node, val);
            }
        } else {
            qWarning(lcFlexbox, "invalid String value: %s", qUtf8Printable(value.toString()));
            return;
        }
    } else {
        qWarning(lcFlexbox, "invalid value: %s", qUtf8Printable(value.toString()));
        return;
    }

    const YGValue newValue = YGNodeStyleGetMinWidth(d->node);
    if (oldValue != newValue) {
        emit minimumWidthChanged();
    }
}

void FlexboxAttached::setMinimumHeight(QJSValue value)
{
    Q_D(FlexboxAttached);

    // https://www.yogalayout.dev/docs/styling/min-max-width-height

    const YGValue oldValue = YGNodeStyleGetMinHeight(d->node);

    if (value.isUndefined()) {
        YGNodeStyleSetMinHeight(d->node, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetMinHeight(d->node, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();

        bool percent = false;
        if (valStr.endsWith('%')) {
            valStr.chop(1);
            percent = true;
        }

        bool ok = false;
        const float val = valStr.toFloat(&ok);
        if (ok) {
            if (percent) {
                YGNodeStyleSetMinHeightPercent(d->node, val);
            } else {
                YGNodeStyleSetMinHeight(d->node, val);
            }
        } else {
            qWarning(lcFlexbox, "invalid String value: %s", qUtf8Printable(value.toString()));
            return;
        }
    } else {
        qWarning(lcFlexbox, "invalid value: %s", qUtf8Printable(value.toString()));
        return;
    }

    const YGValue newValue = YGNodeStyleGetMinHeight(d->node);
    if (oldValue != newValue) {
        emit minimumHeightChanged();
    }
}

void FlexboxAttached::setMaximumWidth(QJSValue value)
{
    Q_D(FlexboxAttached);

    // https://www.yogalayout.dev/docs/styling/min-max-width-height

    const YGValue oldValue = YGNodeStyleGetMaxWidth(d->node);

    if (value.isUndefined()) {
        YGNodeStyleSetMaxWidth(d->node, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetMaxWidth(d->node, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();

        bool percent = false;
        if (valStr.endsWith('%')) {
            valStr.chop(1);
            percent = true;
        }

        bool ok = false;
        const float val = valStr.toFloat(&ok);
        if (ok) {
            if (percent) {
                YGNodeStyleSetMaxWidthPercent(d->node, val);
            } else {
                YGNodeStyleSetMaxWidth(d->node, val);
            }
        } else {
            qWarning(lcFlexbox, "invalid String value: %s", qUtf8Printable(value.toString()));
            return;
        }
    } else {
        qWarning(lcFlexbox, "invalid value: %s", qUtf8Printable(value.toString()));
        return;
    }

    const YGValue newValue = YGNodeStyleGetMaxWidth(d->node);
    if (oldValue != newValue) {
        emit maximumWidthChanged();
    }
}

void FlexboxAttached::setMaximumHeight(QJSValue value)
{
    Q_D(FlexboxAttached);

    // https://www.yogalayout.dev/docs/styling/min-max-width-height

    const YGValue oldValue = YGNodeStyleGetMaxHeight(d->node);

    if (value.isUndefined()) {
        YGNodeStyleSetMaxHeight(d->node, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetMaxHeight(d->node, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();

        bool percent = false;
        if (valStr.endsWith('%')) {
            valStr.chop(1);
            percent = true;
        }

        bool ok = false;
        const float val = valStr.toFloat(&ok);
        if (ok) {
            if (percent) {
                YGNodeStyleSetMaxHeightPercent(d->node, val);
            } else {
                YGNodeStyleSetMaxHeight(d->node, val);
            }
        } else {
            qWarning(lcFlexbox, "invalid String value: %s", qUtf8Printable(value.toString()));
            return;
        }
    } else {
        qWarning(lcFlexbox, "invalid value: %s", qUtf8Printable(value.toString()));
        return;
    }

    const YGValue newValue = YGNodeStyleGetMaxHeight(d->node);
    if (oldValue != newValue) {
        emit maximumHeightChanged();
    }
}

QJSValue FlexboxAttached::minimumWidth() const
{
    // https://www.yogalayout.dev/docs/styling/min-max-width-height

    const YGValue value = YGNodeStyleGetMinWidth(d_func()->node);

    switch (value.unit) {
    case YGUnitUndefined:
        return {};
    case YGUnitPoint:
        return value.value;
    case YGUnitPercent:
        return QStringLiteral("%1%").arg(value.value);
    case YGUnitAuto:
        Q_ASSERT_X(false, "FlexboxAttached::minimumWidth()", "unexpected unit: Auto");
        return {};
    default:
        Q_UNREACHABLE();
    }
}

QJSValue FlexboxAttached::minimumHeight() const
{
    // https://www.yogalayout.dev/docs/styling/min-max-width-height

    const YGValue value = YGNodeStyleGetMinHeight(d_func()->node);

    switch (value.unit) {
    case YGUnitUndefined:
        return {};
    case YGUnitPoint:
        return value.value;
    case YGUnitPercent:
        return QStringLiteral("%1%").arg(value.value);
    case YGUnitAuto:
        Q_ASSERT_X(false, "FlexboxAttached::minimumHeight()", "unexpected unit: Auto");
        return {};
    default:
        Q_UNREACHABLE();
    }
}

QJSValue FlexboxAttached::maximumWidth() const
{
    // https://www.yogalayout.dev/docs/styling/min-max-width-height

    const YGValue value = YGNodeStyleGetMaxWidth(d_func()->node);

    switch (value.unit) {
    case YGUnitUndefined:
        return {};
    case YGUnitPoint:
        return value.value;
    case YGUnitPercent:
        return QStringLiteral("%1%").arg(value.value);
    case YGUnitAuto:
        Q_ASSERT_X(false, "FlexboxAttached::maximumWidth()", "unexpected unit: Auto");
        return {};
    default:
        Q_UNREACHABLE();
    }
}

QJSValue FlexboxAttached::maximumHeight() const
{
    // https://www.yogalayout.dev/docs/styling/min-max-width-height

    const YGValue value = YGNodeStyleGetMaxHeight(d_func()->node);

    switch (value.unit) {
    case YGUnitUndefined:
        return {};
    case YGUnitPoint:
        return value.value;
    case YGUnitPercent:
        return QStringLiteral("%1%").arg(value.value);
    case YGUnitAuto:
        Q_ASSERT_X(false, "FlexboxAttached::maximumHeight()", "unexpected unit: Auto");
        return {};
    default:
        Q_UNREACHABLE();
    }
}

void FlexboxAttached::setLeftMargin(QJSValue value)
{
    if (d_func()->setMargin(YGEdgeLeft, value)) {
        emit leftMarginChanged();
    }
}

void FlexboxAttached::setTopMargin(QJSValue value)
{
    if (d_func()->setMargin(YGEdgeTop, value)) {
        emit topMarginChanged();
    }
}

void FlexboxAttached::setRightMargin(QJSValue value)
{
    if (d_func()->setMargin(YGEdgeRight, value)) {
        emit rightMarginChanged();
    }
}

void FlexboxAttached::setBottomMargin(QJSValue value)
{
    if (d_func()->setMargin(YGEdgeBottom, value)) {
        emit bottomMarginChanged();
    }
}

void FlexboxAttached::setStartMargin(QJSValue value)
{
    if (d_func()->setMargin(YGEdgeStart, value)) {
        emit startMarginChanged();
    }
}

void FlexboxAttached::setEndMargin(QJSValue value)
{
    if (d_func()->setMargin(YGEdgeEnd, value)) {
        emit endMarginChanged();
    }
}

void FlexboxAttached::setHorizontalMargin(QJSValue value)
{
    if (d_func()->setMargin(YGEdgeHorizontal, value)) {
        emit horizontalMarginChanged();
    }
}

void FlexboxAttached::setVerticalMargin(QJSValue value)
{
    if (d_func()->setMargin(YGEdgeVertical, value)) {
        emit verticalMarginChanged();
    }
}

void FlexboxAttached::setMargins(QJSValue value)
{
    if (d_func()->setMargin(YGEdgeAll, value)) {
        emit marginsChanged();
    }
}

QJSValue FlexboxAttached::leftMargin() const
{
    return d_func()->margin(YGEdgeLeft);
}

QJSValue FlexboxAttached::topMargin() const
{
    return d_func()->margin(YGEdgeTop);
}

QJSValue FlexboxAttached::rightMargin() const
{
    return d_func()->margin(YGEdgeRight);
}

QJSValue FlexboxAttached::bottomMargin() const
{
    return d_func()->margin(YGEdgeBottom);
}

QJSValue FlexboxAttached::startMargin() const
{
    return d_func()->margin(YGEdgeStart);
}

QJSValue FlexboxAttached::endMargin() const
{
    return d_func()->margin(YGEdgeEnd);
}

QJSValue FlexboxAttached::horizontalMargin() const
{
    return d_func()->margin(YGEdgeHorizontal);
}

QJSValue FlexboxAttached::verticalMargin() const
{
    return d_func()->margin(YGEdgeVertical);
}

QJSValue FlexboxAttached::margins() const
{
    return d_func()->margin(YGEdgeAll);
}

void FlexboxAttached::setLeftPadding(QJSValue value)
{
    if (d_func()->setPadding(YGEdgeLeft, value)) {
        emit leftPaddingChanged();
    }
}

void FlexboxAttached::setTopPadding(QJSValue value)
{
    if (d_func()->setPadding(YGEdgeTop, value)) {
        emit topPaddingChanged();
    }
}

void FlexboxAttached::setRightPadding(QJSValue value)
{
    if (d_func()->setPadding(YGEdgeRight, value)) {
        emit rightPaddingChanged();
    }
}

void FlexboxAttached::setBottomPadding(QJSValue value)
{
    if (d_func()->setPadding(YGEdgeBottom, value)) {
        emit bottomPaddingChanged();
    }
}

void FlexboxAttached::setStartPadding(QJSValue value)
{
    if (d_func()->setPadding(YGEdgeStart, value)) {
        emit startPaddingChanged();
    }
}

void FlexboxAttached::setEndPadding(QJSValue value)
{
    if (d_func()->setPadding(YGEdgeEnd, value)) {
        emit endPaddingChanged();
    }
}

void FlexboxAttached::setHorizontalPadding(QJSValue value)
{
    if (d_func()->setPadding(YGEdgeHorizontal, value)) {
        emit horizontalPaddingChanged();
    }
}

void FlexboxAttached::setVerticalPadding(QJSValue value)
{
    if (d_func()->setPadding(YGEdgeVertical, value)) {
        emit verticalPaddingChanged();
    }
}

void FlexboxAttached::setPadding(QJSValue value)
{
    if (d_func()->setPadding(YGEdgeAll, value)) {
        emit paddingChanged();
    }
}

QJSValue FlexboxAttached::leftPadding() const
{
    return d_func()->padding(YGEdgeLeft);
}

QJSValue FlexboxAttached::topPadding() const
{
    return d_func()->padding(YGEdgeTop);
}

QJSValue FlexboxAttached::rightPadding() const
{
    return d_func()->padding(YGEdgeRight);
}

QJSValue FlexboxAttached::bottomPadding() const
{
    return d_func()->padding(YGEdgeBottom);
}

QJSValue FlexboxAttached::startPadding() const
{
    return d_func()->padding(YGEdgeStart);
}

QJSValue FlexboxAttached::endPadding() const
{
    return d_func()->padding(YGEdgeEnd);
}

QJSValue FlexboxAttached::horizontalPadding() const
{
    return d_func()->padding(YGEdgeHorizontal);
}

QJSValue FlexboxAttached::verticalPadding() const
{
    return d_func()->padding(YGEdgeVertical);
}

QJSValue FlexboxAttached::padding() const
{
    return d_func()->padding(YGEdgeAll);
}

void FlexboxAttached::setLeftBorder(QJSValue value)
{
    if (d_func()->setBorder(YGEdgeLeft, value)) {
        emit leftBorderChanged();
    }
}

void FlexboxAttached::setTopBorder(QJSValue value)
{
    if (d_func()->setBorder(YGEdgeTop, value)) {
        emit topBorderChanged();
    }
}

void FlexboxAttached::setRightBorder(QJSValue value)
{
    if (d_func()->setBorder(YGEdgeRight, value)) {
        emit rightBorderChanged();
    }
}

void FlexboxAttached::setBottomBorder(QJSValue value)
{
    if (d_func()->setBorder(YGEdgeBottom, value)) {
        emit bottomBorderChanged();
    }
}

void FlexboxAttached::setStartBorder(QJSValue value)
{
    if (d_func()->setBorder(YGEdgeStart, value)) {
        emit startBorderChanged();
    }
}

void FlexboxAttached::setEndBorder(QJSValue value)
{
    if (d_func()->setBorder(YGEdgeEnd, value)) {
        emit endBorderChanged();
    }
}

void FlexboxAttached::setHorizontalBorder(QJSValue value)
{
    if (d_func()->setBorder(YGEdgeHorizontal, value)) {
        emit horizontalBorderChanged();
    }
}

void FlexboxAttached::setVerticalBorder(QJSValue value)
{
    if (d_func()->setBorder(YGEdgeVertical, value)) {
        emit verticalBorderChanged();
    }
}

void FlexboxAttached::setBorders(QJSValue value)
{
    if (d_func()->setBorder(YGEdgeAll, value)) {
        emit bordersChanged();
    }
}

QJSValue FlexboxAttached::leftBorder() const
{
    return d_func()->border(YGEdgeLeft);
}

QJSValue FlexboxAttached::topBorder() const
{
    return d_func()->border(YGEdgeTop);
}

QJSValue FlexboxAttached::rightBorder() const
{
    return d_func()->border(YGEdgeRight);
}

QJSValue FlexboxAttached::bottomBorder() const
{
    return d_func()->border(YGEdgeBottom);
}

QJSValue FlexboxAttached::startBorder() const
{
    return d_func()->border(YGEdgeStart);
}

QJSValue FlexboxAttached::endBorder() const
{
    return d_func()->border(YGEdgeEnd);
}

QJSValue FlexboxAttached::horizontalBorder() const
{
    return d_func()->border(YGEdgeHorizontal);
}

QJSValue FlexboxAttached::verticalBorder() const
{
    return d_func()->border(YGEdgeVertical);
}

QJSValue FlexboxAttached::borders() const
{
    return d_func()->border(YGEdgeAll);
}

void FlexboxAttached::setDirection(Flexbox::Direction value)
{
    // https://yogalayout.com/docs/layout-direction

    Q_D(FlexboxAttached);

    const YGDirection oldValue = YGNodeStyleGetDirection(d->node);

    YGNodeStyleSetDirection(d->node, static_cast<YGDirection>(value));

    const YGDirection newValue = YGNodeStyleGetDirection(d->node);
    if (oldValue != newValue) {
        emit directionChanged();
    }
}

void FlexboxAttached::setPosition(Flexbox::Position value)
{
    // https://yogalayout.com/docs/absolute-relative-layout

    Q_D(FlexboxAttached);

    const YGPositionType oldValue = YGNodeStyleGetPositionType(d->node);

    YGNodeStyleSetPositionType(d->node, static_cast<YGPositionType>(value));

    const YGPositionType newValue = YGNodeStyleGetPositionType(d->node);
    if (oldValue != newValue) {
        emit positionChanged();
    }
}

void FlexboxAttached::setDisplay(Flexbox::Display value)
{
    // no document

    Q_D(FlexboxAttached);

    const YGDisplay oldValue = YGNodeStyleGetDisplay(d->node);

    YGNodeStyleSetDisplay(d->node, static_cast<YGDisplay>(value));

    const YGDisplay newValue = YGNodeStyleGetDisplay(d->node);
    if (oldValue != newValue) {
        emit displayChanged();
    }
}

void FlexboxAttached::setOverflow(Flexbox::Overflow value)
{
    // no document

    Q_D(FlexboxAttached);

    const YGOverflow oldValue = YGNodeStyleGetOverflow(d->node);

    YGNodeStyleSetOverflow(d->node, static_cast<YGOverflow>(value));

    const YGOverflow newValue = YGNodeStyleGetOverflow(d->node);
    if (oldValue != newValue) {
        emit overflowChanged();
    }
}

Flexbox::Direction FlexboxAttached::direction() const
{
    // https://www.yogalayout.dev/docs/styling/layout-direction

    return static_cast<Flexbox::Direction>(YGNodeStyleGetDirection(d_func()->node));
}

Flexbox::Position FlexboxAttached::position() const
{
    // https://yogalayout.com/docs/absolute-relative-layout

    return static_cast<Flexbox::Position>(YGNodeStyleGetPositionType(d_func()->node));
}

Flexbox::Display FlexboxAttached::display() const
{
    // no document

    return static_cast<Flexbox::Display>(YGNodeStyleGetDisplay(d_func()->node));
}

Flexbox::Overflow FlexboxAttached::overflow() const
{
    // no document

    return static_cast<Flexbox::Overflow>(YGNodeStyleGetOverflow(d_func()->node));
}

void FlexboxAttached::setPositionLeft(QJSValue value)
{
    if (d_func()->setPosition(YGEdgeLeft, value)) {
        emit positionLeftChanged();
    }
}

void FlexboxAttached::setPositionTop(QJSValue value)
{
    if (d_func()->setPosition(YGEdgeTop, value)) {
        emit positionTopChanged();
    }
}

void FlexboxAttached::setPositionRight(QJSValue value)
{
    if (d_func()->setPosition(YGEdgeRight, value)) {
        emit positionRightChanged();
    }
}

void FlexboxAttached::setPositionBottom(QJSValue value)
{
    if (d_func()->setPosition(YGEdgeBottom, value)) {
        emit positionBottomChanged();
    }
}

void FlexboxAttached::setPositionStart(QJSValue value)
{
    if (d_func()->setPosition(YGEdgeStart, value)) {
        emit positionStartChanged();
    }
}

void FlexboxAttached::setPositionEnd(QJSValue value)
{
    if (d_func()->setPosition(YGEdgeEnd, value)) {
        emit positionEndChanged();
    }
}

QJSValue FlexboxAttached::positionLeft() const
{
    return d_func()->position(YGEdgeLeft);
}

QJSValue FlexboxAttached::positionTop() const
{
    return d_func()->position(YGEdgeTop);
}

QJSValue FlexboxAttached::positionRight() const
{
    return d_func()->position(YGEdgeRight);
}

QJSValue FlexboxAttached::positionBottom() const
{
    return d_func()->position(YGEdgeBottom);
}

QJSValue FlexboxAttached::positionStart() const
{
    return d_func()->position(YGEdgeStart);
}

QJSValue FlexboxAttached::positionEnd() const
{
    return d_func()->position(YGEdgeEnd);
}

void FlexboxAttached::setFlexDirection(Flexbox::FlexDirection value)
{
    Q_D(FlexboxAttached);

    // https://www.yogalayout.dev/docs/styling/flex-direction

    const YGFlexDirection oldValue = YGNodeStyleGetFlexDirection(d->node);

    YGNodeStyleSetFlexDirection(d->node, static_cast<YGFlexDirection>(value));

    const YGFlexDirection newValue = YGNodeStyleGetFlexDirection(d->node);

    if (oldValue != newValue) {
        emit flexDirectionChanged();
    }
}

void FlexboxAttached::setJustifyContent(Flexbox::Justify value)
{
    Q_D(FlexboxAttached);

    // https://www.yogalayout.dev/docs/styling/justify-content

    const YGJustify oldValue = YGNodeStyleGetJustifyContent(d->node);

    YGNodeStyleSetJustifyContent(d->node, static_cast<YGJustify>(value));

    const YGJustify newValue = YGNodeStyleGetJustifyContent(d->node);

    if (oldValue != newValue) {
        emit justifyContentChanged();
    }
}

void FlexboxAttached::setAlignContent(Flexbox::Align value)
{
    Q_D(FlexboxAttached);

    // https://www.yogalayout.dev/docs/styling/align-content

    const YGAlign oldValue = YGNodeStyleGetAlignContent(d->node);
    YGNodeStyleSetAlignContent(d->node, static_cast<YGAlign>(value));
    const YGAlign newValue = YGNodeStyleGetAlignContent(d->node);

    if (oldValue != newValue) {
        emit alignContentChanged();
    }
}

void FlexboxAttached::setAlignItems(Flexbox::Align value)
{
    Q_D(FlexboxAttached);

    // https://www.yogalayout.dev/docs/styling/align-items-self

    const YGAlign oldValue = YGNodeStyleGetAlignItems(d->node);
    YGNodeStyleSetAlignItems(d->node, static_cast<YGAlign>(value));
    const YGAlign newValue = YGNodeStyleGetAlignItems(d->node);

    if (oldValue != newValue) {
        emit alignItemsChanged();
    }
}

void FlexboxAttached::setAlignSelf(Flexbox::Align value)
{
    Q_D(FlexboxAttached);

    // https://www.yogalayout.dev/docs/styling/align-items-self

    const YGAlign oldValue = YGNodeStyleGetAlignSelf(d->node);
    YGNodeStyleSetAlignSelf(d->node, static_cast<YGAlign>(value));
    const YGAlign newValue = YGNodeStyleGetAlignSelf(d->node);

    if (oldValue != newValue) {
        emit alignSelfChanged();
    }
}

void FlexboxAttached::setFlexWrap(Flexbox::Wrap value)
{
    // https://www.yogalayout.dev/docs/styling/flex-wrap

    Q_D(FlexboxAttached);

    const YGWrap oldValue = YGNodeStyleGetFlexWrap(d->node);
    YGNodeStyleSetFlexWrap(d->node, static_cast<YGWrap>(value));
    const YGWrap newValue = YGNodeStyleGetFlexWrap(d->node);

    if (oldValue != newValue) {
        emit flexWrapChanged();
    }
}

Flexbox::FlexDirection FlexboxAttached::flexDirection() const
{
    // https://www.yogalayout.dev/docs/styling/flex-direction

    Q_D(const FlexboxAttached);

    return static_cast<Flexbox::FlexDirection>(YGNodeStyleGetFlexDirection(d->node));
}

Flexbox::Justify FlexboxAttached::justifyContent() const
{
    // https://www.yogalayout.dev/docs/styling/justify-content

    Q_D(const FlexboxAttached);

    return static_cast<Flexbox::Justify>(YGNodeStyleGetJustifyContent(d->node));
}

Flexbox::Align FlexboxAttached::alignContent() const
{
    // https://www.yogalayout.dev/docs/styling/align-content

    Q_D(const FlexboxAttached);

    return static_cast<Flexbox::Align>(YGNodeStyleGetAlignContent(d->node));
}

Flexbox::Align FlexboxAttached::alignItems() const
{
    // https://www.yogalayout.dev/docs/styling/align-items-self

    Q_D(const FlexboxAttached);

    return static_cast<Flexbox::Align>(YGNodeStyleGetAlignItems(d->node));
}

Flexbox::Align FlexboxAttached::alignSelf() const
{
    // https://www.yogalayout.dev/docs/styling/align-items-self

    Q_D(const FlexboxAttached);

    return static_cast<Flexbox::Align>(YGNodeStyleGetAlignSelf(d->node));
}

Flexbox::Wrap FlexboxAttached::flexWrap() const
{
    // https://www.yogalayout.dev/docs/styling/flex-wrap

    Q_D(const FlexboxAttached);

    return static_cast<Flexbox::Wrap>(YGNodeStyleGetFlexWrap(d->node));
}

void FlexboxAttached::setColumnGap(QJSValue value)
{
    if (d_func()->setGap(YGGutterColumn, value)) {
        emit columnGapChanged();
    }
}

void FlexboxAttached::setRowGap(QJSValue value)
{
    if (d_func()->setGap(YGGutterRow, value)) {
        emit rowGapChanged();
    }
}

void FlexboxAttached::setGap(QJSValue value)
{
    if (d_func()->setGap(YGGutterAll, value)) {
        emit gapChanged();
    }
}

QJSValue FlexboxAttached::columnGap() const
{
    return d_func()->gap(YGGutterColumn);
}

QJSValue FlexboxAttached::rowGap() const
{
    return d_func()->gap(YGGutterRow);
}

QJSValue FlexboxAttached::gap() const
{
    return d_func()->gap(YGGutterAll);
}

void FlexboxAttached::setFlex(QJSValue value)
{
    // https://www.yogalayout.dev/docs/styling/flex-basis-grow-shrink

    Q_D(FlexboxAttached);

    const float oldValue = YGNodeStyleGetFlex(d->node);

    if (value.isUndefined()) {
        YGNodeStyleSetFlex(d->node, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetFlex(d->node, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();

        bool ok = false;
        float v = valStr.toFloat(&ok);
        if (ok) {
            YGNodeStyleSetFlex(d->node, v);
        } else {
            qWarning(lcFlexbox, "invalid string: %s", qUtf8Printable(value.toString()));
            return;
        }
    } else {
        qWarning(lcFlexbox, "invalid value: %s", qUtf8Printable(value.toString()));
        return;
    }

    if (YGNodeStyleGetFlex(d->node) != oldValue) {
        emit flexChanged();
    }
}

void FlexboxAttached::setFlexGrow(QJSValue value)
{
    // https://www.yogalayout.dev/docs/styling/flex-basis-grow-shrink

    Q_D(FlexboxAttached);

    const float oldValue = YGNodeStyleGetFlexGrow(d->node);

    if (value.isUndefined()) {
        YGNodeStyleSetFlexGrow(d->node, 0.0);
    } else if (value.isNumber()) {
        YGNodeStyleSetFlexGrow(d->node, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();

        bool ok = false;
        float v = valStr.toFloat(&ok);
        if (ok) {
            YGNodeStyleSetFlexGrow(d->node, v);
        } else {
            qWarning(lcFlexbox, "invalid string: %s", qUtf8Printable(value.toString()));
            return;
        }
    } else {
        qWarning(lcFlexbox, "invalid value: %s", qUtf8Printable(value.toString()));
        return;
    }

    if (YGNodeStyleGetFlexGrow(d->node) != oldValue) {
        emit flexGrowChanged();
    }
}

void FlexboxAttached::setFlexBasis(QJSValue value)
{
    // https://www.yogalayout.dev/docs/styling/flex-basis-grow-shrink

    Q_D(FlexboxAttached);

    const YGValue oldValue = YGNodeStyleGetFlexBasis(d->node);

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
                valStr.chop(1);
                percent = true;
            }

            bool ok = false;
            float v = valStr.toFloat(&ok);
            if (ok) {
                if (percent) {
                    YGNodeStyleSetFlexBasisPercent(d->node, v);
                } else {
                    YGNodeStyleSetFlexBasis(d->node, v);
                }
            } else {
                qWarning(lcFlexbox, "invalid string: %s", qUtf8Printable(value.toString()));
                return;
            }
        }
    } else {
        qWarning(lcFlexbox, "invalid value: %s", qUtf8Printable(value.toString()));
        return;
    }

    if (YGNodeStyleGetFlexBasis(d->node) != oldValue) {
        emit flexBasisChanged();
    }
}

void FlexboxAttached::setFlexShrink(QJSValue value)
{
    // https://www.yogalayout.dev/docs/styling/flex-basis-grow-shrink

    Q_D(FlexboxAttached);

    const float oldValue = YGNodeStyleGetFlexShrink(d->node);

    if (value.isUndefined()) {
        YGNodeStyleSetFlexShrink(d->node, 0.0);
    } else if (value.isNumber()) {
        YGNodeStyleSetFlexShrink(d->node, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();

        bool ok = false;
        float v = valStr.toFloat(&ok);
        if (ok) {
            YGNodeStyleSetFlexShrink(d->node, v);
        } else {
            qWarning(lcFlexbox, "invalid string: %s", qUtf8Printable(value.toString()));
            return;
        }
    } else {
        qWarning(lcFlexbox, "invalid value: %s", qUtf8Printable(value.toString()));
        return;
    }

    if (YGNodeStyleGetFlexShrink(d->node) != oldValue) {
        emit flexShrinkChanged();
    }
}

QJSValue FlexboxAttached::flex() const
{
    // https://www.yogalayout.dev/docs/styling/flex-basis-grow-shrink

    Q_D(const FlexboxAttached);

    const float value = YGNodeStyleGetFlex(d->node);
    if (!YGFloatIsUndefined(value)) {
        return value;
    }

    return {};
}

QJSValue FlexboxAttached::flexGrow() const
{
    // https://www.yogalayout.dev/docs/styling/flex-basis-grow-shrink

    Q_D(const FlexboxAttached);

    return YGNodeStyleGetFlexGrow(d->node);
}

QJSValue FlexboxAttached::flexBasis() const
{
    // https://www.yogalayout.dev/docs/styling/flex-basis-grow-shrink

    Q_D(const FlexboxAttached);

    const YGValue value = YGNodeStyleGetFlexBasis(d->node);
    if (value.unit == YGUnitPoint) {
        return value.value;
    } else if (value.unit == YGUnitPercent) {
        return QStringLiteral("%1%").arg(value.value);
    }
    Q_ASSERT(value.unit != YGUndefined);

    return QStringLiteral("auto");
}

QJSValue FlexboxAttached::flexShrink() const
{
    // https://www.yogalayout.dev/docs/styling/flex-basis-grow-shrink

    Q_D(const FlexboxAttached);

    return YGNodeStyleGetFlexShrink(d->node);
}

void FlexboxAttached::setAspectRatio(QJSValue value)
{
    // https://www.yogalayout.dev/docs/styling/aspect-ratio

    Q_D(FlexboxAttached);

    const float oldValue = YGNodeStyleGetAspectRatio(d->node);

    if (value.isUndefined()) {
        YGNodeStyleSetAspectRatio(d->node, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetAspectRatio(d->node, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();

        bool ok = false;
        float v = valStr.toFloat(&ok);
        if (ok) {
            YGNodeStyleSetAspectRatio(d->node, v);
        } else {
            qWarning(lcFlexbox, "invalid string: %s", qUtf8Printable(value.toString()));
            return;
        }
    } else {
        qWarning(lcFlexbox, "invalid value: %s", qUtf8Printable(value.toString()));
        return;
    }

    if (YGNodeStyleGetAspectRatio(d->node) != oldValue) {
        emit aspectRatioChanged();
    }
}

QJSValue FlexboxAttached::aspectRatio() const
{
    // https://www.yogalayout.dev/docs/styling/aspect-ratio

    Q_D(const FlexboxAttached);

    const float value = YGNodeStyleGetAspectRatio(d->node);

    if (!YGFloatIsUndefined(value)) {
        return value;
    }

    return {};
}

// class Flexbox

FlexboxAttached *Flexbox::qmlAttachedProperties(QObject *attachee)
{
    return new FlexboxAttached(attachee);
}

// class FlexboxAttachedPrivate

FlexboxAttachedPrivate::FlexboxAttachedPrivate()
    : q_ptr(nullptr)
{
}

FlexboxAttachedPrivate::~FlexboxAttachedPrivate()
{
}

void FlexboxAttachedPrivate::itemGeometryChanged(QQuickItem *, QQuickGeometryChange, const QRectF &)
{
    buildLayout();
}

void FlexboxAttachedPrivate::itemChildAdded(QQuickItem *, QQuickItem *child)
{
    YGNodeRef childNode = nullptr;

    FlexboxAttached *attached = qobject_cast<FlexboxAttached *>(qmlAttachedPropertiesObject<Flexbox>(child, false));
    if (attached) {
        childNode = attached->d_func()->node;
    }

    if (childNode) {
        const size_t index = YGNodeGetChildCount(node);
        YGNodeInsertChild(node, childNode, index);
    }
}

void FlexboxAttachedPrivate::itemChildRemoved(QQuickItem *, QQuickItem *child)
{
    YGNodeRef childNode = nullptr;

    FlexboxAttached *attached = qobject_cast<FlexboxAttached *>(qmlAttachedPropertiesObject<Flexbox>(child, false));
    if (attached) {
        childNode = attached->d_func()->node;
    }

    if (childNode) {
        YGNodeRemoveChild(node, childNode);
    }
}

void FlexboxAttachedPrivate::itemParentChanged(QQuickItem *, QQuickItem *parent)
{
    Q_UNUSED(parent);

    buildLayout();
}

void FlexboxAttachedPrivate::itemVisibilityChanged(QQuickItem *item)
{
    Q_Q(FlexboxAttached);

    if (item->isVisible()) {
        q->setDisplay(Flexbox::DisplayFlex);
    } else {
        q->setDisplay(Flexbox::DisplayNone);
    }
}

void FlexboxAttachedPrivate::itemOpacityChanged(QQuickItem *)
{
}

FlexboxAttachedPrivate *FlexboxAttachedPrivate::context(YGNodeConstRef node)
{
    Q_ASSERT(YGNodeGetContext(node) != nullptr);

    return static_cast<FlexboxAttachedPrivate *>(YGNodeGetContext(node));
}

void FlexboxAttachedPrivate::onDirtied(YGNodeConstRef node)
{
    context(node)->buildLayout();
}

void FlexboxAttachedPrivate::buildLayout()
{
    Q_Q(FlexboxAttached);

    if (YGNodeGetParent(node)) {
        return;
    }

    if (itemd->componentComplete && pending.testAndSetOrdered(0, 1)) {
        QTimer::singleShot(0, q, [=] {
            context(node)->calculateLayout();
            pending = 0;
        });
    }
}

void FlexboxAttachedPrivate::calculateLayout()
{
    // Q_Q(Flexbox);

    YGNodeCalculateLayout(node,
                          itemd->widthValid() ? item->width() : YGUndefined,
                          itemd->heightValid() ? item->height() : YGUndefined,
                          YGDirectionInherit);

    applyLayout();
}

void FlexboxAttachedPrivate::applyLayout()
{
    QQuickItem *q = item;
    if (q == nullptr) {
        Q_CHECK_PTR(q);
        return;
    }

    if (!YGNodeGetHasNewLayout(node)) {
        return;
    }
    YGNodeSetHasNewLayout(node, false);

    qreal left = YGNodeLayoutGetLeft(node);
    if (q->x() != left) {
        q->setProperty("x", left);
    }
    qreal top = YGNodeLayoutGetTop(node);
    if (q->y() != top) {
        q->setProperty("y", top);
    }

    if (sizeType == UnknownSize) {
        if (q->inherits("QQuickText")) {
            sizeType = GeometrySize;
        } else {
            sizeType = ImplicitSize;
        }
    }

    if (sizeType == GeometrySize) {
        const qreal width = YGNodeLayoutGetWidth(node);
        if (q->width() != width) {
            q->setProperty("width", width);
        }
        const qreal height = YGNodeLayoutGetHeight(node);
        if (q->height() != height) {
            q->setProperty("height", height);
        }
    } else {
        const qreal width = YGNodeLayoutGetWidth(node);
        if (q->implicitWidth() != width) {
            q->setProperty("implicitWidth", width);
        }
        const qreal height = YGNodeLayoutGetHeight(node);
        if (q->implicitHeight() != height) {
            q->setProperty("implicitHeight", height);
        }
    }

    const size_t count = YGNodeGetChildCount(node);
    for (size_t index = 0; index < count; ++index) {
        YGNodeRef childNode = YGNodeGetChild(node, index);

        context(childNode)->applyLayout();
    }
}

bool FlexboxAttachedPrivate::setMargin(YGEdge edge, QJSValue value)
{
    // https://www.yogalayout.dev/docs/styling/margin-padding-border

    const YGValue oldValue = YGNodeStyleGetMargin(node, edge);

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
                valStr.chop(1);
                percent = true;
            }

            bool ok = false;
            const float val = valStr.toFloat(&ok);
            if (ok) {
                if (percent) {
                    YGNodeStyleSetMarginPercent(node, edge, val);
                } else {
                    YGNodeStyleSetMargin(node, edge, val);
                }
            } else {
                qWarning(lcFlexbox, "invalid String value: %s", qUtf8Printable(value.toString()));
                return false;
            }
        }
    } else {
        qWarning(lcFlexbox, "invalid value: %s", qUtf8Printable(value.toString()));
        return false;
    }

    const YGValue newValue = YGNodeStyleGetMargin(node, edge);

    return (oldValue != newValue);
}

bool FlexboxAttachedPrivate::setPadding(YGEdge edge, QJSValue value)
{
    // https://www.yogalayout.dev/docs/styling/margin-padding-border

    const YGValue oldValue = YGNodeStyleGetPadding(node, edge);

    if (value.isUndefined()) {
        YGNodeStyleSetPadding(node, edge, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetPadding(node, edge, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();

        bool percent = false;
        if (valStr.endsWith('%')) {
            valStr.chop(1);
            percent = true;
        }

        bool ok = false;
        const float val = valStr.toFloat(&ok);
        if (ok) {
            if (percent) {
                YGNodeStyleSetPaddingPercent(node, edge, val);
            } else {
                YGNodeStyleSetPadding(node, edge, val);
            }
        } else {
            qWarning(lcFlexbox, "invalid String value: %s", qUtf8Printable(value.toString()));
            return false;
        }
    } else {
        qWarning(lcFlexbox, "invalid value: %s", qUtf8Printable(value.toString()));
        return false;
    }

    const YGValue newValue = YGNodeStyleGetPadding(node, edge);

    return (oldValue != newValue);
}

bool FlexboxAttachedPrivate::setBorder(YGEdge edge, QJSValue value)
{
    // https://www.yogalayout.dev/docs/styling/margin-padding-border

    const float oldValue = YGNodeStyleGetBorder(node, edge);

    if (value.isUndefined()) {
        YGNodeStyleSetBorder(node, edge, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetBorder(node, edge, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();

        bool ok = false;
        const float val = valStr.toFloat(&ok);
        if (ok) {
            YGNodeStyleSetBorder(node, edge, val);
        } else {
            qWarning(lcFlexbox, "invalid String value: %s", qUtf8Printable(value.toString()));
            return false;
        }
    } else {
        qWarning(lcFlexbox, "invalid value: %s", qUtf8Printable(value.toString()));
        return false;
    }

    const float newValue = YGNodeStyleGetBorder(node, edge);

    return (oldValue != newValue);
}

QJSValue FlexboxAttachedPrivate::margin(YGEdge edge) const
{
    // https://www.yogalayout.dev/docs/styling/margin-padding-border

    const YGValue value = YGNodeStyleGetMargin(node, edge);

    switch (value.unit) {
    case YGUnitUndefined:
        return {};
    case YGUnitPoint:
        return value.value;
    case YGUnitPercent:
        return QStringLiteral("%1%").arg(value.value);
    case YGUnitAuto:
        return {};
    default:
        Q_UNREACHABLE();
    }
}

QJSValue FlexboxAttachedPrivate::padding(YGEdge edge) const
{
    // https://www.yogalayout.dev/docs/styling/margin-padding-border

    const YGValue value = YGNodeStyleGetPadding(node, edge);

    switch (value.unit) {
    case YGUnitUndefined:
        return {};
    case YGUnitPoint:
        return value.value;
    case YGUnitPercent:
        return QStringLiteral("%1%").arg(value.value);
    case YGUnitAuto:
        return {};
    default:
        Q_UNREACHABLE();
    }
}

QJSValue FlexboxAttachedPrivate::border(YGEdge edge) const
{
    // https://www.yogalayout.dev/docs/styling/margin-padding-border

    const float value = YGNodeStyleGetBorder(node, edge);

    if (!YGFloatIsUndefined(value)) {
        return value;
    }

    return {};
}

bool FlexboxAttachedPrivate::setPosition(YGEdge edge, QJSValue value)
{
    // https://yogalayout.com/docs/absolute-relative-layout

    const YGValue oldValue = YGNodeStyleGetPosition(node, edge);

    if (value.isUndefined()) {
        YGNodeStyleSetPosition(node, edge, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetPosition(node, edge, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();

        bool percent = false;
        if (valStr.endsWith('%')) {
            valStr.chop(1);
            percent = true;
        }

        bool ok = false;
        const float val = valStr.toFloat(&ok);
        if (ok) {
            if (percent) {
                YGNodeStyleSetPositionPercent(node, edge, val);
            } else {
                YGNodeStyleSetPosition(node, edge, val);
            }
        } else {
            qWarning(lcFlexbox, "invalid String value: %s", qUtf8Printable(value.toString()));
            return false;
        }
    } else {
        qWarning(lcFlexbox, "invalid value: %s", qUtf8Printable(value.toString()));
        return false;
    }

    const YGValue newValue = YGNodeStyleGetPosition(node, edge);
    return (oldValue != newValue);
}

QJSValue FlexboxAttachedPrivate::position(YGEdge edge) const
{
    // https://yogalayout.com/docs/absolute-relative-layout

    const YGValue value = YGNodeStyleGetPosition(node, edge);

    switch (value.unit) {
    case YGUnitUndefined:
        return {};
    case YGUnitPoint:
        return value.value;
    case YGUnitPercent:
        return QStringLiteral("%1%").arg(value.value);
    case YGUnitAuto:
        return {};
    default:
        Q_UNREACHABLE();
    }
}

bool FlexboxAttachedPrivate::setGap(YGGutter gutter, QJSValue value)
{
    // no document

    const float oldValue = YGNodeStyleGetGap(node, gutter);

    if (value.isUndefined()) {
        YGNodeStyleSetGap(node, gutter, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetGap(node, gutter, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();

        bool ok = false;
        const float val = valStr.toFloat(&ok);
        if (ok) {
            YGNodeStyleSetGap(node, gutter, val);
        } else {
            qWarning(lcFlexbox, "invalid String value: %s", qUtf8Printable(value.toString()));
            return false;
        }
    } else {
        qWarning(lcFlexbox, "invalid value: %s", qUtf8Printable(value.toString()));
        return false;
    }

    const float newValue = YGNodeStyleGetGap(node, gutter);
    return (oldValue != newValue);
}

QJSValue FlexboxAttachedPrivate::gap(YGGutter gutter) const
{
    // no document

    const float value = YGNodeStyleGetGap(node, gutter);

    if (!YGFloatIsUndefined(value)) {
        return value;
    }

    return {};
}
