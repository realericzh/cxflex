#include "CxFlexItem.h"
#include "CxFlexItem_p.h"

#include <QStack>
#include <QTimer>

#include "CxFlexible.h"
#include "CxFlexible_p.h"
#include "CxFlexSettings.h"
#include "CxFlexSettings_p.h"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(lcFlexItem, "CxFlexItem")

Q_LOGGING_CATEGORY(lcFlexColumn, "CxFlexColumn")
Q_LOGGING_CATEGORY(lcFlexColumnReverse, "CxFlexColumnReverse")
Q_LOGGING_CATEGORY(lcFlexRow, "CxFlexRow")
Q_LOGGING_CATEGORY(lcFlexRowReverse, "CxFlexRowReverse")

// class CxFlexItem

CxFlexItem::CxFlexItem(CxFlexItemPrivate &dd, QQuickItem *parent)
    : QQuickItem(parent)
    , d_ptr(&dd)
{
    d_ptr->q_ptr = this;
}

CxFlexItem::CxFlexItem(QQuickItem *parent)
    : QQuickItem(parent)
    , d_ptr(new CxFlexItemPrivate())
{
    d_ptr->q_ptr = this;
}

CxFlexItem::~CxFlexItem()
{
    d_func()->cleanupNode();
}

void CxFlexItem::componentComplete()
{
    QQuickItem::componentComplete();

    d_func()->buildLayout();
}

void CxFlexItem::geometryChange(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickItem::geometryChange(newGeometry, oldGeometry);

    d_func()->buildLayout();
}

void CxFlexItem::itemChange(ItemChange change, const ItemChangeData &value)
{
    Q_D(CxFlexItem);

    QQuickItem::itemChange(change, value);

    if (change == ItemChildAddedChange) {
        YGNodeRef childNode = nullptr;

        do {
            CxFlexItem *node = qobject_cast<CxFlexItem *>(value.item);
            if (node) {
                childNode = node->d_func()->makeNode();
                break;
            }

            CxFlexible *attached = qobject_cast<CxFlexible *>(qmlAttachedPropertiesObject<CxFlexibleRegister>(value.item, false));
            if (attached) {
                childNode = attached->d_func()->makeNode();
                break;
            }
        } while (false);

        if (childNode) {
            const uint32_t index = YGNodeGetChildCount(d->makeNode());
            YGNodeInsertChild(d->makeNode(), childNode, index);
        }
    } else if (change == ItemChildRemovedChange) {
        YGNodeRef childNode = nullptr;

        do {
            CxFlexItem *node = qobject_cast<CxFlexItem *>(value.item);
            if (node) {
                childNode = node->d_func()->node;
                break;
            }

            CxFlexible *attached = qobject_cast<CxFlexible *>(qmlAttachedPropertiesObject<CxFlexibleRegister>(value.item, false));
            if (attached) {
                childNode = attached->d_func()->node;
                break;
            }
        } while (false);

        if (childNode) {
            YGNodeRemoveChild(d->node, childNode);
        }
    } else if (change == ItemVisibleHasChanged) {
        if (value.boolValue) {
            setDisplay(CxFlex::DisplayFlex);
        } else {
            setDisplay(CxFlex::DisplayNone);
        }
    } else if (change == ItemParentHasChanged) {
        d->root = (qobject_cast<CxFlexItem *>(value.item) == nullptr);

        d->buildLayout();
    }
}

void CxFlexItem::setSettings(CxFlexSettings *settings)
{
    Q_D(CxFlexItem);

    d->makeNode();

    const YGConfigRef oldValue = YGNodeGetConfig(d->node);
    YGNodeSetConfig(d->node, CxFlexSettingsPrivate::get(settings)->makeConfig());
    const YGConfigRef newValue = YGNodeGetConfig(d->node);

    if (oldValue != newValue) {
        emit settingsChanged();
    }
}

CxFlexSettings *CxFlexItem::settings() const
{
    return static_cast<CxFlexSettings *>(YGConfigGetContext(YGNodeGetConfig(d_func()->node)));
}

void CxFlexItem::setPreferredWidth(const QJSValue &value)
{
    if (d_func()->setPreferredWidth(value)) {
        emit preferredWidthChanged();
    }
}

