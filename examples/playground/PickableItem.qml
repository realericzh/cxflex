import QtQuick

import CxFlex

CxFlexItem {
    id: flexNode

    Rectangle {
        anchors {
            fill: parent
        }

        color: mouseArea.containsMouse ? "#f3fffa" : "#ffffff"
        border {
            width: currentItem === flexNode ? 2 : 1
            color: currentItem === flexNode ? "#5dc8b3" : "#caccce"
        }
    }

    MouseArea {
        id: mouseArea
        anchors {
            fill: parent
        }

        hoverEnabled: true
        onClicked: {
            currentItem = flexNode
        }
    }

    Behavior on width {
        NumberAnimation { duration: 250 }
    }
    Behavior on height {
        NumberAnimation { duration: 250 }
    }
}
