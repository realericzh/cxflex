import QtQuick
import QtQuick.Controls.Basic

import Flexbox

TextEdit {
    id: viewer

    Flexbox.height: contentHeight

    property string fileName: ""

    font {
        pixelSize: 16
    }
    readOnly: true
    color: "#1c1e21"
    wrapMode: TextEdit.WordWrap
    textFormat: TextEdit.RichText

    Component.onCompleted: {
        if (fileName !== "") {
            text = FlexboxApp.readFile(fileName);
        }
    }
}
