#include "CxFlex.h"
#include "CxFlex_p.h"

#include "CxFlexSettings.h"
#include "CxFlexSettings_p.h"

// class CxYogaNode

CxYogaNode::CxYogaNode()
{
}

CxYogaNode::~CxYogaNode()
{
}

YGNodeRef CxYogaNode::makeNode()
{
    if (node == nullptr) {
        node = YGNodeNewWithConfig(CxFlexSettingsPrivate::defaultConfig());

        initNode(node);
    }

    return node;
}

void CxYogaNode::cleanupNode()
{
    if (node) {
        YGNodeRef parentNode = YGNodeGetParent(node);
        if (parentNode) {
            YGNodeRemoveChild(parentNode, node);
        }

        YGNodeFree(node);
        node = nullptr;
    }
}

void CxYogaNode::initNode(YGNodeRef node)
{
    YGNodeSetContext(node, this);
    YGNodeSetDirtiedFunc(node, &CxYogaNode::onDirtied);
}

CxYogaNode *CxYogaNode::context(YGNodeRef node)
{
    Q_ASSERT(YGNodeGetContext(node) != nullptr);

    return static_cast<CxYogaNode *>(YGNodeGetContext(node));
}

void CxYogaNode::onDirtied(YGNodeRef node)
{
    context(node)->buildLayout();
}

void CxYogaNode::buildLayout()
{
}

void CxYogaNode::applyLayout()
{
}