void CxFlexItem::setPreferredHeight(const QJSValue &value)
{
    if (d_func()->setPreferredHeight(value)) {
        emit preferredHeightChanged();
    }
}

QJSValue CxFlexItem::preferredWidth() const
{
    return d_func()->preferredWidth();
}

QJSValue CxFlexItem::preferredHeight() const
{
    return d_func()->preferredHeight();
}

void CxFlexItem::setMinimumWidth(const QJSValue &value)
{
    if (d_func()->setMinimumWidth((value))) {
        emit minimumWidthChanged();
    }
}

void CxFlexItem::setMinimumHeight(const QJSValue &value)
{
    if (d_func()->setMinimumHeight((value))) {
        emit minimumHeightChanged();
    }
}

void CxFlexItem::setMaximumWidth(const QJSValue &value)
{
    if (d_func()->setMaximumWidth((value))) {
        emit maximumWidthChanged();
    }
}

void CxFlexItem::setMaximumHeight(const QJSValue &value)
{
    if (d_func()->setMaximumHeight((value))) {
        emit maximumHeightChanged();
    }
}

QJSValue CxFlexItem::minimumWidth() const
{
    return d_func()->minimumWidth();
}

QJSValue CxFlexItem::minimumHeight() const
{
    return d_func()->minimumHeight();
}

QJSValue CxFlexItem::maximumWidth() const
{
    return d_func()->maximumWidth();
}

QJSValue CxFlexItem::maximumHeight() const
{
    return d_func()->maximumHeight();
}

void CxFlexItem::setMarginLeft(const QJSValue &value)
{
    if (d_func()->setMargin(YGEdgeLeft, value)) {
        emit marginLeftChanged();
    }
}

void CxFlexItem::setMarginTop(const QJSValue &value)
{
    if (d_func()->setMargin(YGEdgeTop, value)) {
        emit marginTopChanged();
    }
}

void CxFlexItem::setMarginRight(const QJSValue &value)
{
    if (d_func()->setMargin(YGEdgeRight, value)) {
        emit marginRightChanged();
    }
}

void CxFlexItem::setMarginBottom(const QJSValue &value)
{
    if (d_func()->setMargin(YGEdgeBottom, value)) {
        emit marginBottomChanged();
    }
}

void CxFlexItem::setMarginStart(const QJSValue &value)
{
    if (d_func()->setMargin(YGEdgeStart, value)) {
        emit marginStartChanged();
    }
}

void CxFlexItem::setMarginEnd(const QJSValue &value)
{
    if (d_func()->setMargin(YGEdgeEnd, value)) {
        emit marginEndChanged();
    }
}

void CxFlexItem::setMarginHorizontal(const QJSValue &value)
{
    if (d_func()->setMargin(YGEdgeHorizontal, value)) {
        emit marginHorizontalChanged();
    }
}

void CxFlexItem::setMarginVertical(const QJSValue &value)
{
    if (d_func()->setMargin(YGEdgeVertical, value)) {
        emit marginVerticalChanged();
    }
}

void CxFlexItem::setMargins(const QJSValue &value)
{
    if (d_func()->setMargin(YGEdgeAll, value)) {
        emit marginsChanged();
    }
}

QJSValue CxFlexItem::marginLeft() const
{
    return d_func()->margin(YGEdgeLeft);
}

QJSValue CxFlexItem::marginTop() const
{
    return d_func()->margin(YGEdgeTop);
}

QJSValue CxFlexItem::marginRight() const
{
    return d_func()->margin(YGEdgeRight);
}

QJSValue CxFlexItem::marginBottom() const
{
    return d_func()->margin(YGEdgeBottom);
}

QJSValue CxFlexItem::marginStart() const
{
    return d_func()->margin(YGEdgeStart);
}

QJSValue CxFlexItem::marginEnd() const
{
    return d_func()->margin(YGEdgeEnd);
}

QJSValue CxFlexItem::marginHorizontal() const
{
    return d_func()->margin(YGEdgeHorizontal);
}

QJSValue CxFlexItem::marginVertical() const
{
    return d_func()->margin(YGEdgeVertical);
}

