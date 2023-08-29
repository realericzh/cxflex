#ifndef CXFLEX_H
#define CXFLEX_H

#include <QQuickItem>

class CxFlex : public QObject
{
    Q_OBJECT

public:
    enum Direction {
        DirectionInherit,
        DirectionLTR,
        DirectionRTL,
    };
    Q_ENUM(Direction)

    enum Position {
        PositionStatic,
        PositionRelative,
        PositionAbsolute,
    };
    Q_ENUM(Position)

    enum Display {
        DisplayFlex,
        DisplayNone,
    };
    Q_ENUM(Display)

    enum Overflow {
        OverflowVisible,
        OverflowHidden,
        OverflowScroll,
    };
    Q_ENUM(Overflow)

    enum FlexDirection {
        FlexDirectionColumn,
        FlexDirectionColumnReverse,
        FlexDirectionRow,
        FlexDirectionRowReverse,
    };
    Q_ENUM(FlexDirection)

    enum Justify {
        JustifyFlexStart,
        JustifyCenter,
        JustifyFlexEnd,
        JustifySpaceBetween,
        JustifySpaceAround,
        JustifySpaceEvenly,
    };
    Q_ENUM(Justify)

    enum Align {
        AlignAuto,
        AlignFlexStart,
        AlignCenter,
        AlignFlexEnd,
        AlignStretch,
        AlignBaseline,
        AlignSpaceBetween,
        AlignSpaceAround,
    };
    Q_ENUM(Align)

    enum Wrap {
        WrapNoWrap,
        WrapWrap,
        WrapWrapReverse,
    };
    Q_ENUM(Wrap);
};

#endif // CXFLEX_H