bool CxYogaNode::setPreferredWidth(const QJSValue &value)
{
    // https://yogalayout.com/docs/width-height

    makeNode();

    const YGValue oldValue = YGNodeStyleGetWidth(node);

    if (value.isUndefined()) {
        YGNodeStyleSetWidthAuto(node);
    } else if (value.isNumber()) {
        YGNodeStyleSetWidth(node, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();
        if (valStr == "auto") {
            YGNodeStyleSetWidthAuto(node);
        } else {
            bool percent = false;
            if (valStr.endsWith("%")) {
                valStr.chop(1);
                percent = true;
            }

            bool ok = false;
            float v = valStr.toFloat(&ok);
            if (ok) {
                if (percent) {
                    YGNodeStyleSetWidthPercent(node, v);
                } else {
                    YGNodeStyleSetWidth(node, v);
                }
            } else {
                qWarning(loggingCategory(), "invalid string value: %s", qUtf8Printable(value.toString()));
                return false;
            }
        }
    } else {
        qWarning(loggingCategory(), "invalid value: %s", qUtf8Printable(value.toString()));
        return false;
    }

    return (YGNodeStyleGetWidth(node) != oldValue);
}

bool CxYogaNode::setPreferredHeight(const QJSValue &value)
{
    // https://yogalayout.com/docs/width-height

    makeNode();

    const YGValue oldValue = YGNodeStyleGetHeight(node);

    if (value.isUndefined()) {
        YGNodeStyleSetHeightAuto(node);
    } else if (value.isNumber()) {
        YGNodeStyleSetHeight(node, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();
        if (valStr == "auto") {
            YGNodeStyleSetHeightAuto(node);
        } else {
            bool percent = false;
            if (valStr.endsWith("%")) {
                valStr.chop(1);
                percent = true;
            }

            bool ok = false;
            float v = valStr.toFloat(&ok);
            if (ok) {
                if (percent) {
                    YGNodeStyleSetHeightPercent(node, v);
                } else {
                    YGNodeStyleSetHeight(node, v);
                }
            } else {
                qWarning(loggingCategory(), "invalid string value: %s", qUtf8Printable(value.toString()));
                return false;
            }
        }
    } else {
        qWarning(loggingCategory(), "invalid value: %s", qUtf8Printable(value.toString()));
        return false;
    }

    return (YGNodeStyleGetHeight(node) != oldValue);
}

QJSValue CxYogaNode::preferredWidth() const
{
    // https://yogalayout.com/docs/width-height

    if (node) {
        const YGValue value = YGNodeStyleGetWidth(node);
        if (value.unit == YGUnitPoint) {
            return value.value;
        } else if (value.unit == YGUnitPercent) {
            return QStringLiteral("%1%").arg(value.value);
        }
        Q_ASSERT(value.unit != YGUnitUndefined);
    }

    return QStringLiteral("auto");
}

QJSValue CxYogaNode::preferredHeight() const
{
    // https://yogalayout.com/docs/width-height

    if (node) {
        const YGValue value = YGNodeStyleGetHeight(node);
        if (value.unit == YGUnitPoint) {
            return value.value;
        } else if (value.unit == YGUnitPercent) {
            return QStringLiteral("%1%").arg(value.value);
        }
        Q_ASSERT(value.unit != YGUnitUndefined);
    }

    return QStringLiteral("auto");
}

bool CxYogaNode::setMinimumWidth(const QJSValue &value)
{
    // https://yogalayout.com/docs/min-max

    makeNode();

    const YGValue oldValue = YGNodeStyleGetMinWidth(node);

    if (value.isUndefined()) {
        YGNodeStyleSetMinWidth(node, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetMinWidth(node, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();

        bool percent = false;
        if (valStr.endsWith("%")) {
            valStr.chop(1);
            percent = true;
        }

        bool ok = false;
        float v = valStr.toFloat(&ok);
        if (ok) {
            if (percent) {
                YGNodeStyleSetMinWidthPercent(node, v);
            } else {
                YGNodeStyleSetMinWidth(node, v);
            }
        } else {
            qWarning(loggingCategory(), "invalid string value: %s", qUtf8Printable(value.toString()));
            return false;
        }
    } else {
        qWarning(loggingCategory(), "invalid value: %s", qUtf8Printable(value.toString()));
        return false;
    }

    return (YGNodeStyleGetMinWidth(node) != oldValue);
}

bool CxYogaNode::setMinimumHeight(const QJSValue &value)
{
    // https://yogalayout.com/docs/min-max

    makeNode();

    const YGValue oldValue = YGNodeStyleGetMinHeight(node);

    if (value.isUndefined()) {
        YGNodeStyleSetMinHeight(node, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetMinHeight(node, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();

        bool percent = false;
        if (valStr.endsWith("%")) {
            valStr.chop(1);
            percent = true;
        }

        bool ok = false;
        float v = valStr.toFloat(&ok);
        if (ok) {
            if (percent) {
                YGNodeStyleSetMinHeightPercent(node, v);
            } else {
                YGNodeStyleSetMinHeight(node, v);
            }
        } else {
            qWarning(loggingCategory(), "invalid string value: %s", qUtf8Printable(value.toString()));
            return false;
        }
    } else {
        qWarning(loggingCategory(), "invalid value: %s", qUtf8Printable(value.toString()));
        return false;
    }

    return (YGNodeStyleGetMinHeight(node) != oldValue);
}

bool CxYogaNode::setMaximumWidth(const QJSValue &value)
{
    // https://yogalayout.com/docs/min-max

    makeNode();

    const YGValue oldValue = YGNodeStyleGetMaxWidth(node);

    if (value.isUndefined()) {
        YGNodeStyleSetMaxWidth(node, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetMaxWidth(node, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();

        bool percent = false;
        if (valStr.endsWith("%")) {
            valStr.chop(1);
            percent = true;
        }

        bool ok = false;
        float v = valStr.toFloat(&ok);
        if (ok) {
            if (percent) {
                YGNodeStyleSetMaxWidthPercent(node, v);
            } else {
                YGNodeStyleSetMaxWidth(node, v);
            }
        } else {
            qWarning(loggingCategory(), "invalid String value: %s", qUtf8Printable(value.toString()));
            return false;
        }
    } else {
        qWarning(loggingCategory(), "invalid value: %s", qUtf8Printable(value.toString()));
        return false;
    }

    return (YGNodeStyleGetMaxWidth(node) != oldValue);
}

bool CxYogaNode::setMaximumHeight(const QJSValue &value)
{
    // https://yogalayout.com/docs/min-max

    makeNode();

    const YGValue oldValue = YGNodeStyleGetMaxHeight(node);

    if (value.isUndefined()) {
        YGNodeStyleSetMaxHeight(node, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetMaxHeight(node, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();

        bool percent = false;
        if (valStr.endsWith("%")) {
            valStr.chop(1);
            percent = true;
        }

        bool ok = false;
        float v = valStr.toFloat(&ok);
        if (ok) {
            if (percent) {
                YGNodeStyleSetMaxHeightPercent(node, v);
            } else {
                YGNodeStyleSetMaxHeight(node, v);
            }
        } else {
            qWarning(loggingCategory(), "axvalid String value: %s", qUtf8Printable(value.toString()));
            return false;
        }
    } else {
        qWarning(loggingCategory(), "axvalid value: %s", qUtf8Printable(value.toString()));
        return false;
    }

    return (YGNodeStyleGetMaxHeight(node) != oldValue);
}

QJSValue CxYogaNode::minimumWidth() const
{
    // https://yogalayout.com/docs/min-max

    if (node) {
        const YGValue value = YGNodeStyleGetMinWidth(node);
        if (value.unit == YGUnitPoint) {
            return value.value;
        } else if (value.unit == YGUnitPercent) {
            return QStringLiteral("%1%").arg(value.value);
        }
        Q_ASSERT(value.unit != YGUnitAuto);
    }

    return QJSValue();
}

QJSValue CxYogaNode::minimumHeight() const
{
    // https://yogalayout.com/docs/min-max

    if (node) {
        const YGValue value = YGNodeStyleGetMinHeight(node);
        if (value.unit == YGUnitPoint) {
            return value.value;
        } else if (value.unit == YGUnitPercent) {
            return QStringLiteral("%1%").arg(value.value);
        }
        Q_ASSERT(value.unit != YGUnitAuto);
    }

    return QJSValue();
}

QJSValue CxYogaNode::maximumWidth() const
{
    // https://yogalayout.com/docs/min-max

    if (node) {
        const YGValue value = YGNodeStyleGetMaxWidth(node);
        if (value.unit == YGUnitPoint) {
            return value.value;
        } else if (value.unit == YGUnitPercent) {
            return QStringLiteral("%1%").arg(value.value);
        }
        Q_ASSERT(value.unit != YGUnitAuto);
    }

    return QJSValue();
}

QJSValue CxYogaNode::maximumHeight() const
{
    // https://yogalayout.com/docs/min-max

    if (node) {
        const YGValue value = YGNodeStyleGetMaxHeight(node);
        if (value.unit == YGUnitPoint) {
            return value.value;
        } else if (value.unit == YGUnitPercent) {
            return QStringLiteral("%1%").arg(value.value);
        }
        Q_ASSERT(value.unit != YGUnitAuto);
    }

    return QJSValue();
}

bool CxYogaNode::setMargin(YGEdge edge, const QJSValue &value)
{
    // https://yogalayout.com/docs/margins-paddings-borders

    makeNode();

    const YGValue oldValue = YGNodeStyleGetMargin(node, edge);

    if (value.isUndefined()) {
        YGNodeStyleSetMargin(node, edge, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetMargin(node, edge, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();
        if (valStr == "auto") {
            YGNodeStyleSetMarginAuto(node, edge);
        } else {
            bool percent = false;
            if (valStr.endsWith("%")) {
                valStr.chop(1);
                percent = true;
            }

            bool ok = false;
            float v = valStr.toFloat(&ok);
            if (ok) {
                if (percent) {
                    YGNodeStyleSetMarginPercent(node, edge, v);
                } else {
                    YGNodeStyleSetMargin(node, edge, v);
                }
            } else {
                qWarning(loggingCategory(), "invalid string value: %s", qUtf8Printable(value.toString()));
                return false;
            }
        }
    } else {
        qWarning(loggingCategory(), "invalid value: %s", qUtf8Printable(value.toString()));
        return false;
    }

    return (YGNodeStyleGetMargin(node, edge) != oldValue);
}

bool CxYogaNode::setPadding(YGEdge edge, const QJSValue &value)
{
    // https://yogalayout.com/docs/margins-paddings-borders

    makeNode();

    const YGValue oldValue = YGNodeStyleGetPadding(node, edge);

    if (value.isUndefined()) {
        YGNodeStyleSetPadding(node, edge, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetPadding(node, edge, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();

        bool percent = false;
        if (valStr.endsWith("%")) {
            valStr.chop(1);
            percent = true;
        }

        bool ok = false;
        float v = valStr.toFloat(&ok);
        if (ok) {
            if (percent) {
                YGNodeStyleSetPaddingPercent(node, edge, v);
            } else {
                YGNodeStyleSetPadding(node, edge, v);
            }
        } else {
            qWarning(loggingCategory(), "invalid string value: %s", qUtf8Printable(value.toString()));
            return false;
        }
    } else {
        qWarning(loggingCategory(), "invalid value: %s", qUtf8Printable(value.toString()));
        return false;
    }

    return (YGNodeStyleGetPadding(node, edge) != oldValue);
}

bool CxYogaNode::setBorder(YGEdge edge, const QJSValue &value)
{
    // https://yogalayout.com/docs/margins-paddings-borders

    makeNode();

    const float oldValue = YGNodeStyleGetBorder(node, edge);

    if (value.isUndefined()) {
        YGNodeStyleSetBorder(node, edge, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetBorder(node, edge, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();

        bool ok = false;
        float v = valStr.toFloat(&ok);
        if (ok) {
            YGNodeStyleSetBorder(node, edge, v);
        } else {
            qWarning(loggingCategory(), "invalid string value: %s", qUtf8Printable(value.toString()));
            return false;
        }
    } else {
        qWarning(loggingCategory(), "invalid value: %s", qUtf8Printable(value.toString()));
        return false;
    }

    return (YGNodeStyleGetBorder(node, edge) != oldValue);
}

QJSValue CxYogaNode::margin(YGEdge edge) const
{
    // https://yogalayout.com/docs/margins-paddings-borders

    if (node) {
        const YGValue value = YGNodeStyleGetMargin(node, edge);
        if (value.unit == YGUnitPoint) {
            return value.value;
        } else if (value.unit == YGUnitPercent) {
            return QStringLiteral("%1%").arg(value.value);
        } else if (value.unit == YGUnitAuto) {
            return QStringLiteral("auto");
        }
    }

    return QJSValue();
}

QJSValue CxYogaNode::padding(YGEdge edge) const
{
    // https://yogalayout.com/docs/margins-paddings-borders

    if (node) {
        const YGValue value = YGNodeStyleGetPadding(node, edge);
        if (value.unit == YGUnitPoint) {
            return value.value;
        } else if (value.unit == YGUnitPercent) {
            return QStringLiteral("%1%").arg(value.value);
        }
        Q_ASSERT(value.unit != YGUnitAuto);
    }

    return QJSValue();
}

QJSValue CxYogaNode::border(YGEdge edge) const
{
    // https://yogalayout.com/docs/margins-paddings-borders

    if (node) {
        const float value = YGNodeStyleGetBorder(node, edge);
        if (!YGFloatIsUndefined(value)) {
            return value;
        }
    }

    return QJSValue();
}

bool CxYogaNode::setDirection(CxFlex::Direction value)
{
    // https://yogalayout.com/docs/layout-direction

    makeNode();

    const YGDirection oldValue = YGNodeStyleGetDirection(node);
    YGNodeStyleSetDirection(node, static_cast<YGDirection>(value));
    const YGDirection newValue = YGNodeStyleGetDirection(node);

    return (oldValue != newValue);
}

bool CxYogaNode::setPosition(CxFlex::Position value)
{
    // https://yogalayout.com/docs/absolute-relative-layout

    makeNode();

    const YGPositionType oldValue = YGNodeStyleGetPositionType(node);
    YGNodeStyleSetPositionType(node, static_cast<YGPositionType>(value));
    const YGPositionType newValue = YGNodeStyleGetPositionType(node);

    return (oldValue != newValue);
}

bool CxYogaNode::setDisplay(CxFlex::Display value)
{
    // no document

    makeNode();

    const YGDisplay oldValue = YGNodeStyleGetDisplay(node);
    YGNodeStyleSetDisplay(node, static_cast<YGDisplay>(value));
    const YGDisplay newValue = YGNodeStyleGetDisplay(node);

    return (oldValue != newValue);
}

bool CxYogaNode::setOverflow(CxFlex::Overflow value)
{
    // no document

    makeNode();

    const YGOverflow oldValue = YGNodeStyleGetOverflow(node);
    YGNodeStyleSetOverflow(node, static_cast<YGOverflow>(value));
    const YGOverflow newValue = YGNodeStyleGetOverflow(node);

    return (oldValue != newValue);
}

CxFlex::Direction CxYogaNode::direction() const
{
    // https://yogalayout.com/docs/layout-direction

    if (node == nullptr) { // test case confirmed
        return CxFlex::DirectionInherit;
    }

    return static_cast<CxFlex::Direction>(YGNodeStyleGetDirection(node));
}

CxFlex::Position CxYogaNode::position() const
{
    // https://yogalayout.com/docs/absolute-relative-layout

    if (node == nullptr) { // test case confirmed
        return CxFlex::PositionStatic;
    }

    return static_cast<CxFlex::Position>(YGNodeStyleGetPositionType(node));
}

CxFlex::Display CxYogaNode::display() const
{
    // no document

    if (node == nullptr) { // test case confirmed
        return CxFlex::DisplayFlex;
    }

    return static_cast<CxFlex::Display>(YGNodeStyleGetDisplay(node));
}

CxFlex::Overflow CxYogaNode::overflow() const
{
    // no document

    if (node == nullptr) { // test case confirmed
        return CxFlex::OverflowVisible;
    }

    return static_cast<CxFlex::Overflow>(YGNodeStyleGetOverflow(node));
}

bool CxYogaNode::setPosition(YGEdge edge, const QJSValue &value)
{
    // https://yogalayout.com/docs/absolute-relative-layout

    makeNode();

    const YGValue oldValue = YGNodeStyleGetPosition(node, edge);

    if (value.isUndefined()) {
        YGNodeStyleSetPosition(node, edge, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetPosition(node, edge, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();

        bool percent = false;
        if (valStr.endsWith("%")) {
            valStr.chop(1);
            percent = true;
        }

        bool ok = false;
        float v = valStr.toFloat(&ok);
        if (ok) {
            if (percent) {
                YGNodeStyleSetPositionPercent(node, edge, v);
            } else {
                YGNodeStyleSetPosition(node, edge, v);
            }
        } else {
            qWarning(loggingCategory(), "invalid string value: %s", qUtf8Printable(value.toString()));
            return false;
        }
    } else {
        qWarning(loggingCategory(), "invalid value: %s", qUtf8Printable(value.toString()));
        return false;
    }

    return (YGNodeStyleGetPosition(node, edge) != oldValue);
}

QJSValue CxYogaNode::position(YGEdge edge) const
{
    // https://yogalayout.com/docs/absolute-relative-layout

    if (node) {
        const YGValue value = YGNodeStyleGetPosition(node, edge);
        if (value.unit == YGUnitPoint) {
            return value.value;
        } else if (value.unit == YGUnitPercent) {
            return QStringLiteral("%1%").arg(value.value);
        }
        Q_ASSERT(value.unit != YGUnitAuto);
    }

    return QJSValue();
}

bool CxYogaNode::setFlexDirection(CxFlex::FlexDirection value)
{
    // https://yogalayout.com/docs/flex-direction

    makeNode();

    const YGFlexDirection oldValue = YGNodeStyleGetFlexDirection(node);
    YGNodeStyleSetFlexDirection(node, static_cast<YGFlexDirection>(value));
    const YGFlexDirection newValue = YGNodeStyleGetFlexDirection(node);

    return (oldValue != newValue);
}

bool CxYogaNode::setJustifyContent(CxFlex::Justify value)
{
    // https://yogalayout.com/docs/justify-content

    makeNode();

    const YGJustify oldValue = YGNodeStyleGetJustifyContent(node);
    YGNodeStyleSetJustifyContent(node, static_cast<YGJustify>(value));
    const YGJustify newValue = YGNodeStyleGetJustifyContent(node);

    return (oldValue != newValue);
}

bool CxYogaNode::setAlignContent(CxFlex::Align value)
{
    // https://yogalayout.com/docs/align-content

    makeNode();

    const YGAlign oldValue = YGNodeStyleGetAlignContent(node);
    YGNodeStyleSetAlignContent(node, static_cast<YGAlign>(value));
    const YGAlign newValue = YGNodeStyleGetAlignContent(node);

    return (oldValue != newValue);
}

bool CxYogaNode::setAlignItems(CxFlex::Align value)
{
    // https://yogalayout.com/docs/align-items

    makeNode();

    const YGAlign oldValue = YGNodeStyleGetAlignItems(node);
    YGNodeStyleSetAlignItems(node, static_cast<YGAlign>(value));
    const YGAlign newValue = YGNodeStyleGetAlignItems(node);

    return (oldValue != newValue);
}

bool CxYogaNode::setAlignSelf(CxFlex::Align value)
{
    // https://yogalayout.com/docs/align-items

    makeNode();

    const YGAlign oldValue = YGNodeStyleGetAlignSelf(node);
    YGNodeStyleSetAlignSelf(node, static_cast<YGAlign>(value));
    const YGAlign newValue = YGNodeStyleGetAlignSelf(node);

    return (oldValue != newValue);
}

bool CxYogaNode::setFlexWrap(CxFlex::Wrap value)
{
    // https://yogalayout.com/docs/flex-wrap

    makeNode();

    const YGWrap oldValue = YGNodeStyleGetFlexWrap(node);
    YGNodeStyleSetFlexWrap(node, static_cast<YGWrap>(value));
    const YGWrap newValue = YGNodeStyleGetFlexWrap(node);

    return (oldValue != newValue);
}

CxFlex::FlexDirection CxYogaNode::flexDirection() const
{
    // https://yogalayout.com/docs/flex-direction

    if (node == nullptr) { // test case confirmed
        return CxFlex::FlexDirectionColumn;
    }

    return static_cast<CxFlex::FlexDirection>(YGNodeStyleGetFlexDirection(node));
}

CxFlex::Justify CxYogaNode::justifyContent() const
{
    // https://yogalayout.com/docs/justify-content

    if (node == nullptr) { // test case confirmed
        return CxFlex::JustifyFlexStart;
    }

    return static_cast<CxFlex::Justify>(YGNodeStyleGetJustifyContent(node));
}

CxFlex::Align CxYogaNode::alignContent() const
{
    // https://yogalayout.com/docs/align-content

    if (node == nullptr) { // test case confirmed
        return CxFlex::AlignFlexStart;
    }

    return static_cast<CxFlex::Align>(YGNodeStyleGetAlignContent(node));
}

CxFlex::Align CxYogaNode::alignItems() const
{
    // https://yogalayout.com/docs/align-items

    if (node == nullptr) { // test case confirmed
        return CxFlex::AlignStretch;
    }

    return static_cast<CxFlex::Align>(YGNodeStyleGetAlignItems(node));
}

CxFlex::Align CxYogaNode::alignSelf() const
{
    // https://yogalayout.com/docs/align-items

    if (node == nullptr) { // test case confirmed
        return CxFlex::AlignAuto;
    }

    return static_cast<CxFlex::Align>(YGNodeStyleGetAlignSelf(node));
}

CxFlex::Wrap CxYogaNode::flexWrap() const
{
    // https://yogalayout.com/docs/flex-wrap

    if (node == nullptr) { // test case confirmed
        return CxFlex::WrapNoWrap;
    }

    return static_cast<CxFlex::Wrap>(YGNodeStyleGetFlexWrap(node));
}

bool CxYogaNode::setGap(YGGutter gutter, const QJSValue &value)
{
    // no document

    makeNode();

    const float oldValue = YGNodeStyleGetGap(node, gutter);

    if (value.isUndefined()) {
        YGNodeStyleSetGap(node, gutter, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetGap(node, gutter, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();

        bool ok = false;
        float v = valStr.toFloat(&ok);
        if (ok) {
            YGNodeStyleSetGap(node, gutter, v);
        } else {
            qWarning(loggingCategory(), "invalid string value: %s", qUtf8Printable(value.toString()));
            return false;
        }
    } else {
        qWarning(loggingCategory(), "invalid value: %s", qUtf8Printable(value.toString()));
        return false;
    }

    return (YGNodeStyleGetGap(node, gutter) != oldValue);
}

QJSValue CxYogaNode::gap(YGGutter gutter) const
{
    // no document

    if (node) {
        const float value = YGNodeStyleGetGap(node, gutter);
        if (!YGFloatIsUndefined(value)) {
            return value;
        }
    }

    return QJSValue();
}

bool CxYogaNode::setFlex(const QJSValue &value)
{
    // https://yogalayout.com/docs/flex

    makeNode();

    const float oldValue = YGNodeStyleGetFlex(node);

    if (value.isUndefined()) {
        YGNodeStyleSetFlex(node, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetFlex(node, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();

        bool ok = false;
        float v = valStr.toFloat(&ok);
        if (ok) {
            YGNodeStyleSetFlex(node, v);
        } else {
            qWarning(loggingCategory(), "invalid string: %s", qUtf8Printable(value.toString()));
            return false;
        }
    } else {
        qWarning(loggingCategory(), "invalid value: %s", qUtf8Printable(value.toString()));
        return false;
    }

    return (YGNodeStyleGetFlex(node) != oldValue);
}

bool CxYogaNode::setFlexGrow(const QJSValue &value)
{
    // https://yogalayout.com/docs/flex

    makeNode();

    const float oldValue = YGNodeStyleGetFlexGrow(node);

    if (value.isUndefined()) {
        YGNodeStyleSetFlexGrow(node, 0.0);
    } else if (value.isNumber()) {
        YGNodeStyleSetFlexGrow(node, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();

        bool ok = false;
        float v = valStr.toFloat(&ok);
        if (ok) {
            YGNodeStyleSetFlexGrow(node, v);
        } else {
            qWarning(loggingCategory(), "invalid string: %s", qUtf8Printable(value.toString()));
            return false;
        }
    } else {
        qWarning(loggingCategory(), "invalid value: %s", qUtf8Printable(value.toString()));
        return false;
    }

    return (YGNodeStyleGetFlexGrow(node) != oldValue);
}

bool CxYogaNode::setFlexBasis(const QJSValue &value)
{
    // https://yogalayout.com/docs/flex

    makeNode();

    const YGValue oldValue = YGNodeStyleGetFlexBasis(node);

    if (value.isUndefined()) {
        YGNodeStyleSetFlexBasisAuto(node);
    } else if (value.isNumber()) {
        YGNodeStyleSetFlexBasis(node, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();
        if (valStr == "auto") {
            YGNodeStyleSetFlexBasisAuto(node);
        } else {
            bool percent = false;
            if (valStr.endsWith("%")) {
                valStr.chop(1);
                percent = true;
            }

            bool ok = false;
            float v = valStr.toFloat(&ok);
            if (ok) {
                if (percent) {
                    YGNodeStyleSetFlexBasisPercent(node, v);
                } else {
                    YGNodeStyleSetFlexBasis(node, v);
                }
            } else {
                qWarning(loggingCategory(), "invalid string: %s", qUtf8Printable(value.toString()));
                return false;
            }
        }
    } else {
        qWarning(loggingCategory(), "invalid value: %s", qUtf8Printable(value.toString()));
        return false;
    }

    return (YGNodeStyleGetFlexBasis(node) != oldValue);
}

bool CxYogaNode::setFlexShrink(const QJSValue &value)
{
    // https://yogalayout.com/docs/flex

    makeNode();

    const float oldValue = YGNodeStyleGetFlexShrink(node);

    if (value.isUndefined()) {
        YGNodeStyleSetFlexShrink(node, 0.0);
    } else if (value.isNumber()) {
        YGNodeStyleSetFlexShrink(node, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();

        bool ok = false;
        float v = valStr.toFloat(&ok);
        if (ok) {
            YGNodeStyleSetFlexShrink(node, v);
        } else {
            qWarning(loggingCategory(), "invalid string: %s", qUtf8Printable(value.toString()));
            return false;
        }
    } else {
        qWarning(loggingCategory(), "invalid value: %s", qUtf8Printable(value.toString()));
        return false;
    }

    return (YGNodeStyleGetFlexShrink(node) != oldValue);
}

QJSValue CxYogaNode::flex() const
{
    // https://yogalayout.com/docs/flex

    if (node) { // test case confirmed
        const float value = YGNodeStyleGetFlex(node);
        if (!YGFloatIsUndefined(value)) {
            return value;
        }
    }

    return QJSValue();
}

QJSValue CxYogaNode::flexGrow() const
{
    // https://yogalayout.com/docs/flex

    if (node == nullptr) { // test case confirmed
        return 0.0;
    }

    return YGNodeStyleGetFlexGrow(node);
}

QJSValue CxYogaNode::flexBasis() const
{
    // https://yogalayout.com/docs/flex

    if (node) {
        const YGValue value = YGNodeStyleGetFlexBasis(node);
        if (value.unit == YGUnitPoint) {
            return value.value;
        } else if (value.unit == YGUnitPercent) {
            return QStringLiteral("%1%").arg(value.value);
        }
        Q_ASSERT(value.unit != YGUndefined);
    }

    return QStringLiteral("auto");
}

QJSValue CxYogaNode::flexShrink() const
{
    // https://yogalayout.com/docs/flex

    if (node == nullptr) { // test case confirmed
        return 0.0;
    }

    return YGNodeStyleGetFlexShrink(node);
}

bool CxYogaNode::setAspectRatio(const QJSValue &value)
{
    // https://yogalayout.com/docs/aspect-ratio

    makeNode();

    const float oldValue = YGNodeStyleGetAspectRatio(node);

    if (value.isUndefined()) {
        YGNodeStyleSetAspectRatio(node, YGUndefined);
    } else if (value.isNumber()) {
        YGNodeStyleSetAspectRatio(node, value.toNumber());
    } else if (value.isString()) {
        QString valStr = value.toString();

        bool ok = false;
        float v = valStr.toFloat(&ok);
        if (ok) {
            YGNodeStyleSetAspectRatio(node, v);
        } else {
            qWarning(loggingCategory(), "invalid string: %s", qUtf8Printable(value.toString()));
            return false;
        }
    } else {
        qWarning(loggingCategory(), "invalid value: %s", qUtf8Printable(value.toString()));
        return false;
    }

    return (YGNodeStyleGetAspectRatio(node) != oldValue);
}

QJSValue CxYogaNode::aspectRatio() const
{
    // https://yogalayout.com/docs/aspect-ratio

    if (node) {
        const YGValue value = YGNodeStyleGetFlexBasis(node);
        if (value.unit == YGUnitPoint) {
            return value.value;
        } else if (value.unit == YGUnitPercent) {
            return QStringLiteral("%1%").arg(value.value);
        }
        Q_ASSERT(value.unit != YGUndefined);
    }

    return QStringLiteral("auto");
}
