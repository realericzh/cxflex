import QtQuick
import QtQuick.Controls.Basic

import Flexbox

Item {
    id: codeViewer

    Flexbox.height: textEdit.contentHeight + 32
    Flexbox.flexGrow: 1

    property string fileName: ""

    Rectangle {
        anchors.fill: parent

        radius: 6
        color: "#f6faf8"

        border {
            width: 1
            color: "#caccce"
        }
    }

    TextEdit {
        id: textEdit
        width: parent.width
        font {
            family: "Cascadia Mono"
            pixelSize: 14
        }
        color: "#000000"
        padding: 16
        readOnly: true

        SyntaxHighlighter {
            id: syntaxHighlighter
        }

        Component.onCompleted: {
            if (codeViewer.fileName !== "") {
                text = FlexboxApp.readFile(codeViewer.fileName);
            }
        }
    }
}
