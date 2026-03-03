import QtQuick
import QtQuick.Effects

import Flexbox

Item {
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
