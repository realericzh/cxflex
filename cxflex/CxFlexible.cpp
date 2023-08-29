#include "CxFlexible.h"
#include "CxFlexible_p.h"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(lcFlexNode, "CxFlexible")

// class CxFlexible

CxFlexible::CxFlexible(QObject *parent)
    : QObject(parent)
    , d_ptr(new CxFlexiblePrivate())
{
    d_ptr->q_ptr = this;
}

CxFlexible::~CxFlexible()
{
    d_func()->cleanupNode();
}

void CxFlexible::setPreferredWidth(const QJSValue &value)
{
    if (d_func()->setPreferredWidth(value)) {
        emit preferredWidthChanged();
    }
}

void CxFlexible::setPreferredHeight(const QJSValue &value)
{
    if (d_func()->setPreferredHeight(value)) {
        emit preferredHeightChanged();
    }
}

QJSValue CxFlexible::preferredWidth() const
{
    return d_func()->preferredWidth();
}

QJSValue CxFlexible::preferredHeight() const
{
    return d_func()->preferredHeight();
}

void CxFlexible::setMinimumWidth(const QJSValue &value)
{
    if (d_func()->setMinimumWidth((value))) {
        emit minimumWidthChanged();
    }
}

void CxFlexible::setMinimumHeight(const QJSValue &value)
{
    if (d_func()->setMinimumHeight((value))) {
        emit minimumHeightChanged();
    }
}

void CxFlexible::setMaximumWidth(const QJSValue &value)
{
    if (d_func()->setMaximumWidth((value))) {
        emit maximumWidthChanged();
    }
}

void CxFlexible::setMaximumHeight(const QJSValue &value)
{
    if (d_func()->setMaximumHeight((value))) {
        emit maximumHeightChanged();
    }
}

QJSValue CxFlexible::minimumWidth() const
{
    return d_func()->minimumWidth();
}

QJSValue CxFlexible::minimumHeight() const
{
    return d_func()->minimumHeight();
}

QJSValue CxFlexible::maximumWidth() const
{
    return d_func()->maximumWidth();
}

QJSValue CxFlexible::maximumHeight() const
{
    return d_func()->maximumHeight();
}

void CxFlexible::setMarginLeft(const QJSValue &value)
{
    if (d_func()->setMargin(YGEdgeLeft, value)) {
        emit marginLeftChanged();
    }
}

void CxFlexible::setMarginTop(const QJSValue &value)
{
    if (d_func()->setMargin(YGEdgeTop, value)) {
        emit marginTopChanged();
    }
}

void CxFlexible::setMarginRight(const QJSValue &value)
{
    if (d_func()->setMargin(YGEdgeRight, value)) {
        emit marginRightChanged();
    }
}

void CxFlexible::setMarginBottom(const QJSValue &value)
{
    if (d_func()->setMargin(YGEdgeBottom, value)) {
        emit marginBottomChanged();
    }
}

void CxFlexible::setMarginStart(const QJSValue &value)
{
    if (d_func()->setMargin(YGEdgeStart, value)) {
        emit marginStartChanged();
    }
}

void CxFlexible::setMarginEnd(const QJSValue &value)
{
    if (d_func()->setMargin(YGEdgeEnd, value)) {
        emit marginEndChanged();
    }
}

void CxFlexible::setMarginHorizontal(const QJSValue &value)
{
    if (d_func()->setMargin(YGEdgeHorizontal, value)) {
        emit marginHorizontalChanged();
    }
}

void CxFlexible::setMarginVertical(const QJSValue &value)
{
    if (d_func()->setMargin(YGEdgeVertical, value)) {
        emit marginVerticalChanged();
    }
}

void CxFlexible::setMargins(const QJSValue &value)
{
    if (d_func()->setMargin(YGEdgeAll, value)) {
        emit marginsChanged();
    }
}

QJSValue CxFlexible::marginLeft() const
{
    return d_func()->margin(YGEdgeLeft);
}

QJSValue CxFlexible::marginTop() const
{
    return d_func()->margin(YGEdgeTop);
}

QJSValue CxFlexible::marginRight() const
{
    return d_func()->margin(YGEdgeRight);
}

QJSValue CxFlexible::marginBottom() const
{
    return d_func()->margin(YGEdgeBottom);
}

QJSValue CxFlexible::marginStart() const
{
    return d_func()->margin(YGEdgeStart);
}

QJSValue CxFlexible::marginEnd() const
{
    return d_func()->margin(YGEdgeEnd);
}

QJSValue CxFlexible::marginHorizontal() const
{
    return d_func()->margin(YGEdgeHorizontal);
}

QJSValue CxFlexible::marginVertical() const
{
    return d_func()->margin(YGEdgeVertical);
}

QJSValue CxFlexible::margins() const
{
    return d_func()->margin(YGEdgeAll);
}

void CxFlexible::setPaddingLeft(const QJSValue &value)
{
    if (d_func()->setPadding(YGEdgeLeft, value)) {
        emit paddingLeftChanged();
    }
}

void CxFlexible::setPaddingTop(const QJSValue &value)
{
    if (d_func()->setPadding(YGEdgeTop, value)) {
        emit paddingTopChanged();
    }
}

