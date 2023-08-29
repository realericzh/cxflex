#include <QtTest>

#include "yoga/Yoga.h"

class Defaults : public QObject
{
    Q_OBJECT

private slots:
    void testDefaults();
};

//CxFlex::Direction direction() const;
//CxFlex::PositionType positionType() const;
//CxFlex::Align alignSelf() const;
//CxFlex::Overflow overflow() const;

void Defaults::testDefaults()
{
    YGNodeRef node = YGNodeNew();

    QVERIFY(YGNodeStyleGetDirection(node) == YGDirectionInherit);
    QVERIFY(YGNodeStyleGetPositionType(node) == YGPositionTypeStatic);
    QVERIFY(YGNodeStyleGetAlignSelf(node) == YGAlignAuto);
    QVERIFY(YGNodeStyleGetOverflow(node) == YGOverflowVisible);

    QVERIFY(YGNodeStyleGetFlexDirection(node) == YGFlexDirectionColumn);
    QVERIFY(YGNodeStyleGetJustifyContent(node) == YGJustifyFlexStart);
    QVERIFY(YGNodeStyleGetAlignContent(node) == YGAlignFlexStart);
    QVERIFY(YGNodeStyleGetAlignItems(node) == YGAlignStretch);
    QVERIFY(YGNodeStyleGetFlexWrap(node) == YGWrapNoWrap);

//    qInfo() << YGNodeStyleGetFlexGrow(node);
//    qInfo() << YGNodeStyleGetFlexBasis(node).unit;
//    qInfo() << YGNodeStyleGetFlexShrink(node);

    QVERIFY(YGFloatIsUndefined(YGNodeStyleGetFlex(node)));
    QVERIFY(YGNodeStyleGetFlexGrow(node) == 0);
    QVERIFY(YGNodeStyleGetFlexBasis(node).unit == YGUnitAuto);
    QVERIFY(YGNodeStyleGetFlexShrink(node) == 0);

    YGNodeFree(node);
}

QTEST_APPLESS_MAIN(Defaults)

#include "defaults.moc"
