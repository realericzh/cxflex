import QtQuick
import QtQuick.Effects
import QtQuick.Controls

import CxFlex

Window {
    width: 1280
    height: 800
    visible: true
    title: qsTr("Playground")
    color: "#f3f3f3"

    property var currentItem: null

    property alias rootItem: rootItem2

    MouseArea {
        anchors {
            fill: parent
        }

        onClicked: {
            currentItem = null
        }
    }

    CxFlexRow {
        anchors {
            fill: parent
        }

        CxFlexRow {
            justifyContent: CxFlex.JustifyCenter
            alignItems: CxFlex.AlignCenter

            marginLeft: -175
            marginRight: 175

            flexGrow: 1

            MultiEffect {
                anchors {
                    fill: rootItem2
                }

                source: rootItem2

                shadowEnabled: true
                shadowColor: "#000000"
                shadowOpacity: 0.2
                shadowHorizontalOffset: 3
                shadowVerticalOffset: 3
            }

            PickableItem {
                id: rootItem2

                preferredWidth: 500
                preferredHeight: 500
            }
        }

        Sidebar { }
    }
}
