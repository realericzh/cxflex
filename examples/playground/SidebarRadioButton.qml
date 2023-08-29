import QtQuick
import QtQuick.Effects
import QtQuick.Templates

import CxFlex

Button {
    id: control

    CxFlexible.flexGrow: 1
    CxFlexible.preferredHeight: 32

    property int radiusPosition: 0

    CxFlexible.marginLeft: radiusPosition == 0 ? -1 : undefined
    CxFlexible.marginRight: radiusPosition == 0 ? -1 : undefined

    z: control.checked ? 2 : control.hovered ? 1 : 0

    checkable: true

    font {
        pixelSize: 14
    }

    background: Item {
        id: backgroundItem

        Item {
            anchors {
                top: parent.top
                left: control.radiusPosition < 0 ? parent.left : undefined
                right: control.radiusPosition > 0 ? parent.right : undefined
                bottom: parent.bottom
            }

            width: 8

            Rectangle {
                anchors {
                    fill: parent
                }

                border {
                    width: 1
                    color: control.enabled ? (control.checked ? "#60c7b3" : (control.activeFocus || control.hovered ? "#8ad6c4" : "#d4d4d4")) : "#d4d4d4"
                }
                color: control.enabled ? "#ffffff" : control.checked ? "#e2e2e2" : "#f3f3f3"
                radius: 4
            }
        }

        Item {
            anchors {
                fill: parent

                leftMargin: control.radiusPosition < 0 ? 4 : 0
                rightMargin: control.radiusPosition > 0 ? 4 : 0
            }

            clip: true

            Rectangle {
                anchors {
                    fill: parent

                    leftMargin: control.radiusPosition < 0 ? -4 : 0
                    rightMargin: control.radiusPosition > 0 ? -4 : 0
                }

                border {
                    width: 1
                    color: control.enabled ? (control.checked ? "#60c7b3" : (control.activeFocus || control.hovered ? "#8ad6c4" : "#d4d4d4")) : "#d4d4d4"
                }
                color: control.enabled ? "#ffffff" : control.checked ? "#e2e2e2" : "#f3f3f3"
            }
        }
    }

    contentItem: Text {
        text: control.text
        font: control.font
        color: control.checked ? (control.enabled ? "#60c7b3" : "#ffffff") : (control.enabled ? (control.activeFocus || control.hovered ? "#8ad6c4" : "#595959") : "#b6b6b6")
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }
}