QJSValue CxFlexItem::margins() const
{
    return d_func()->margin(YGEdgeAll);
}

void CxFlexItem::setPaddingLeft(const QJSValue &value)
{
    if (d_func()->setPadding(YGEdgeLeft, value)) {
        emit paddingLeftChanged();
    }
}

void CxFlexItem::setPaddingTop(const QJSValue &value)
{
    if (d_func()->setPadding(YGEdgeTop, value)) {
        emit paddingTopChanged();
    }
}

void CxFlexItem::setPaddingRight(const QJSValue &value)
{
    if (d_func()->setPadding(YGEdgeRight, value)) {
        emit paddingRightChanged();
    }
}

void CxFlexItem::setPaddingBottom(const QJSValue &value)
{
    if (d_func()->setPadding(YGEdgeBottom, value)) {
        emit paddingBottomChanged();
    }
}

void CxFlexItem::setPaddingStart(const QJSValue &value)
{
    if (d_func()->setPadding(YGEdgeStart, value)) {
        emit paddingStartChanged();
    }
}

void CxFlexItem::setPaddingEnd(const QJSValue &value)
{
    if (d_func()->setPadding(YGEdgeEnd, value)) {
        emit paddingEndChanged();
    }
}

void CxFlexItem::setPaddingHorizontal(const QJSValue &value)
{
    if (d_func()->setPadding(YGEdgeHorizontal, value)) {
        emit paddingHorizontalChanged();
    }
}

void CxFlexItem::setPaddingVertical(const QJSValue &value)
{
    if (d_func()->setPadding(YGEdgeVertical, value)) {
        emit paddingVerticalChanged();
    }
}

void CxFlexItem::setPadding(const QJSValue &value)
{
    if (d_func()->setPadding(YGEdgeAll, value)) {
        emit paddingChanged();
    }
}

QJSValue CxFlexItem::paddingLeft() const
{
    return d_func()->padding(YGEdgeLeft);
}

QJSValue CxFlexItem::paddingTop() const
{
    return d_func()->padding(YGEdgeTop);
}

QJSValue CxFlexItem::paddingRight() const
{
    return d_func()->padding(YGEdgeRight);
}

QJSValue CxFlexItem::paddingBottom() const
{
    return d_func()->padding(YGEdgeBottom);
}

QJSValue CxFlexItem::paddingStart() const
{
    return d_func()->padding(YGEdgeStart);
}

QJSValue CxFlexItem::paddingEnd() const
{
    return d_func()->padding(YGEdgeEnd);
}

QJSValue CxFlexItem::paddingHorizontal() const
{
    return d_func()->padding(YGEdgeHorizontal);
}

QJSValue CxFlexItem::paddingVertical() const
{
    return d_func()->padding(YGEdgeVertical);
}

QJSValue CxFlexItem::padding() const
{
    return d_func()->padding(YGEdgeAll);
}

void CxFlexItem::setBorderLeft(const QJSValue &value)
{
    if (d_func()->setBorder(YGEdgeLeft, value)) {
        emit borderLeftChanged();
    }
}

void CxFlexItem::setBorderTop(const QJSValue &value)
{
    if (d_func()->setBorder(YGEdgeTop, value)) {
        emit borderTopChanged();
    }
}

void CxFlexItem::setBorderRight(const QJSValue &value)
{
    if (d_func()->setBorder(YGEdgeRight, value)) {
        emit borderRightChanged();
    }
}

void CxFlexItem::setBorderBottom(const QJSValue &value)
{
    if (d_func()->setBorder(YGEdgeBottom, value)) {
        emit borderBottomChanged();
    }
}

void CxFlexItem::setBorderStart(const QJSValue &value)
{
    if (d_func()->setBorder(YGEdgeStart, value)) {
        emit borderStartChanged();
    }
}

void CxFlexItem::setBorderEnd(const QJSValue &value)
{
    if (d_func()->setBorder(YGEdgeEnd, value)) {
        emit borderEndChanged();
    }
}

void CxFlexItem::setBorderHorizontal(const QJSValue &value)
{
    if (d_func()->setBorder(YGEdgeHorizontal, value)) {
        emit borderHorizontalChanged();
    }
}

