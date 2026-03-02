#ifndef REALERICZH_FLEXBOX_H
#define REALERICZH_FLEXBOX_H

#include <QObject>
#include <QJSValue>
#include <QtQmlIntegration>

// class Flexbox

class FlexboxAttached;

class Flexbox : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_ATTACHED(FlexboxAttached)

public:
    static FlexboxAttached *qmlAttachedProperties(QObject *attachee);

public:
    enum Generic {
        // Align
        Auto,
        FlexStart,
        Center,
        FlexEnd,
        Stretch,
        Baseline,
        SpaceBetween,
        SpaceAround,
        SpaceEvenly,

        // BoxSizing
        BorderBox,
        ContentBox,

        // Direction
        Inherit,
        LTR,
        RTL,

        // Display
        Flex,
        None,
        Contents,

        // FlexDirection
        Column,
        ColumnReverse,
        Row,
        RowReverse,

        // Justify
        // FlexStart,
        // Center,
        // FlexEnd,
        // SpaceBetween,
        // SpaceAround,
        // SpaceEvenly,

        // Overflow
        Visible,
        Hidden,
        Scroll,

        // Position
        Static,
        Relative,
        Absolute,

        // Wrap
        NoWrap,
        Wrap,
        WrapReverse,
    };
    Q_ENUM(Generic)
};

// class FlexboxAttached

