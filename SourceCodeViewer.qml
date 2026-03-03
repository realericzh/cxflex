import QtQuick
import QtQuick.Controls.Basic

import Flexbox

Item {
    id: codeViewer

    property string fileName: ""

    ScrollView {
        anchors {
            fill: parent
        }

        TextArea {
            font {
                family: "Fira Code"
                pixelSize: 14
            }
            color: "#000000"
            padding: 16
            readOnly: true

            background: Rectangle {
                radius: 2
                color: "#ebedf0"

                border {
                    width: 1
                    color: "#8d949e"
                }
            }

            SyntaxHighlighter {
                id: syntaxHighlighter
            }

            Component.onCompleted: {
                if (codeViewer.fileName !== "") {
                    text = syntaxHighlighter.loadCode(codeViewer.fileName);
                }
            }
        }
    }
}