void CxFlexItem::setBorderVertical(const QJSValue &value)
{
    if (d_func()->setBorder(YGEdgeVertical, value)) {
        emit borderVerticalChanged();
    }
}

void CxFlexItem::setBorders(const QJSValue &value)
{
    if (d_func()->setBorder(YGEdgeAll, value)) {
        emit bordersChanged();
    }
}

QJSValue CxFlexItem::borderLeft() const
{
    return d_func()->border(YGEdgeLeft);
}

QJSValue CxFlexItem::borderTop() const
{
    return d_func()->border(YGEdgeTop);
}

QJSValue CxFlexItem::borderRight() const
{
    return d_func()->border(YGEdgeRight);
}

QJSValue CxFlexItem::borderBottom() const
{
    return d_func()->border(YGEdgeBottom);
}

QJSValue CxFlexItem::borderStart() const
{
    return d_func()->border(YGEdgeStart);
}

QJSValue CxFlexItem::borderEnd() const
{
    return d_func()->border(YGEdgeEnd);
}

QJSValue CxFlexItem::borderHorizontal() const
{
    return d_func()->border(YGEdgeHorizontal);
}

QJSValue CxFlexItem::borderVertical() const
{
    return d_func()->border(YGEdgeVertical);
}

QJSValue CxFlexItem::borders() const
{
    return d_func()->border(YGEdgeAll);
}

void CxFlexItem::setDirection(CxFlex::Direction value)
{
    if (d_func()->setDirection(value)) {
        emit directionChanged();
    }
}

void CxFlexItem::setPosition(CxFlex::Position value)
{
    if (d_func()->setPosition(value)) {
        emit positionChanged();
    }
}

void CxFlexItem::setDisplay(CxFlex::Display value)
{
    if (d_func()->setDisplay(value)) {
        emit displayChanged();
    }
}

void CxFlexItem::setOverflow(CxFlex::Overflow value)
{
    if (d_func()->setOverflow(value)) {
        emit overflowChanged();
    }
}

CxFlex::Direction CxFlexItem::direction() const
{
    return d_func()->direction();
}

CxFlex::Position CxFlexItem::position() const
{
    return d_func()->position();
}

CxFlex::Display CxFlexItem::display() const
{
    return d_func()->display();
}

CxFlex::Overflow CxFlexItem::overflow() const
{
    return d_func()->overflow();
}

void CxFlexItem::setPositionLeft(const QJSValue &value)
{
    if (d_func()->setPosition(YGEdgeLeft, value)) {
        emit positionLeftChanged();
    }
}

void CxFlexItem::setPositionTop(const QJSValue &value)
{
    if (d_func()->setPosition(YGEdgeTop, value)) {
        emit positionTopChanged();
    }
}

void CxFlexItem::setPositionRight(const QJSValue &value)
{
    if (d_func()->setPosition(YGEdgeRight, value)) {
        emit positionRightChanged();
    }
}

void CxFlexItem::setPositionBottom(const QJSValue &value)
{
    if (d_func()->setPosition(YGEdgeBottom, value)) {
        emit positionBottomChanged();
    }
}

void CxFlexItem::setPositionStart(const QJSValue &value)
{
    if (d_func()->setPosition(YGEdgeStart, value)) {
        emit positionStartChanged();
    }
}

void CxFlexItem::setPositionEnd(const QJSValue &value)
{
    if (d_func()->setPosition(YGEdgeEnd, value)) {
        emit positionEndChanged();
    }
}

QJSValue CxFlexItem::positionLeft() const
{
    return d_func()->position(YGEdgeLeft);
}

QJSValue CxFlexItem::positionTop() const
{
    return d_func()->position(YGEdgeTop);
}

QJSValue CxFlexItem::positionRight() const
{
    return d_func()->position(YGEdgeRight);
}

QJSValue CxFlexItem::positionBottom() const
{
    return d_func()->position(YGEdgeBottom);
}

QJSValue CxFlexItem::positionStart() const
{
    return d_func()->position(YGEdgeStart);
}

QJSValue CxFlexItem::positionEnd() const
{
    return d_func()->position(YGEdgeEnd);
}

