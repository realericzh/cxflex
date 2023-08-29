import QtQuick
import QtQuick.Controls

import CxFlex

ScrollView {
    id: scrollView

    CxFlexColumn {
        width: scrollView.width - 15

        padding: 15

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

                switch (currentItem.justifyContent) {
                case CxFlex.JustifyFlexStart:
                    return 0
                case CxFlex.JustifyCenter:
                    return 1
                case CxFlex.JustifyFlexEnd:
                    return 2
                case CxFlex.JustifySpaceBetween:
                    return 3
                case CxFlex.JustifySpaceAround:
                    return 4
                case CxFlex.JustifySpaceEvenly:
                    return 5
                }

                return 0
            }

            onCurrentIndexChanged: {
                if (currentItem) {
                    switch (currentIndex) {
                    case 0:
                        currentItem.justifyContent = CxFlex.JustifyFlexStart
                        break
                    case 1:
                        currentItem.justifyContent = CxFlex.JustifyCenter
                        break
                    case 2:
                        currentItem.justifyContent = CxFlex.JustifyFlexEnd
                        break
                    case 3:
                        currentItem.justifyContent = CxFlex.JustifySpaceBetween
                        break
                    case 4:
                        currentItem.justifyContent = CxFlex.JustifySpaceAround
                        break
                    case 5:
                        currentItem.justifyContent = CxFlex.JustifySpaceEvenly
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

                switch (currentItem.alignItems) {
                case CxFlex.AlignAuto:
                    return 0
                case CxFlex.AlignFlexStart:
                    return 1
                case CxFlex.AlignCenter:
                    return 2
                case CxFlex.AlignFlexEnd:
                    return 3
                case CxFlex.AlignStretch:
                    return 4
                case CxFlex.AlignBaseline:
                    return 5
                case CxFlex.AlignSpaceBetween:
                    return 6
                case CxFlex.AlignSpaceAround:
                    return 7
                }

                return 0
            }

            onCurrentIndexChanged: {
                if (currentItem) {
                    switch (currentIndex) {
                    case 0:
                        currentItem.alignItems = CxFlex.AlignAuto
                        break
                    case 1:
                        currentItem.alignItems = CxFlex.AlignFlexStart
                        break
                    case 2:
                        currentItem.alignItems = CxFlex.AlignCenter
                        break
                    case 3:
                        currentItem.alignItems = CxFlex.AlignFlexEnd
                        break
                    case 4:
                        currentItem.alignItems = CxFlex.AlignStretch
                        break
                    case 5:
                        currentItem.alignItems = CxFlex.AlignBaseline
                        break
                    case 6:
                        currentItem.alignItems = CxFlex.AlignSpaceBetween
                        break
                    case 7:
                        currentItem.alignItems = CxFlex.AlignSpaceAround
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

                switch (currentItem.alignSelf) {
                case CxFlex.AlignAuto:
                    return 0
                case CxFlex.AlignFlexStart:
                    return 1
                case CxFlex.AlignCenter:
                    return 2
                case CxFlex.AlignFlexEnd:
                    return 3
                case CxFlex.AlignStretch:
                    return 4
                case CxFlex.AlignBaseline:
                    return 5
                case CxFlex.AlignSpaceBetween:
                    return 6
                case CxFlex.AlignSpaceAround:
                    return 7
                }

                return 0
            }

            onCurrentIndexChanged: {
                if (currentItem) {
                    switch (currentIndex) {
                    case 0:
                        currentItem.alignSelf = CxFlex.AlignAuto
                        break
                    case 1:
                        currentItem.alignSelf = CxFlex.AlignFlexStart
                        break
                    case 2:
                        currentItem.alignSelf = CxFlex.AlignCenter
                        break
                    case 3:
                        currentItem.alignSelf = CxFlex.AlignFlexEnd
                        break
                    case 4:
                        currentItem.alignSelf = CxFlex.AlignStretch
                        break
                    case 5:
                        currentItem.alignSelf = CxFlex.AlignBaseline
                        break
                    case 6:
                        currentItem.alignSelf = CxFlex.AlignSpaceBetween
                        break
                    case 7:
                        currentItem.alignSelf = CxFlex.AlignSpaceAround
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

                switch (currentItem.alignContent) {
                case CxFlex.AlignAuto:
                    return 0
                case CxFlex.AlignFlexStart:
                    return 1
                case CxFlex.AlignCenter:
                    return 2
                case CxFlex.AlignFlexEnd:
                    return 3
                case CxFlex.AlignStretch:
                    return 4
                case CxFlex.AlignBaseline:
                    return 5
                case CxFlex.AlignSpaceBetween:
                    return 6
                case CxFlex.AlignSpaceAround:
                    return 7
                }

                return 0
            }

            onCurrentIndexChanged: {
                if (currentItem) {
                    switch (currentIndex) {
                    case 0:
                        currentItem.alignContent = CxFlex.AlignAuto
                        break
                    case 1:
                        currentItem.alignContent = CxFlex.AlignFlexStart
                        break
                    case 2:
                        currentItem.alignContent = CxFlex.AlignCenter
                        break
                    case 3:
                        currentItem.alignContent = CxFlex.AlignFlexEnd
                        break
                    case 4:
                        currentItem.alignContent = CxFlex.AlignStretch
                        break
                    case 5:
                        currentItem.alignContent = CxFlex.AlignBaseline
                        break
                    case 6:
                        currentItem.alignContent = CxFlex.AlignSpaceBetween
                        break
                    case 7:
                        currentItem.alignContent = CxFlex.AlignSpaceAround
                        break
                    }
                }
            }
        }
    }
}
