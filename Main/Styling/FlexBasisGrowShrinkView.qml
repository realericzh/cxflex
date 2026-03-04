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
            fileName: "Styling/FlexBasisGrowShrinkView1.txt"
        }

        Item {
            Flexbox.flexDirection: Flexbox.Row
            Flexbox.gap: 16

            CodeViewer {
                fileName: "Styling/FlexBasisGrowShrinkCode1.qml"
            }

            PreviewBox {
                FlexBasisGrowShrinkCode1 { }
            }
        }

        TextViewer {
            fileName: "Styling/FlexBasisGrowShrinkView2.txt"
        }

        Item {
            Flexbox.flexDirection: Flexbox.Row
            Flexbox.gap: 16

            CodeViewer {
                fileName: "Styling/FlexBasisGrowShrinkCode2.qml"
            }

            PreviewBox {
                FlexBasisGrowShrinkCode2 { }
            }
        }

        TextViewer {
            fileName: "Styling/FlexBasisGrowShrinkView3.txt"
        }

        Item {
            Flexbox.flexDirection: Flexbox.Row
            Flexbox.gap: 16

            CodeViewer {
                fileName: "Styling/FlexBasisGrowShrinkCode3.qml"
            }

            PreviewBox {
                FlexBasisGrowShrinkCode3 { }
            }
        }
    }
}
