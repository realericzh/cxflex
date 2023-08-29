import QtQuick
import QtQuick.Templates

import CxFlex

TextField {
    id: control

    CxFlexible.preferredHeight: 32

    property bool center: false

    background: Rectangle {
        border {
            width: 1
            color: control.enabled && (control.activeFocus || control.hovered) ? "#8ad6c4" : "#d4d4d4"
        }
        color: control.enabled ? "#ffffff" : "#f3f3f3"
        radius: 4
    }

    placeholderTextColor: "#b7b7b7"
    selectedTextColor: "#ffffff"
    selectionColor: "#60c7b3"
    color: "#595959"

    font {
        pixelSize: 14
    }

    leftPadding: 12
    rightPadding: 12

    horizontalAlignment: control.center ? Text.AlignHCenter : Text.AlignLeft
    verticalAlignment: Text.AlignVCenter

    Text {
        id: placeholder

        x: control.leftPadding
        y: control.topPadding
        width: control.width - (control.leftPadding + control.rightPadding)
        height: control.height - (control.topPadding + control.bottomPadding)

        font: control.font
        text: control.placeholderText
        color: control.placeholderTextColor
        verticalAlignment: control.verticalAlignment
        visible: !control.length && !control.preeditText && (!control.activeFocus || control.horizontalAlignment !== Qt.AlignHCenter)
        renderType: control.renderType
        elide: Text.ElideRight
    }
}
