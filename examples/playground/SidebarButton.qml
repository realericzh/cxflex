import QtQuick
import QtQuick.Templates

import CxFlex

Button {
    id: control

    CxFlexible.marginTop: 20
    CxFlexible.marginBottom: 8
    CxFlexible.preferredWidth: 152
    CxFlexible.preferredHeight: 32

    property bool warning: false

    background: Rectangle {
        height: 32
        color: {
            if (control.warning) {
                if (!control.enabled) {
                    return "#f3f3f3"
                } else if (control.pressed) {
                    return "#d42f36"
                } else if (control.hovered) {
                    return "#ff6d6a"
                }


                return "#ff4446"
            }

            if (!control.enabled) {
                return "#f3f3f3"
            } else if (control.pressed) {
                return "#469e8e"
            } else if (control.hovered) {
                return "#8ad6c4"
            }


            return "#60c7b3"
        }
        radius: 4

        border {
            width: 1
            color: control.enabled ? "transparent" : "#d4d4d4"
        }
    }

    contentItem: Text {
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        text: control.text
        font {
            pixelSize: 14
        }
        color: control.enabled ? "#ffffff" : "#b6b6b6"
    }
}