class FlexboxAttachedPrivate;
class FlexboxAttached : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(FlexboxAttached)

    Q_PROPERTY(Flexbox::Generic direction READ direction WRITE setDirection NOTIFY directionChanged)
    Q_PROPERTY(Flexbox::Generic position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(Flexbox::Generic display READ display WRITE setDisplay NOTIFY displayChanged)
    Q_PROPERTY(Flexbox::Generic overflow READ overflow WRITE setOverflow NOTIFY overflowChanged)
    Q_PROPERTY(Flexbox::Generic boxSizing READ boxSizing WRITE setBoxSizing NOTIFY boxSizingChanged)

    Q_PROPERTY(Flexbox::Generic justifyContent READ justifyContent WRITE setJustifyContent NOTIFY justifyContentChanged)
    Q_PROPERTY(Flexbox::Generic flexDirection READ flexDirection WRITE setFlexDirection NOTIFY flexDirectionChanged)
    Q_PROPERTY(Flexbox::Generic alignContent READ alignContent WRITE setAlignContent NOTIFY alignContentChanged)
    Q_PROPERTY(Flexbox::Generic alignItems READ alignItems WRITE setAlignItems NOTIFY alignItemsChanged)
    Q_PROPERTY(Flexbox::Generic alignSelf READ alignSelf WRITE setAlignSelf NOTIFY alignSelfChanged)
    Q_PROPERTY(Flexbox::Generic flexWrap READ flexWrap WRITE setFlexWrap NOTIFY flexWrapChanged)

    Q_PROPERTY(QJSValue left READ left WRITE setLeft NOTIFY leftChanged)
    Q_PROPERTY(QJSValue top READ top WRITE setTop NOTIFY topChanged)
    Q_PROPERTY(QJSValue right READ right WRITE setRight NOTIFY rightChanged)
    Q_PROPERTY(QJSValue bottom READ bottom WRITE setBottom NOTIFY bottomChanged)
    Q_PROPERTY(QJSValue start READ start WRITE setStart NOTIFY startChanged)
    Q_PROPERTY(QJSValue end READ end WRITE setEnd NOTIFY endChanged)

    Q_PROPERTY(QJSValue width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(QJSValue height READ height WRITE setHeight NOTIFY heightChanged)

    Q_PROPERTY(QJSValue minimumWidth READ minimumWidth WRITE setMinimumWidth NOTIFY minimumWidthChanged)
    Q_PROPERTY(QJSValue minimumHeight READ minimumHeight WRITE setMinimumHeight NOTIFY minimumHeightChanged)
    Q_PROPERTY(QJSValue maximumWidth READ maximumWidth WRITE setMaximumWidth NOTIFY maximumWidthChanged)
    Q_PROPERTY(QJSValue maximumHeight READ maximumHeight WRITE setMaximumHeight NOTIFY maximumHeightChanged)

    Q_PROPERTY(QJSValue leftMargin READ leftMargin WRITE setLeftMargin NOTIFY leftMarginChanged)
    Q_PROPERTY(QJSValue topMargin READ topMargin WRITE setTopMargin NOTIFY topMarginChanged)
    Q_PROPERTY(QJSValue rightMargin READ rightMargin WRITE setRightMargin NOTIFY rightMarginChanged)
    Q_PROPERTY(QJSValue bottomMargin READ bottomMargin WRITE setBottomMargin NOTIFY bottomMarginChanged)
    Q_PROPERTY(QJSValue startMargin READ startMargin WRITE setStartMargin NOTIFY startMarginChanged)
    Q_PROPERTY(QJSValue endMargin READ endMargin WRITE setEndMargin NOTIFY endMarginChanged)
    Q_PROPERTY(QJSValue horizontalMargin READ horizontalMargin WRITE setHorizontalMargin NOTIFY horizontalMarginChanged)
    Q_PROPERTY(QJSValue verticalMargin READ verticalMargin WRITE setVerticalMargin NOTIFY verticalMarginChanged)
    Q_PROPERTY(QJSValue margins READ margins WRITE setMargins NOTIFY marginsChanged)

    Q_PROPERTY(QJSValue leftPadding READ leftPadding WRITE setLeftPadding NOTIFY leftPaddingChanged)
    Q_PROPERTY(QJSValue topPadding READ topPadding WRITE setTopPadding NOTIFY topPaddingChanged)
    Q_PROPERTY(QJSValue rightPadding READ rightPadding WRITE setRightPadding NOTIFY rightPaddingChanged)
    Q_PROPERTY(QJSValue bottomPadding READ bottomPadding WRITE setBottomPadding NOTIFY bottomPaddingChanged)
    Q_PROPERTY(QJSValue startPadding READ startPadding WRITE setStartPadding NOTIFY startPaddingChanged)
    Q_PROPERTY(QJSValue endPadding READ endPadding WRITE setEndPadding NOTIFY endPaddingChanged)
    Q_PROPERTY(QJSValue horizontalPadding READ horizontalPadding WRITE setHorizontalPadding NOTIFY horizontalPaddingChanged)
    Q_PROPERTY(QJSValue verticalPadding READ verticalPadding WRITE setVerticalPadding NOTIFY verticalPaddingChanged)
    Q_PROPERTY(QJSValue padding READ padding WRITE setPadding NOTIFY paddingChanged)

    Q_PROPERTY(QJSValue leftBorder READ leftBorder WRITE setLeftBorder NOTIFY leftBorderChanged)
    Q_PROPERTY(QJSValue topBorder READ topBorder WRITE setTopBorder NOTIFY topBorderChanged)
    Q_PROPERTY(QJSValue rightBorder READ rightBorder WRITE setRightBorder NOTIFY rightBorderChanged)
    Q_PROPERTY(QJSValue bottomBorder READ bottomBorder WRITE setBottomBorder NOTIFY bottomBorderChanged)
    Q_PROPERTY(QJSValue startBorder READ startBorder WRITE setStartBorder NOTIFY startBorderChanged)
    Q_PROPERTY(QJSValue endBorder READ endBorder WRITE setEndBorder NOTIFY endBorderChanged)
    Q_PROPERTY(QJSValue horizontalBorder READ horizontalBorder WRITE setHorizontalBorder NOTIFY horizontalBorderChanged)
    Q_PROPERTY(QJSValue verticalBorder READ verticalBorder WRITE setVerticalBorder NOTIFY verticalBorderChanged)
    Q_PROPERTY(QJSValue borders READ borders WRITE setBorders NOTIFY bordersChanged)

    Q_PROPERTY(QJSValue columnGap READ columnGap WRITE setColumnGap NOTIFY columnGapChanged)
    Q_PROPERTY(QJSValue rowGap READ rowGap WRITE setRowGap NOTIFY rowGapChanged)
    Q_PROPERTY(QJSValue gap READ gap WRITE setGap NOTIFY gapChanged)

    Q_PROPERTY(QJSValue flex READ flex WRITE setFlex NOTIFY flexChanged)
    Q_PROPERTY(QJSValue flexGrow READ flexGrow WRITE setFlexGrow NOTIFY flexGrowChanged)
    Q_PROPERTY(QJSValue flexBasis READ flexBasis WRITE setFlexBasis NOTIFY flexBasisChanged)
    Q_PROPERTY(QJSValue flexShrink READ flexShrink WRITE setFlexShrink NOTIFY flexShrinkChanged)

    Q_PROPERTY(QJSValue aspectRatio READ aspectRatio WRITE setAspectRatio NOTIFY aspectRatioChanged)

public:
    explicit FlexboxAttached(QObject *parent = nullptr);
    virtual ~FlexboxAttached() override;
protected:
    QScopedPointer<FlexboxAttachedPrivate> d_ptr;

signals:
    void directionChanged();
    void positionChanged();
    void displayChanged();
    void overflowChanged();
    void boxSizingChanged();
public:
    void setDirection(Flexbox::Generic value);
    void setPosition(Flexbox::Generic value);
    void setDisplay(Flexbox::Generic value);
    void setOverflow(Flexbox::Generic value);
    void setBoxSizing(Flexbox::Generic value);
public:
    Flexbox::Generic direction() const;
    Flexbox::Generic position() const;
    Flexbox::Generic display() const;
    Flexbox::Generic overflow() const;
    Flexbox::Generic boxSizing() const;

signals:
    void justifyContentChanged();
    void flexDirectionChanged();
    void alignContentChanged();
    void alignItemsChanged();
    void alignSelfChanged();
    void flexWrapChanged();
public:
    void setJustifyContent(Flexbox::Generic value);
    void setFlexDirection(Flexbox::Generic value);
    void setAlignContent(Flexbox::Generic value);
    void setAlignItems(Flexbox::Generic value);
    void setAlignSelf(Flexbox::Generic value);
    void setFlexWrap(Flexbox::Generic value);
public:
    Flexbox::Generic justifyContent() const;
    Flexbox::Generic flexDirection() const;
    Flexbox::Generic alignContent() const;
    Flexbox::Generic alignItems() const;
    Flexbox::Generic alignSelf() const;
    Flexbox::Generic flexWrap() const;

signals:
    void leftChanged();
    void topChanged();
    void rightChanged();
    void bottomChanged();
    void startChanged();
    void endChanged();
public:
    void setLeft(QJSValue value);
    void setTop(QJSValue value);
    void setRight(QJSValue value);
    void setBottom(QJSValue value);
    void setStart(QJSValue value);
    void setEnd(QJSValue value);
public:
    QJSValue left() const;
    QJSValue top() const;
    QJSValue right() const;
    QJSValue bottom() const;
    QJSValue start() const;
    QJSValue end() const;

signals:
    void widthChanged();
    void heightChanged();
public:
    void setWidth(QJSValue value);
    void setHeight(QJSValue value);
public:
    QJSValue width() const;
    QJSValue height() const;

signals:
    void minimumWidthChanged();
    void minimumHeightChanged();
    void maximumWidthChanged();
    void maximumHeightChanged();
public:
    void setMinimumWidth(QJSValue value);
    void setMinimumHeight(QJSValue value);
    void setMaximumWidth(QJSValue value);
    void setMaximumHeight(QJSValue value);
public:
    QJSValue minimumWidth() const;
    QJSValue minimumHeight() const;
    QJSValue maximumWidth() const;
    QJSValue maximumHeight() const;

signals:
    void leftMarginChanged();
    void topMarginChanged();
    void rightMarginChanged();
    void bottomMarginChanged();
    void startMarginChanged();
    void endMarginChanged();
    void horizontalMarginChanged();
    void verticalMarginChanged();
    void marginsChanged();
public:
    void setLeftMargin(QJSValue value);
    void setTopMargin(QJSValue value);
    void setRightMargin(QJSValue value);
    void setBottomMargin(QJSValue value);
    void setStartMargin(QJSValue value);
    void setEndMargin(QJSValue value);
    void setHorizontalMargin(QJSValue value);
    void setVerticalMargin(QJSValue value);
    void setMargins(QJSValue value);
public:
    QJSValue leftMargin() const;
    QJSValue topMargin() const;
    QJSValue rightMargin() const;
    QJSValue bottomMargin() const;
    QJSValue startMargin() const;
    QJSValue endMargin() const;
    QJSValue horizontalMargin() const;
    QJSValue verticalMargin() const;
    QJSValue margins() const;

signals:
    void leftPaddingChanged();
    void topPaddingChanged();
    void rightPaddingChanged();
    void bottomPaddingChanged();
    void startPaddingChanged();
    void endPaddingChanged();
    void horizontalPaddingChanged();
    void verticalPaddingChanged();
    void paddingChanged();
public:
    void setLeftPadding(QJSValue value);
    void setTopPadding(QJSValue value);
    void setRightPadding(QJSValue value);
    void setBottomPadding(QJSValue value);
    void setStartPadding(QJSValue value);
    void setEndPadding(QJSValue value);
    void setHorizontalPadding(QJSValue value);
    void setVerticalPadding(QJSValue value);
    void setPadding(QJSValue value);
public:
    QJSValue leftPadding() const;
    QJSValue topPadding() const;
    QJSValue rightPadding() const;
    QJSValue bottomPadding() const;
    QJSValue startPadding() const;
    QJSValue endPadding() const;
    QJSValue horizontalPadding() const;
    QJSValue verticalPadding() const;
    QJSValue padding() const;

signals:
    void leftBorderChanged();
    void topBorderChanged();
    void rightBorderChanged();
    void bottomBorderChanged();
    void startBorderChanged();
    void endBorderChanged();
    void horizontalBorderChanged();
    void verticalBorderChanged();
    void bordersChanged();
public:
    void setLeftBorder(QJSValue value);
    void setTopBorder(QJSValue value);
    void setRightBorder(QJSValue value);
    void setBottomBorder(QJSValue value);
    void setStartBorder(QJSValue value);
    void setEndBorder(QJSValue value);
    void setHorizontalBorder(QJSValue value);
    void setVerticalBorder(QJSValue value);
    void setBorders(QJSValue value);
public:
    QJSValue leftBorder() const;
    QJSValue topBorder() const;
    QJSValue rightBorder() const;
    QJSValue bottomBorder() const;
    QJSValue startBorder() const;
    QJSValue endBorder() const;
    QJSValue horizontalBorder() const;
    QJSValue verticalBorder() const;
    QJSValue borders() const;

signals:
    void columnGapChanged();
    void rowGapChanged();
    void gapChanged();
public:
    void setColumnGap(QJSValue value);
    void setRowGap(QJSValue value);
    void setGap(QJSValue value);
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
    void setFlex(QJSValue value);
    void setFlexGrow(QJSValue value);
    void setFlexBasis(QJSValue value);
    void setFlexShrink(QJSValue value);
public:
    QJSValue flex() const;
    QJSValue flexGrow() const;
    QJSValue flexBasis() const;
    QJSValue flexShrink() const;

signals:
    void aspectRatioChanged();
public:
    void setAspectRatio(QJSValue value);
public:
    QJSValue aspectRatio() const;
};

#endif // REALERICZH_FLEXBOX_H