void CxFlexItem::setFlexDirection(CxFlex::FlexDirection value)
{
    if (d_func()->setFlexDirection(value)) {
        emit flexDirectionChanged();
    }
}

void CxFlexItem::setJustifyContent(CxFlex::Justify value)
{
    if (d_func()->setJustifyContent(value)) {
        emit justifyContentChanged();
    }
}

void CxFlexItem::setAlignContent(CxFlex::Align value)
{
    if (d_func()->setAlignContent(value)) {
        emit alignContentChanged();
    }
}

void CxFlexItem::setAlignItems(CxFlex::Align value)
{
    if (d_func()->setAlignItems(value)) {
        emit alignItemsChanged();
    }
}

void CxFlexItem::setAlignSelf(CxFlex::Align value)
{
    if (d_func()->setAlignSelf(value)) {
        emit alignSelfChanged();
    }
}

void CxFlexItem::setFlexWrap(CxFlex::Wrap value)
{
    if (d_func()->setFlexWrap(value)) {
        emit flexWrapChanged();
    }
}

CxFlex::FlexDirection CxFlexItem::flexDirection() const
{
    return d_func()->flexDirection();
}

CxFlex::Justify CxFlexItem::justifyContent() const
{
    return d_func()->justifyContent();
}

CxFlex::Align CxFlexItem::alignContent() const
{
    return d_func()->alignContent();
}

CxFlex::Align CxFlexItem::alignItems() const
{
    return d_func()->alignItems();
}

CxFlex::Align CxFlexItem::alignSelf() const
{
    return d_func()->alignSelf();
}

CxFlex::Wrap CxFlexItem::flexWrap() const
{
    return d_func()->flexWrap();
}

void CxFlexItem::setColumnGap(const QJSValue &value)
{
    if (d_func()->setGap(YGGutterColumn, value)) {
        emit columnGapChanged();
    }
}

void CxFlexItem::setRowGap(const QJSValue &value)
{
    if (d_func()->setGap(YGGutterRow, value)) {
        emit rowGapChanged();
    }
}

void CxFlexItem::setGap(const QJSValue &value)
{
    if (d_func()->setGap(YGGutterAll, value)) {
        emit gapChanged();
    }
}

QJSValue CxFlexItem::columnGap() const
{
    return d_func()->gap(YGGutterColumn);
}

QJSValue CxFlexItem::rowGap() const
{
    return d_func()->gap(YGGutterRow);
}

QJSValue CxFlexItem::gap() const
{
    return d_func()->gap(YGGutterAll);
}

void CxFlexItem::setFlex(const QJSValue &value)
{
    if (d_func()->setFlex(value)) {
        emit flexChanged();
    }
}

void CxFlexItem::setFlexGrow(const QJSValue &value)
{
    if (d_func()->setFlexGrow(value)) {
        emit flexGrowChanged();
    }
}

void CxFlexItem::setFlexBasis(const QJSValue &value)
{
    if (d_func()->setFlexBasis(value)) {
        emit flexBasisChanged();
    }
}

void CxFlexItem::setFlexShrink(const QJSValue &value)
{
    if (d_func()->setFlexShrink(value)) {
        emit flexShrinkChanged();
    }
}

QJSValue CxFlexItem::flex() const
{
    return d_func()->flex();
}

QJSValue CxFlexItem::flexGrow() const
{
    return d_func()->flexGrow();
}

QJSValue CxFlexItem::flexBasis() const
{
    return d_func()->flexBasis();
}

QJSValue CxFlexItem::flexShrink() const
{
    return d_func()->flexShrink();
}

void CxFlexItem::setAspectRatio(const QJSValue &value)
{
    if (d_func()->setAspectRatio(value)) {
        emit aspectRatioChanged();
    }
}

QJSValue CxFlexItem::aspectRatio() const
{
    return d_func()->aspectRatio();
}

// class CxFlexItemPrivate

const QLoggingCategory &CxFlexItemPrivate::loggingCategory() const
{
    return lcFlexItem();
}

CxFlexItemPrivate::CxFlexItemPrivate()
    : q_ptr(nullptr)
{
}

CxFlexItemPrivate::~CxFlexItemPrivate()
{
}

