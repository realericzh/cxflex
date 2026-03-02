import QtQuick
import QtQuick.Controls

import CxFlex

ScrollView {
    id: scrollView

    Item {
        Flexbox.flexDirection: Flexbox.FlexDirectionColumn

        Flexbox.padding: 15

        width: scrollView.width - 15

        SidebarLabel {
            text: "JUSTIFY CONTENT"
        }

        SidebarComboBox {
            model: ListModel {
                ListElement { elementText: "flex start" }
                ListElement { elementText: "center" }
                ListElement { elementText: "flex end" }
                ListElement { elementText: "space between" }
                ListElement { elementText: "space around" }
                ListElement { elementText: "space evenly" }
            }

            currentIndex: {
                if (currentItem == null) {
                    return 0
                }

                switch (currentItem.Flexbox.justifyContent) {
                case Flexbox.JustifyFlexStart:
                    return 0
                case Flexbox.JustifyCenter:
                    return 1
                case Flexbox.JustifyFlexEnd:
                    return 2
                case Flexbox.JustifySpaceBetween:
                    return 3
                case Flexbox.JustifySpaceAround:
                    return 4
                case Flexbox.JustifySpaceEvenly:
                    return 5
                }

                return 0
            }

            onCurrentIndexChanged: {
                if (currentItem) {
                    switch (currentIndex) {
                    case 0:
                        currentItem.Flexbox.justifyContent = Flexbox.JustifyFlexStart
                        break
                    case 1:
                        currentItem.Flexbox.justifyContent = Flexbox.JustifyCenter
                        break
                    case 2:
                        currentItem.Flexbox.justifyContent = Flexbox.JustifyFlexEnd
                        break
                    case 3:
                        currentItem.Flexbox.justifyContent = Flexbox.JustifySpaceBetween
                        break
                    case 4:
                        currentItem.Flexbox.justifyContent = Flexbox.JustifySpaceAround
                        break
                    case 5:
                        currentItem.Flexbox.justifyContent = Flexbox.JustifySpaceEvenly
                        break
                    }
                }
            }
        }

        SidebarLabel {
            text: "ALIGN ITEMS"
        }

        SidebarComboBox {
            model: ListModel {
                ListElement { elementText: "auto" }
                ListElement { elementText: "flex start" }
                ListElement { elementText: "center" }
                ListElement { elementText: "flex end" }
                ListElement { elementText: "stretch" }
                ListElement { elementText: "baseline" }
                ListElement { elementText: "space between" }
                ListElement { elementText: "space around" }
            }

            currentIndex: {
                if (currentItem == null) {
                    return 0
                }

                switch (currentItem.Flexbox.alignItems) {
                case Flexbox.AlignAuto:
                    return 0
                case Flexbox.AlignFlexStart:
                    return 1
                case Flexbox.AlignCenter:
                    return 2
                case Flexbox.AlignFlexEnd:
                    return 3
                case Flexbox.AlignStretch:
                    return 4
                case Flexbox.AlignBaseline:
                    return 5
                case Flexbox.AlignSpaceBetween:
                    return 6
                case Flexbox.AlignSpaceAround:
                    return 7
                }

                return 0
            }

            onCurrentIndexChanged: {
                if (currentItem) {
                    switch (currentIndex) {
                    case 0:
                        currentItem.Flexbox.alignItems = Flexbox.AlignAuto
                        break
                    case 1:
                        currentItem.Flexbox.alignItems = Flexbox.AlignFlexStart
                        break
                    case 2:
                        currentItem.Flexbox.alignItems = Flexbox.AlignCenter
                        break
                    case 3:
                        currentItem.Flexbox.alignItems = Flexbox.AlignFlexEnd
                        break
                    case 4:
                        currentItem.Flexbox.alignItems = Flexbox.AlignStretch
                        break
                    case 5:
                        currentItem.Flexbox.alignItems = Flexbox.AlignBaseline
                        break
                    case 6:
                        currentItem.Flexbox.alignItems = Flexbox.AlignSpaceBetween
                        break
                    case 7:
                        currentItem.Flexbox.alignItems = Flexbox.AlignSpaceAround
                        break
                    }
                }
            }
        }

        SidebarLabel {
            text: "ALIGN SELF"
        }

        SidebarComboBox {
            enabled: currentItem && currentItem != rootItem

            model: ListModel {
                ListElement { elementText: "auto" }
                ListElement { elementText: "flex start" }
                ListElement { elementText: "center" }
                ListElement { elementText: "flex end" }
                ListElement { elementText: "stretch" }
                ListElement { elementText: "baseline" }
                ListElement { elementText: "space between" }
                ListElement { elementText: "space around" }
            }

            currentIndex: {
                if (currentItem == null) {
                    return 0
                }

                switch (currentItem.Flexbox.alignSelf) {
                case Flexbox.AlignAuto:
                    return 0
                case Flexbox.AlignFlexStart:
                    return 1
                case Flexbox.AlignCenter:
                    return 2
                case Flexbox.AlignFlexEnd:
                    return 3
                case Flexbox.AlignStretch:
                    return 4
                case Flexbox.AlignBaseline:
                    return 5
                case Flexbox.AlignSpaceBetween:
                    return 6
                case Flexbox.AlignSpaceAround:
                    return 7
                }

                return 0
            }

            onCurrentIndexChanged: {
                if (currentItem) {
                    switch (currentIndex) {
                    case 0:
                        currentItem.Flexbox.alignSelf = Flexbox.AlignAuto
                        break
                    case 1:
                        currentItem.Flexbox.alignSelf = Flexbox.AlignFlexStart
                        break
                    case 2:
                        currentItem.Flexbox.alignSelf = Flexbox.AlignCenter
                        break
                    case 3:
                        currentItem.Flexbox.alignSelf = Flexbox.AlignFlexEnd
                        break
                    case 4:
                        currentItem.Flexbox.alignSelf = Flexbox.AlignStretch
                        break
                    case 5:
                        currentItem.Flexbox.alignSelf = Flexbox.AlignBaseline
                        break
                    case 6:
                        currentItem.Flexbox.alignSelf = Flexbox.AlignSpaceBetween
                        break
                    case 7:
                        currentItem.Flexbox.alignSelf = Flexbox.AlignSpaceAround
                        break
                    }
                }
            }
        }

        SidebarLabel {
            text: "ALIGN CONTENT"
        }

        SidebarComboBox {
            model: ListModel {
                ListElement { elementText: "auto" }
                ListElement { elementText: "flex start" }
                ListElement { elementText: "center" }
                ListElement { elementText: "flex end" }
                ListElement { elementText: "stretch" }
                ListElement { elementText: "baseline" }
                ListElement { elementText: "space between" }
                ListElement { elementText: "space around" }
            }

            currentIndex: {
                if (currentItem == null) {
                    return 0
                }

                switch (currentItem.Flexbox.alignContent) {
                case Flexbox.AlignAuto:
                    return 0
                case Flexbox.AlignFlexStart:
                    return 1
                case Flexbox.AlignCenter:
                    return 2
                case Flexbox.AlignFlexEnd:
                    return 3
                case Flexbox.AlignStretch:
                    return 4
                case Flexbox.AlignBaseline:
                    return 5
                case Flexbox.AlignSpaceBetween:
                    return 6
                case Flexbox.AlignSpaceAround:
                    return 7
                }

                return 0
            }

            onCurrentIndexChanged: {
                if (currentItem) {
                    switch (currentIndex) {
                    case 0:
                        currentItem.Flexbox.alignContent = Flexbox.AlignAuto
                        break
                    case 1:
                        currentItem.Flexbox.alignContent = Flexbox.AlignFlexStart
                        break
                    case 2:
                        currentItem.Flexbox.alignContent = Flexbox.AlignCenter
                        break
                    case 3:
                        currentItem.Flexbox.alignContent = Flexbox.AlignFlexEnd
                        break
                    case 4:
                        currentItem.Flexbox.alignContent = Flexbox.AlignStretch
                        break
                    case 5:
                        currentItem.Flexbox.alignContent = Flexbox.AlignBaseline
                        break
                    case 6:
                        currentItem.Flexbox.alignContent = Flexbox.AlignSpaceBetween
                        break
                    case 7:
                        currentItem.Flexbox.alignContent = Flexbox.AlignSpaceAround
                        break
                    }
                }
            }
        }
    }
}
