import QtQuick
import QtQuick.Effects
import QtQuick.Templates

import CxFlex

ComboBox {
    id: control

    CxFlexible.preferredHeight: 32

    font {
        pixelSize: 14
    }

    delegate: ItemDelegate {
        width: control.width
        height: 32

        contentItem: Text {
            text: elementText
            color: "#595959"
            font: control.font
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
            leftPadding: 12
            rightPadding: 12
        }
        highlighted: control.highlightedIndex === index
        background: Rectangle {
            color: parent.highlighted ? "#eefff8" : "#ffffff"
        }
    }

    background: Rectangle {
        border {
            width: 1
            color: control.enabled && (control.activeFocus || control.hovered) ? "#8ad6c4" : "#d4d4d4"
        }
        color: control.enabled ? "#ffffff" : "#f3f3f3"
        radius: 4
    }

    contentItem: Text {
        leftPadding: 12
        rightPadding: control.indicator.width + control.spacing + 12

        text: control.displayText
        font: control.font
        color: control.enabled && (control.activeFocus || control.hovered) ? "#8ad6c4" : "#595959"
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    indicator: Canvas {
        id: canvas
        anchors {
            verticalCenter: control.verticalCenter
            right: control.right
            rightMargin: 12
        }
        width: 12
        height: 8
        contextType: "2d"

        rotation: control.popup.visible ? 180: 0

        Connections {
            target: control
            function onPressedChanged() { canvas.requestPaint(); }
            function onActiveFocusChanged() { canvas.requestPaint(); }
        }

        onPaint: {
            context.reset();
            context.moveTo(0, 0);
            context.lineTo(width, 0);
            context.lineTo(width / 2, height);
            context.closePath();
            context.fillStyle = control.enabled && (control.activeFocus || control.hovered) ? "#8ad6c4" : "#595959";
            context.fill();
        }
    }

    popup: Popup {
        y: control.height + 4
        width: control.width
        implicitHeight: 32 * control.model.count + 8
        topPadding: 4
        bottomPadding: 4

        contentItem: ListView {
            clip: true
            implicitHeight: contentHeight
            model: control.popup.visible ? control.delegateModel : null
            currentIndex: control.highlightedIndex

            ScrollIndicator.vertical: ScrollIndicator { }
        }

        background: Item {
            Rectangle {
                id: popback
                anchors {
                    fill: parent
                }

                radius: 4
                color: "#ffffff"
                visible: false
            }

            MultiEffect {
                anchors {
                    fill: popback
                }

                source: popback

                shadowEnabled: true
                shadowColor: "#000000"
                shadowOpacity: 0.2
                shadowHorizontalOffset: 3
                shadowVerticalOffset: 3
            }
        }
    }

    textRole: "elementText"
}
