#ifndef CXFLEXITEM_H
#define CXFLEXITEM_H

#include "CxFlex.h"
#include "CxFlexSettings.h"

// class CxFlexItem

class CxFlexItemPrivate;
class CxFlexItem : public QQuickItem
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(CxFlexItem)

    Q_PROPERTY(CxFlexSettings *settings READ settings WRITE setSettings NOTIFY settingsChanged)

    Q_PROPERTY(QJSValue preferredWidth READ preferredWidth WRITE setPreferredWidth NOTIFY preferredWidthChanged)
    Q_PROPERTY(QJSValue preferredHeight READ preferredHeight WRITE setPreferredHeight NOTIFY preferredHeightChanged)

    Q_PROPERTY(QJSValue minimumWidth READ minimumWidth WRITE setMinimumWidth NOTIFY minimumWidthChanged)
    Q_PROPERTY(QJSValue minimumHeight READ minimumHeight WRITE setMinimumHeight NOTIFY minimumHeightChanged)
    Q_PROPERTY(QJSValue maximumWidth READ maximumWidth WRITE setMaximumWidth NOTIFY maximumWidthChanged)
    Q_PROPERTY(QJSValue maximumHeight READ maximumHeight WRITE setMaximumHeight NOTIFY maximumHeightChanged)

    Q_PROPERTY(QJSValue marginLeft READ marginLeft WRITE setMarginLeft NOTIFY marginLeftChanged)
    Q_PROPERTY(QJSValue marginTop READ marginTop WRITE setMarginTop NOTIFY marginTopChanged)
    Q_PROPERTY(QJSValue marginRight READ marginRight WRITE setMarginRight NOTIFY marginRightChanged)
    Q_PROPERTY(QJSValue marginBottom READ marginBottom WRITE setMarginBottom NOTIFY marginBottomChanged)
    Q_PROPERTY(QJSValue marginStart READ marginStart WRITE setMarginStart NOTIFY marginStartChanged)
    Q_PROPERTY(QJSValue marginEnd READ marginEnd WRITE setMarginEnd NOTIFY marginEndChanged)
    Q_PROPERTY(QJSValue marginHorizontal READ marginHorizontal WRITE setMarginHorizontal NOTIFY marginHorizontalChanged)
    Q_PROPERTY(QJSValue marginVertical READ marginVertical WRITE setMarginVertical NOTIFY marginVerticalChanged)
    Q_PROPERTY(QJSValue margins READ margins WRITE setMargins NOTIFY marginsChanged)

    Q_PROPERTY(QJSValue paddingLeft READ paddingLeft WRITE setPaddingLeft NOTIFY paddingLeftChanged)
    Q_PROPERTY(QJSValue paddingTop READ paddingTop WRITE setPaddingTop NOTIFY paddingTopChanged)
    Q_PROPERTY(QJSValue paddingRight READ paddingRight WRITE setPaddingRight NOTIFY paddingRightChanged)
    Q_PROPERTY(QJSValue paddingBottom READ paddingBottom WRITE setPaddingBottom NOTIFY paddingBottomChanged)
    Q_PROPERTY(QJSValue paddingStart READ paddingStart WRITE setPaddingStart NOTIFY paddingStartChanged)
    Q_PROPERTY(QJSValue paddingEnd READ paddingEnd WRITE setPaddingEnd NOTIFY paddingEndChanged)
    Q_PROPERTY(QJSValue paddingHorizontal READ paddingHorizontal WRITE setPaddingHorizontal NOTIFY paddingHorizontalChanged)
    Q_PROPERTY(QJSValue paddingVertical READ paddingVertical WRITE setPaddingVertical NOTIFY paddingVerticalChanged)
    Q_PROPERTY(QJSValue padding READ padding WRITE setPadding NOTIFY paddingChanged)

    Q_PROPERTY(QJSValue borderLeft READ borderLeft WRITE setBorderLeft NOTIFY borderLeftChanged)
    Q_PROPERTY(QJSValue borderTop READ borderTop WRITE setBorderTop NOTIFY borderTopChanged)
    Q_PROPERTY(QJSValue borderRight READ borderRight WRITE setBorderRight NOTIFY borderRightChanged)
    Q_PROPERTY(QJSValue borderBottom READ borderBottom WRITE setBorderBottom NOTIFY borderBottomChanged)
    Q_PROPERTY(QJSValue borderStart READ borderStart WRITE setBorderStart NOTIFY borderStartChanged)
    Q_PROPERTY(QJSValue borderEnd READ borderEnd WRITE setBorderEnd NOTIFY borderEndChanged)
    Q_PROPERTY(QJSValue borderHorizontal READ borderHorizontal WRITE setBorderHorizontal NOTIFY borderHorizontalChanged)
    Q_PROPERTY(QJSValue borderVertical READ borderVertical WRITE setBorderVertical NOTIFY borderVerticalChanged)
    Q_PROPERTY(QJSValue borders READ borders WRITE setBorders NOTIFY bordersChanged)

    Q_PROPERTY(CxFlex::Direction direction READ direction WRITE setDirection NOTIFY directionChanged)
    Q_PROPERTY(CxFlex::Position position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(CxFlex::Display display READ display WRITE setDisplay NOTIFY displayChanged)
    Q_PROPERTY(CxFlex::Overflow overflow READ overflow WRITE setOverflow NOTIFY overflowChanged)

    Q_PROPERTY(QJSValue positionLeft READ positionLeft WRITE setPositionLeft NOTIFY positionLeftChanged)
    Q_PROPERTY(QJSValue positionTop READ positionTop WRITE setPositionTop NOTIFY positionTopChanged)
    Q_PROPERTY(QJSValue positionRight READ positionRight WRITE setPositionRight NOTIFY positionRightChanged)
    Q_PROPERTY(QJSValue positionBottom READ positionBottom WRITE setPositionBottom NOTIFY positionBottomChanged)
    Q_PROPERTY(QJSValue positionStart READ positionStart WRITE setPositionStart NOTIFY positionStartChanged)
    Q_PROPERTY(QJSValue positionEnd READ positionEnd WRITE setPositionEnd NOTIFY positionEndChanged)

    Q_PROPERTY(CxFlex::FlexDirection flexDirection READ flexDirection WRITE setFlexDirection NOTIFY flexDirectionChanged)
    Q_PROPERTY(CxFlex::Justify justifyContent READ justifyContent WRITE setJustifyContent NOTIFY justifyContentChanged)
    Q_PROPERTY(CxFlex::Align alignContent READ alignContent WRITE setAlignContent NOTIFY alignContentChanged)
    Q_PROPERTY(CxFlex::Align alignItems READ alignItems WRITE setAlignItems NOTIFY alignItemsChanged)
    Q_PROPERTY(CxFlex::Align alignSelf READ alignSelf WRITE setAlignSelf NOTIFY alignSelfChanged)
    Q_PROPERTY(CxFlex::Wrap flexWrap READ flexWrap WRITE setFlexWrap NOTIFY flexWrapChanged)

    Q_PROPERTY(QJSValue columnGap READ columnGap WRITE setColumnGap NOTIFY columnGapChanged)
    Q_PROPERTY(QJSValue rowGap READ rowGap WRITE setRowGap NOTIFY rowGapChanged)
    Q_PROPERTY(QJSValue gap READ gap WRITE setGap NOTIFY gapChanged)

    Q_PROPERTY(QJSValue flex READ flex WRITE setFlex NOTIFY flexChanged)
    Q_PROPERTY(QJSValue flexGrow READ flexGrow WRITE setFlexGrow NOTIFY flexGrowChanged)
    Q_PROPERTY(QJSValue flexBasis READ flexBasis WRITE setFlexBasis NOTIFY flexBasisChanged)
    Q_PROPERTY(QJSValue flexShrink READ flexShrink WRITE setFlexShrink NOTIFY flexShrinkChanged)

    Q_PROPERTY(QJSValue aspectRatio READ aspectRatio WRITE setAspectRatio NOTIFY aspectRatioChanged)

protected:
    CxFlexItem(CxFlexItemPrivate &dd, QQuickItem *parent);
public:
    explicit CxFlexItem(QQuickItem *parent = nullptr);
    virtual ~CxFlexItem();
protected:
    QScopedPointer<CxFlexItemPrivate> d_ptr;

protected:
    void componentComplete() override;

protected:
    void geometryChange(const QRectF &newGeometry, const QRectF &oldGeometry) override;
    void itemChange(QQuickItem::ItemChange change, const QQuickItem::ItemChangeData &value) override;

signals:
    void settingsChanged();
public:
    void setSettings(CxFlexSettings *settings);
public:
    CxFlexSettings *settings() const;

signals:
    void preferredWidthChanged();
    void preferredHeightChanged();
public:
    void setPreferredWidth(const QJSValue &value);
    void setPreferredHeight(const QJSValue &value);
public:
    QJSValue preferredWidth() const;
    QJSValue preferredHeight() const;

signals:
    void minimumWidthChanged();
    void minimumHeightChanged();
    void maximumWidthChanged();
    void maximumHeightChanged();
public:
    void setMinimumWidth(const QJSValue &value);
    void setMinimumHeight(const QJSValue &value);
    void setMaximumWidth(const QJSValue &value);
    void setMaximumHeight(const QJSValue &value);
public:
    QJSValue minimumWidth() const;
    QJSValue minimumHeight() const;
    QJSValue maximumWidth() const;
    QJSValue maximumHeight() const;

signals:
    void marginLeftChanged();
    void marginTopChanged();
    void marginRightChanged();
    void marginBottomChanged();
    void marginStartChanged();
    void marginEndChanged();
    void marginHorizontalChanged();
    void marginVerticalChanged();
    void marginsChanged();
public:
    void setMarginLeft(const QJSValue &value);
    void setMarginTop(const QJSValue &value);
    void setMarginRight(const QJSValue &value);
    void setMarginBottom(const QJSValue &value);
    void setMarginStart(const QJSValue &value);
    void setMarginEnd(const QJSValue &value);
    void setMarginHorizontal(const QJSValue &value);
    void setMarginVertical(const QJSValue &value);
    void setMargins(const QJSValue &value);
public:
    QJSValue marginLeft() const;
    QJSValue marginTop() const;
    QJSValue marginRight() const;
    QJSValue marginBottom() const;
    QJSValue marginStart() const;
    QJSValue marginEnd() const;
    QJSValue marginHorizontal() const;
    QJSValue marginVertical() const;
    QJSValue margins() const;

signals:
    void paddingLeftChanged();
    void paddingTopChanged();
    void paddingRightChanged();
    void paddingBottomChanged();
    void paddingStartChanged();
    void paddingEndChanged();
    void paddingHorizontalChanged();
    void paddingVerticalChanged();
    void paddingChanged();
public:
    void setPaddingLeft(const QJSValue &value);
    void setPaddingTop(const QJSValue &value);
    void setPaddingRight(const QJSValue &value);
    void setPaddingBottom(const QJSValue &value);
    void setPaddingStart(const QJSValue &value);
    void setPaddingEnd(const QJSValue &value);
    void setPaddingHorizontal(const QJSValue &value);
    void setPaddingVertical(const QJSValue &value);
    void setPadding(const QJSValue &value);
public:
    QJSValue paddingLeft() const;
    QJSValue paddingTop() const;
    QJSValue paddingRight() const;
    QJSValue paddingBottom() const;
    QJSValue paddingStart() const;
    QJSValue paddingEnd() const;
    QJSValue paddingHorizontal() const;
    QJSValue paddingVertical() const;
    QJSValue padding() const;

signals:
    void borderLeftChanged();
    void borderTopChanged();
    void borderRightChanged();
    void borderBottomChanged();
    void borderStartChanged();
    void borderEndChanged();
    void borderHorizontalChanged();
    void borderVerticalChanged();
    void bordersChanged();
public:
    void setBorderLeft(const QJSValue &value);
    void setBorderTop(const QJSValue &value);
    void setBorderRight(const QJSValue &value);
    void setBorderBottom(const QJSValue &value);
    void setBorderStart(const QJSValue &value);
    void setBorderEnd(const QJSValue &value);
    void setBorderHorizontal(const QJSValue &value);
    void setBorderVertical(const QJSValue &value);
    void setBorders(const QJSValue &value);
public:
    QJSValue borderLeft() const;
    QJSValue borderTop() const;
    QJSValue borderRight() const;
    QJSValue borderBottom() const;
    QJSValue borderStart() const;
    QJSValue borderEnd() const;
    QJSValue borderHorizontal() const;
    QJSValue borderVertical() const;
    QJSValue borders() const;

signals:
    void directionChanged();
    void positionChanged();
    void displayChanged();
    void overflowChanged();
public:
    void setDirection(CxFlex::Direction value);
    void setPosition(CxFlex::Position value);
    void setDisplay(CxFlex::Display value);
    void setOverflow(CxFlex::Overflow value);
public:
    CxFlex::Direction direction() const;
    CxFlex::Position position() const;
    CxFlex::Display display() const;
    CxFlex::Overflow overflow() const;

signals:
    void positionLeftChanged();
    void positionTopChanged();
    void positionRightChanged();
    void positionBottomChanged();
    void positionStartChanged();
    void positionEndChanged();
public:
    void setPositionLeft(const QJSValue &value);
    void setPositionTop(const QJSValue &value);
    void setPositionRight(const QJSValue &value);
    void setPositionBottom(const QJSValue &value);
    void setPositionStart(const QJSValue &value);
    void setPositionEnd(const QJSValue &value);
public:
    QJSValue positionLeft() const;
    QJSValue positionTop() const;
    QJSValue positionRight() const;
    QJSValue positionBottom() const;
    QJSValue positionStart() const;
    QJSValue positionEnd() const;

signals:
    void flexDirectionChanged();
    void justifyContentChanged();
    void alignContentChanged();
    void alignItemsChanged();
    void alignSelfChanged();
    void flexWrapChanged();
public:
    void setFlexDirection(CxFlex::FlexDirection value);
    void setJustifyContent(CxFlex::Justify value);
    void setAlignContent(CxFlex::Align value);
    void setAlignItems(CxFlex::Align value);
    void setAlignSelf(CxFlex::Align value);
    void setFlexWrap(CxFlex::Wrap value);
public:
    CxFlex::FlexDirection flexDirection() const;
    CxFlex::Justify justifyContent() const;
    CxFlex::Align alignContent() const;
    CxFlex::Align alignItems() const;
    CxFlex::Align alignSelf() const;
    CxFlex::Wrap flexWrap() const;

signals:
    void columnGapChanged();
    void rowGapChanged();
    void gapChanged();
public:
    void setColumnGap(const QJSValue &value);
    void setRowGap(const QJSValue &value);
    void setGap(const QJSValue &value);
public:
    QJSValue columnGap() const;
    QJSValue rowGap() const;
    QJSValue gap() const;

signals:
    void flexChanged();
    void flexGrowChanged();
    void flexBasisChanged();
    void flexShrinkChanged();
public:
    void setFlex(const QJSValue &value);
    void setFlexGrow(const QJSValue &value);
    void setFlexBasis(const QJSValue &value);
    void setFlexShrink(const QJSValue &value);
public:
    QJSValue flex() const;
    QJSValue flexGrow() const;
    QJSValue flexBasis() const;
    QJSValue flexShrink() const;

signals:
    void aspectRatioChanged();
public:
    void setAspectRatio(const QJSValue &value);
public:
    QJSValue aspectRatio() const;
};

// class CxFlexColumn

class CxFlexColumnPrivate;
class CxFlexColumn : public CxFlexItem
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(CxFlexColumn)

public:
    explicit CxFlexColumn(QQuickItem *parent = nullptr);
    virtual ~CxFlexColumn();
};

// class CxFlexColumnReverse

class CxFlexColumnReversePrivate;
class CxFlexColumnReverse : public CxFlexItem
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(CxFlexColumnReverse)

public:
    explicit CxFlexColumnReverse(QQuickItem *parent = nullptr);
    virtual ~CxFlexColumnReverse();
};

// class CxFlexRow

class CxFlexRowPrivate;
class CxFlexRow : public CxFlexItem
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(CxFlexRow)

public:
    explicit CxFlexRow(QQuickItem *parent = nullptr);
    virtual ~CxFlexRow();
};

// class CxFlexRowReverse

class CxFlexRowReversePrivate;
class CxFlexRowReverse : public CxFlexItem
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(CxFlexRowReverse)

public:
    explicit CxFlexRowReverse(QQuickItem *parent = nullptr);
    virtual ~CxFlexRowReverse();
};

#endif // CXFLEXITEM_H
