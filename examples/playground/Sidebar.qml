import QtQuick
import QtQuick.Effects
import QtQuick.Controls

import CxFlex

CxFlexColumn {
    id: sidebar

    preferredWidth: 350
    preferredHeight: currentItem ? 428 : 108

    position: CxFlex.PositionAbsolute

    positionTop: 25
    positionRight: 25

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

    CxFlexRow {
        id: tabbarNode

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

        preferredHeight: 45

        visible: currentItem != null
    }

    CxFlexRow {
        id: swipeViewNode

        flexGrow: 1

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

    CxFlexRow {
        id: buttonNode

        preferredHeight: 62

        visible: currentItem != null

        justifyContent: CxFlex.JustifyCenter

        columnGap: 15

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

    CxFlexRow {
        preferredWidth: "100%"
        preferredHeight: "100%"

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

            preferredWidth: 100
            preferredHeight: 100
        }
    }

    Component.onCompleted: {
        subNodeComponnet.createObject(rootItem)
        subNodeComponnet.createObject(rootItem)
        subNodeComponnet.createObject(rootItem)
    }
}
