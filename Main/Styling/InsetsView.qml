import QtQuick
import QtQuick.Controls

import Flexbox

ScrollView {
    id: scrollView

    contentWidth: width

    ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

    Item {
        width: scrollView.width

        Flexbox.flexDirection: Flexbox.Column
        Flexbox.padding: 24
        Flexbox.gap: 16

        TextViewer {
            fileName: "Styling/InsetsView.txt"
        }

        Item {
            Flexbox.flexDirection: Flexbox.Row
            Flexbox.gap: 16

            CodeViewer {
                fileName: "Styling/InsetsCode.qml"
            }

            PreviewBox {
                InsetsCode { }
            }
        }
    }
}
