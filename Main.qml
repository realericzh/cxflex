import QtQuick
import QtQuick.Effects
import QtQuick.Controls

import Flexbox

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

    Item {
        anchors {
            fill: parent
        }

        Flexbox.flexDirection: Flexbox.Row

        Item {
            Flexbox.justifyContent: Flexbox.Center
            Flexbox.alignItems: Flexbox.Center

            Flexbox.leftMargin: -175
            Flexbox.rightMargin: 175

            Flexbox.flexGrow: 1

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

                Flexbox.width: 500
                Flexbox.height: 500
            }
        }

        Sidebar { }
    }
}