void CxFlexible::setPaddingRight(const QJSValue &value)
{
    if (d_func()->setPadding(YGEdgeRight, value)) {
        emit paddingRightChanged();
    }
}

void CxFlexible::setPaddingBottom(const QJSValue &value)
{
    if (d_func()->setPadding(YGEdgeBottom, value)) {
        emit paddingBottomChanged();
    }
}

void CxFlexible::setPaddingStart(const QJSValue &value)
{
    if (d_func()->setPadding(YGEdgeStart, value)) {
        emit paddingStartChanged();
    }
}

void CxFlexible::setPaddingEnd(const QJSValue &value)
{
    if (d_func()->setPadding(YGEdgeEnd, value)) {
        emit paddingEndChanged();
    }
}

void CxFlexible::setPaddingHorizontal(const QJSValue &value)
{
    if (d_func()->setPadding(YGEdgeHorizontal, value)) {
        emit paddingHorizontalChanged();
    }
}

void CxFlexible::setPaddingVertical(const QJSValue &value)
{
    if (d_func()->setPadding(YGEdgeVertical, value)) {
        emit paddingVerticalChanged();
    }
}

void CxFlexible::setPadding(const QJSValue &value)
{
    if (d_func()->setPadding(YGEdgeAll, value)) {
        emit paddingChanged();
    }
}

QJSValue CxFlexible::paddingLeft() const
{
    return d_func()->padding(YGEdgeLeft);
}

QJSValue CxFlexible::paddingTop() const
{
    return d_func()->padding(YGEdgeTop);
}

QJSValue CxFlexible::paddingRight() const
{
    return d_func()->padding(YGEdgeRight);
}

QJSValue CxFlexible::paddingBottom() const
{
    return d_func()->padding(YGEdgeBottom);
}

QJSValue CxFlexible::paddingStart() const
{
    return d_func()->padding(YGEdgeStart);
}

QJSValue CxFlexible::paddingEnd() const
{
    return d_func()->padding(YGEdgeEnd);
}

QJSValue CxFlexible::paddingHorizontal() const
{
    return d_func()->padding(YGEdgeHorizontal);
}

QJSValue CxFlexible::paddingVertical() const
{
    return d_func()->padding(YGEdgeVertical);
}

QJSValue CxFlexible::padding() const
{
    return d_func()->padding(YGEdgeAll);
}

void CxFlexible::setBorderLeft(const QJSValue &value)
{
    if (d_func()->setBorder(YGEdgeLeft, value)) {
        emit borderLeftChanged();
    }
}

void CxFlexible::setBorderTop(const QJSValue &value)
{
    if (d_func()->setBorder(YGEdgeTop, value)) {
        emit borderTopChanged();
    }
}

void CxFlexible::setBorderRight(const QJSValue &value)
{
    if (d_func()->setBorder(YGEdgeRight, value)) {
        emit borderRightChanged();
    }
}

void CxFlexible::setBorderBottom(const QJSValue &value)
{
    if (d_func()->setBorder(YGEdgeBottom, value)) {
        emit borderBottomChanged();
    }
}

void CxFlexible::setBorderStart(const QJSValue &value)
{
    if (d_func()->setBorder(YGEdgeStart, value)) {
        emit borderStartChanged();
    }
}

void CxFlexible::setBorderEnd(const QJSValue &value)
{
    if (d_func()->setBorder(YGEdgeEnd, value)) {
        emit borderEndChanged();
    }
}

void CxFlexible::setBorderHorizontal(const QJSValue &value)
{
    if (d_func()->setBorder(YGEdgeHorizontal, value)) {
        emit borderHorizontalChanged();
    }
}

void CxFlexible::setBorderVertical(const QJSValue &value)
{
    if (d_func()->setBorder(YGEdgeVertical, value)) {
        emit borderVerticalChanged();
    }
}

void CxFlexible::setBorders(const QJSValue &value)
{
    if (d_func()->setBorder(YGEdgeAll, value)) {
        emit bordersChanged();
    }
}

QJSValue CxFlexible::borderLeft() const
{
    return d_func()->border(YGEdgeLeft);
}

QJSValue CxFlexible::borderTop() const
{
    return d_func()->border(YGEdgeTop);
}

QJSValue CxFlexible::borderRight() const
{
    return d_func()->border(YGEdgeRight);
}

QJSValue CxFlexible::borderBottom() const
{
    return d_func()->border(YGEdgeBottom);
}

QJSValue CxFlexible::borderStart() const
{
    return d_func()->border(YGEdgeStart);
}

QJSValue CxFlexible::borderEnd() const
{
    return d_func()->border(YGEdgeEnd);
}

QJSValue CxFlexible::borderHorizontal() const
{
    return d_func()->border(YGEdgeHorizontal);
}

QJSValue CxFlexible::borderVertical() const
{
    return d_func()->border(YGEdgeVertical);
}

QJSValue CxFlexible::borders() const
{
    return d_func()->border(YGEdgeAll);
}

