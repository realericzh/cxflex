import QtQuick
import QtQuick.Effects
import QtQuick.Controls

import CxFlex

Item {
    id: sidebar

    Flexbox.width: 350
    Flexbox.height: currentItem ? 428 : 108

    Flexbox.position: Flexbox.PositionAbsolute

    Flexbox.positionTop: 25
    Flexbox.positionRight: 25

    Rectangle {
        id: background
        anchors {
            fill: parent
        }

        color: "#ffffff"
        radius: 6
        visible: false
    }

    MultiEffect {
        anchors {
            fill: background
        }

        source: background

        shadowEnabled: true
        shadowColor: "#000000"
        shadowOpacity: 0.2
        shadowHorizontalOffset: 3
        shadowVerticalOffset: 3
    }

    Item {
        id: tabbarNode

        Flexbox.flexDirection: Flexbox.FlexDirectionRow

        SwipeButton {
            text: "Flex"
            onClicked: {
                swipeView.currentIndex = 0
            }
        }

        SwipeButton {
            text: "Alignment"
            onClicked: {
                swipeView.currentIndex = 1
            }
        }

        SwipeButton {
            text: "Layout"
            onClicked: {
                swipeView.currentIndex = 2
            }
        }

        Rectangle {
            anchors {
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }

            height: 1
            color: "#e5e5e5"
        }

        Rectangle {
            y: parent.height - 2
            width: parent.width / 3
            height: 2
            color: "#60c7b3"
            x: width * swipeView.currentIndex
        }

        Flexbox.height: 45

        visible: currentItem != null
    }

    Item {
        id: swipeViewNode

        Flexbox.flexDirection: Flexbox.FlexDirectionRow

        Flexbox.flexGrow: 1

        SwipeView {
            id: swipeView
            anchors {
                fill: parent
            }

            interactive: false

            clip: true

            SidebarViewFlex { }
            SidebarViewAlignment { }
            SidebarViewLayout { }
        }

        visible: currentItem != null
    }

    Item {
        id: buttonNode

        Flexbox.flexDirection: Flexbox.FlexDirectionRow

        Flexbox.height: 62

        visible: currentItem != null

        Flexbox.justifyContent: Flexbox.JustifyCenter

        Flexbox.columnGap: 15

        SidebarButton {
            text: "add child node"
            enabled: currentItem
            onClicked: {
                subNodeComponnet.createObject(currentItem)
            }
        }

        SidebarButton {
            text: "remove node"
            enabled: currentItem && currentItem != rootItem
            onClicked: {
                currentItem.destroy()
                currentItem = null
            }
            warning: true
        }
    }

    Item {
        Flexbox.flexDirection: Flexbox.FlexDirectionRow

        Flexbox.width: "100%"
        Flexbox.height: "100%"

        Text {
            anchors {
                centerIn: parent
            }

            text: "Select a node to edit its properties"
            font {
                pixelSize: 18
            }
            color: "#d4d4d4"
        }

        visible: currentItem == null
    }

    Component {
        id: subNodeComponnet

        PickableItem {
            Behavior on x {
                NumberAnimation { duration: 250 }
            }
            Behavior on y {
                NumberAnimation { duration: 250 }
            }

            Flexbox.width: 100
            Flexbox.height: 100
        }
    }

    Component.onCompleted: {
        subNodeComponnet.createObject(rootItem)
        subNodeComponnet.createObject(rootItem)
        subNodeComponnet.createObject(rootItem)
    }
}
