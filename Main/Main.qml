import QtQuick
import QtQuick.Layouts

import Flexbox

Window {
    width: 1280
    height: 800

    minimumWidth: 1280
    minimumHeight: 800

    visible: true

    title: qsTr("Flexbox for QML")

    Item {
        anchors.fill: parent

        Flexbox.flexDirection: Flexbox.Row

        Item { // sidebar -->
            id: sidebar

            Flexbox.width: 300

            Column {
                Repeater {
                    model: ListModel {
                        ListElement { displayText: "Playground" }
                        ListElement { displayText: "Align Content" }
                        ListElement { displayText: "Align Items" }
                        ListElement { displayText: "Aspect Ratio" }
                        ListElement { displayText: "Display" }
                        ListElement { displayText: "Flex Basis, Grow, and Shrink" }
                        ListElement { displayText: "Flex Direction" }
                        ListElement { displayText: "Flex Wrap" }
                        ListElement { displayText: "Gaps" }
                        ListElement { displayText: "Insets" }
                        ListElement { displayText: "Justify Content" }
                        ListElement { displayText: "Layout Direction" }
                        ListElement { displayText: "Margin, Padding, and Border" }
                        ListElement { displayText: "Position" }
                        ListElement { displayText: "Min/Max Width and Height" }
                        ListElement { displayText: "Width and Height" }
                    }
                    delegate: Item {
                        width: sidebar.width

                        height: 50

                        Text {
                            anchors {
                                centerIn: parent
                            }

                            text: displayText

                            color: stackLayout.currentIndex === index ? "#6bcebb" : "#1c1e21"

                            font.pixelSize: 16
                            font.bold: true
                        }

                        MouseArea {
                            anchors {
                                fill: parent
                            }

                            onClicked: {
                                stackLayout.currentIndex = index;
                            }
                        }
                    }
                }
            }
        } // <-- sidebar

        Rectangle {
            Flexbox.width: 1

            color: "#d9d9d9"
        }

        Item { // content -->
            Flexbox.flexGrow: 1

            StackLayout {
                id: stackLayout
                anchors {
                    fill: parent
                }

                Playground { }

                Loader { source: visible ? "qrc:///qt/qml/Flexbox/Main/Styling/AlignContentView.qml" : "" }
                Loader { source: visible ? "qrc:///qt/qml/Flexbox/Main/Styling/AlignItemsView.qml" : "" }
                Loader { source: visible ? "qrc:///qt/qml/Flexbox/Main/Styling/AspectRatioView.qml" : "" }
                Loader { source: visible ? "qrc:///qt/qml/Flexbox/Main/Styling/DisplayView.qml" : "" }
                Loader { source: visible ? "qrc:///qt/qml/Flexbox/Main/Styling/FlexBasisGrowShrinkView.qml" : "" }
                Loader { source: visible ? "qrc:///qt/qml/Flexbox/Main/Styling/FlexDirectionView.qml" : "" }
                Loader { source: visible ? "qrc:///qt/qml/Flexbox/Main/Styling/FlexWrapView.qml" : "" }
                Loader { source: visible ? "qrc:///qt/qml/Flexbox/Main/Styling/GapView.qml" : "" }
                Loader { source: visible ? "qrc:///qt/qml/Flexbox/Main/Styling/InsetsView.qml" : "" }
                Loader { source: visible ? "qrc:///qt/qml/Flexbox/Main/Styling/JustifyContentView.qml" : "" }
                Loader { source: visible ? "qrc:///qt/qml/Flexbox/Main/Styling/LayoutDirectionView.qml" : "" }
                Loader { source: visible ? "qrc:///qt/qml/Flexbox/Main/Styling/MarginPaddingBorderView.qml" : "" }
                Loader { source: visible ? "qrc:///qt/qml/Flexbox/Main/Styling/PositionView.qml" : "" }
                Loader { source: visible ? "qrc:///qt/qml/Flexbox/Main/Styling/MinMaxWidthHeightView.qml" : "" }
                Loader { source: visible ? "qrc:///qt/qml/Flexbox/Main/Styling/WidthHeightView.qml" : "" }
            }
        } // <-- content
    }
}
