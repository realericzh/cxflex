import QtQuick

import CxFlex

Item {
    id: swipeButton

    Flexbox.flexGrow: 1

    property alias text: buttonText.text

    signal clicked()

    MouseArea {
        id: mouseArea
        anchors {
            fill: parent
        }

        hoverEnabled: true
        onClicked: {
            swipeButton.clicked()
        }
    }

    Text {
        id: buttonText
        anchors {
            centerIn: parent
        }

        color: mouseArea.containsMouse ? "#60c7b3" : "#595959"
        font {
            pixelSize: 14
        }
    }
}
