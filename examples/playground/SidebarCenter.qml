import QtQuick

import CxFlex

Text {
    id: control

    CxFlexible.preferredWidth: 55
    CxFlexible.preferredHeight: 32

    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter

    font {
        pixelSize: 12
        bold: true
    }
}