void CxFlexible::setDirection(CxFlex::Direction value)
{
    if (d_func()->setDirection(value)) {
        emit directionChanged();
    }
}

void CxFlexible::setPosition(CxFlex::Position value)
{
    if (d_func()->setPosition(value)) {
        emit positionChanged();
    }
}

void CxFlexible::setDisplay(CxFlex::Display value)
{
    if (d_func()->setDisplay(value)) {
        emit displayChanged();
    }
}

void CxFlexible::setOverflow(CxFlex::Overflow value)
{
    if (d_func()->setOverflow(value)) {
        emit overflowChanged();
    }
}

CxFlex::Direction CxFlexible::direction() const
{
    return d_func()->direction();
}

CxFlex::Position CxFlexible::position() const
{
    return d_func()->position();
}

CxFlex::Display CxFlexible::display() const
{
    return d_func()->display();
}

CxFlex::Overflow CxFlexible::overflow() const
{
    return d_func()->overflow();
}

void CxFlexible::setPositionLeft(const QJSValue &value)
{
    if (d_func()->setPosition(YGEdgeLeft, value)) {
        emit positionLeftChanged();
    }
}

void CxFlexible::setPositionTop(const QJSValue &value)
{
    if (d_func()->setPosition(YGEdgeTop, value)) {
        emit positionTopChanged();
    }
}

void CxFlexible::setPositionRight(const QJSValue &value)
{
    if (d_func()->setPosition(YGEdgeRight, value)) {
        emit positionRightChanged();
    }
}

void CxFlexible::setPositionBottom(const QJSValue &value)
{
    if (d_func()->setPosition(YGEdgeBottom, value)) {
        emit positionBottomChanged();
    }
}

void CxFlexible::setPositionStart(const QJSValue &value)
{
    if (d_func()->setPosition(YGEdgeStart, value)) {
        emit positionStartChanged();
    }
}

void CxFlexible::setPositionEnd(const QJSValue &value)
{
    if (d_func()->setPosition(YGEdgeEnd, value)) {
        emit positionEndChanged();
    }
}

QJSValue CxFlexible::positionLeft() const
{
    return d_func()->position(YGEdgeLeft);
}

QJSValue CxFlexible::positionTop() const
{
    return d_func()->position(YGEdgeTop);
}

QJSValue CxFlexible::positionRight() const
{
    return d_func()->position(YGEdgeRight);
}

QJSValue CxFlexible::positionBottom() const
{
    return d_func()->position(YGEdgeBottom);
}

QJSValue CxFlexible::positionStart() const
{
    return d_func()->position(YGEdgeStart);
}

QJSValue CxFlexible::positionEnd() const
{
    return d_func()->position(YGEdgeEnd);
}

void CxFlexible::setAlignSelf(CxFlex::Align value)
{
    if (d_func()->setAlignSelf(value)) {
        emit alignSelfChanged();
    }
}

CxFlex::Align CxFlexible::alignSelf() const
{
    return d_func()->alignSelf();
}

void CxFlexible::setFlex(const QJSValue &value)
{
    if (d_func()->setFlex(value)) {
        emit flexChanged();
    }
}

void CxFlexible::setFlexGrow(const QJSValue &value)
{
    if (d_func()->setFlexGrow(value)) {
        emit flexGrowChanged();
    }
}

void CxFlexible::setFlexBasis(const QJSValue &value)
{
    if (d_func()->setFlexBasis(value)) {
        emit flexBasisChanged();
    }
}

void CxFlexible::setFlexShrink(const QJSValue &value)
{
    if (d_func()->setFlexShrink(value)) {
        emit flexShrinkChanged();
    }
}

QJSValue CxFlexible::flex() const
{
    return d_func()->flex();
}

QJSValue CxFlexible::flexGrow() const
{
    return d_func()->flexGrow();
}

QJSValue CxFlexible::flexBasis() const
{
    return d_func()->flexBasis();
}

QJSValue CxFlexible::flexShrink() const
{
    return d_func()->flexShrink();
}

void CxFlexible::setAspectRatio(const QJSValue &value)
{
    if (d_func()->setAspectRatio(value)) {
        emit aspectRatioChanged();
    }
}

QJSValue CxFlexible::aspectRatio() const
{
    return d_func()->aspectRatio();
}

// class CxFlexibleRegister

CxFlexible *CxFlexibleRegister::qmlAttachedProperties(QObject *attachee)
{
    return new CxFlexible(attachee);
}

// class CxFlexiblePrivate

const QLoggingCategory &CxFlexiblePrivate::loggingCategory() const
{
    return lcFlexNode();
}

CxFlexiblePrivate::CxFlexiblePrivate()
    : q_ptr(nullptr)
{
}

CxFlexiblePrivate::~CxFlexiblePrivate()
{
}

void CxFlexiblePrivate::applyLayout()
{
    QQuickItem *q = qobject_cast<QQuickItem *>(q_func()->parent());
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

    const uint32_t count = YGNodeGetChildCount(node);
    for (uint32_t index = 0; index < count; ++index) {
        YGNodeRef childNode = YGNodeGetChild(node, index);

        context(childNode)->applyLayout();
    }
}
