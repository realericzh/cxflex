import QtQuick

import Flexbox

Text {
    id: control

    Flexbox.width: 55
    Flexbox.height: 32

    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter

    font {
        pixelSize: 12
        bold: true
    }
}