void CxFlexItemPrivate::buildLayout()
{
    Q_Q(CxFlexItem);

    if (root && q->isComponentComplete() && pending.testAndSetOrdered(0, 1)) {
        QTimer::singleShot(0, q, [=] {
            calculateLayout();
            pending = 0;
        });
    }
}

void CxFlexItemPrivate::calculateLayout()
{
    Q_Q(CxFlexItem);

    YGNodeCalculateLayout(node,
                          q->widthValid() ? q->width() : YGUndefined,
                          q->heightValid()  ? q->height() : YGUndefined,
                          YGDirectionInherit);

    applyLayout();
}

void CxFlexItemPrivate::applyLayout()
{
    Q_Q(CxFlexItem);

    if (!YGNodeGetHasNewLayout(node)) {
        return;
    }
    YGNodeSetHasNewLayout(node, false);

    if (!root) {
        qreal left = YGNodeLayoutGetLeft(node);
        if (q->x() != left) {
            q->setProperty("x", left);
        }
        qreal top = YGNodeLayoutGetTop(node);
        if (q->y() != top) {
            q->setProperty("y", top);
        }
    }

    qreal width = YGNodeLayoutGetWidth(node);
    if (q->implicitWidth() != width) {
        q->setProperty("implicitWidth", width);
    }
    qreal height = YGNodeLayoutGetHeight(node);
    if (q->implicitHeight() != height) {
        q->setProperty("implicitHeight", height);
    }

    const uint32_t count = YGNodeGetChildCount(node);
    for (uint32_t index = 0; index < count; ++index) {
        YGNodeRef childNode = YGNodeGetChild(node, index);

        context(childNode)->applyLayout();
    }
}

// class CxFlexColumn

CxFlexColumn::CxFlexColumn(QQuickItem *parent)
    : CxFlexItem(*new CxFlexColumnPrivate(), parent)
{
}

CxFlexColumn::~CxFlexColumn()
{
}

// class CxFlexColumnPrivate

const QLoggingCategory &CxFlexColumnPrivate::loggingCategory() const
{
    return lcFlexColumn();
}

void CxFlexColumnPrivate::initNode(YGNodeRef node)
{
    CxFlexItemPrivate::initNode(node);

    YGNodeStyleSetFlexDirection(node, YGFlexDirectionColumn);
}

// class CxFlexColumnReverse

CxFlexColumnReverse::CxFlexColumnReverse(QQuickItem *parent)
    : CxFlexItem(*new CxFlexColumnReversePrivate(), parent)
{
}

CxFlexColumnReverse::~CxFlexColumnReverse()
{
}

// class CxFlexColumnReversePrivate

const QLoggingCategory &CxFlexColumnReversePrivate::loggingCategory() const
{
    return lcFlexColumnReverse();
}

void CxFlexColumnReversePrivate::initNode(YGNodeRef node)
{
    CxFlexItemPrivate::initNode(node);

    YGNodeStyleSetFlexDirection(node, YGFlexDirectionColumnReverse);
}

// class CxFlexRow

CxFlexRow::CxFlexRow(QQuickItem *parent)
    : CxFlexItem(*new CxFlexRowPrivate(), parent)
{
}

CxFlexRow::~CxFlexRow()
{
}

// class CxFlexRowPrivate

const QLoggingCategory &CxFlexRowPrivate::loggingCategory() const
{
    return lcFlexRow();
}

void CxFlexRowPrivate::initNode(YGNodeRef node)
{
    CxFlexItemPrivate::initNode(node);

    YGNodeStyleSetFlexDirection(node, YGFlexDirectionRow);
}

// class CxFlexRowReverse

CxFlexRowReverse::CxFlexRowReverse(QQuickItem *parent)
    : CxFlexItem(*new CxFlexRowReversePrivate(), parent)
{
}

CxFlexRowReverse::~CxFlexRowReverse()
{
}

// class CxFlexRowReversePrivate

const QLoggingCategory &CxFlexRowReversePrivate::loggingCategory() const
{
    return lcFlexRowReverse();
}

void CxFlexRowReversePrivate::initNode(YGNodeRef node)
{
    CxFlexItemPrivate::initNode(node);

    YGNodeStyleSetFlexDirection(node, YGFlexDirectionRowReverse);
}
