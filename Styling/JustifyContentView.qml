import QtQuick
import QtQuick.Controls

import Flexbox

Item {
    Flexbox.flexDirection: Flexbox.Column

    Flexbox.padding: 24

    Item {
        Flexbox.flexDirection: Flexbox.Row

        Flexbox.height: 360
        Flexbox.gap: 16

        SourceCodeViewer {
            Flexbox.flexGrow: 1

            fileName: "Styling/JustifyContentCode.qml"
        }

        Rectangle {
            Flexbox.flexDirection: Flexbox.Row
            Flexbox.justifyContent: Flexbox.Center
            Flexbox.alignItems: Flexbox.Center

            Flexbox.width: 360

            radius: 6
            color: "#469f8f"

            JustifyContentCode { }
        }
    }
}
