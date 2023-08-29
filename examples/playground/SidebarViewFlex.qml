import QtQuick
import QtQuick.Controls

import CxFlex

ScrollView {
    id: scrollView

    CxFlexColumn {
        width: scrollView.width - 15

        padding: 15

        SidebarLabel {
            text: "DIRECTION"
        }

        ButtonGroup {
            id: directionButtonGroup
            buttons: directionRow.children
        }

        CxFlexRow {
            id: directionRow

            SidebarRadioButton {
                radiusPosition: -1

                text: "inherit"
                checked: currentItem && currentItem.direction === CxFlex.DirectionInherit
                onClicked: {
                    if (currentItem) {
                        currentItem.direction = CxFlex.DirectionInherit
                    }
                }
            }

            SidebarRadioButton {
                radiusPosition: 0

                text: "ltr"
                checked: currentItem && currentItem.direction === CxFlex.DirectionLTR
                onClicked: {
                    if (currentItem) {
                        currentItem.direction = CxFlex.DirectionLTR
                    }
                }
            }

            SidebarRadioButton {
                radiusPosition: 1

                text: "rtl"
                checked: currentItem && currentItem.direction === CxFlex.DirectionRTL
                onClicked: {
                    if (currentItem) {
                        currentItem.direction = CxFlex.DirectionRTL
                    }
                }
            }
        }

        SidebarLabel {
            text: "FLEX DIRECTION"
        }

        SidebarComboBox {
            model: ListModel {
                ListElement { elementText: "column" }
                ListElement { elementText: "column reverse" }
                ListElement { elementText: "row" }
                ListElement { elementText: "row reverse" }
            }

            currentIndex: {
                if (currentItem == null) {
                    return 0
                }

                switch (currentItem.flexDirection) {
                case CxFlex.FlexDirectionColumn:
                    return 0
                case CxFlex.FlexDirectionColumnReverse:
                    return 1
                case CxFlex.FlexDirectionRow:
                    return 2
                case CxFlex.FlexDirectionRowReverse:
                    return 3
                }

                return 0
            }

            onCurrentIndexChanged: {
                if (currentItem) {
                    switch (currentIndex) {
                    case 0:
                        currentItem.flexDirection = CxFlex.FlexDirectionColumn
                        break
                    case 1:
                        currentItem.flexDirection = CxFlex.FlexDirectionColumnReverse
                        break
                    case 2:
                        currentItem.flexDirection = CxFlex.FlexDirectionRow
                        break
                    case 3:
                        currentItem.flexDirection = CxFlex.FlexDirectionRowReverse
                        break
                    }
                }
            }
        }

        CxFlexRow {
            gap: 15

            CxFlexColumn {
                flexGrow: 1

                SidebarLabel {
                    text: "BASIS"
                }

                SidebarTextField {
                    enabled: currentItem && currentItem != rootItem
                    placeholderText: "auto"
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.flexBasis = undefined
                            } else {
                                currentItem.flexBasis = text
                            }
                        }
                    }
                }
            }

            CxFlexColumn {
                flexGrow: 1

                SidebarLabel {
                    text: "GROW"
                }

                SidebarTextField {
                    enabled: currentItem && currentItem != rootItem
                    placeholderText: "0"
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.flexGrow = undefined
                            } else {
                                currentItem.flexGrow = text
                            }
                        }
                    }
                }
            }

            CxFlexColumn {
                flexGrow: 1

                SidebarLabel {
                    text: "SHRINK"
                }

                SidebarTextField {
                    enabled: currentItem && currentItem != rootItem
                    placeholderText: "1"
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.flexShrink = undefined
                            } else {
                                currentItem.flexShrink = text
                            }
                        }
                    }
                }
            }
        }

        SidebarLabel {
            text: "FLEX WRAP"
        }

        ButtonGroup {
            id: wrapButtonGroup
            buttons: flexWrapRow.children
        }

        CxFlexRow {
            id: flexWrapRow

            SidebarRadioButton {
                radiusPosition: -1

                text: "no wrap"
                checked: currentItem && currentItem.flexWrap === CxFlex.WrapNoWrap
                onClicked: {
                    if (currentItem) {
                        currentItem.flexWrap = CxFlex.WrapNoWrap
                    }
                }
            }

            SidebarRadioButton {
                radiusPosition: 0

                text: "wrap"
                checked: currentItem && currentItem.flexWrap === CxFlex.WrapWrap
                onClicked: {
                    if (currentItem) {
                        currentItem.flexWrap = CxFlex.WrapWrap
                    }
                }
            }

            SidebarRadioButton {
                radiusPosition: 1

                text: "wrap reverse"
                checked: currentItem && currentItem.flexWrap === CxFlex.WrapWrapReverse
                onClicked: {
                    if (currentItem) {
                        currentItem.flexWrap = CxFlex.WrapWrapReverse
                    }
                }
            }
        }

        CxFlexRow {
            gap: 15

            CxFlexColumn {
                flexGrow: 1

                SidebarLabel {
                    text: "GAP"
                }

                SidebarTextField {
                    placeholderText: "0"
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.gap = undefined
                            } else {
                                currentItem.gap = text
                            }
                        }
                    }
                }
            }

            CxFlexColumn {
                flexGrow: 1

                SidebarLabel {
                    text: "ROW-GAP"
                }

                SidebarTextField {
                    placeholderText: "0"
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.rowGap = undefined
                            } else {
                                currentItem.rowGap = text
                            }
                        }
                    }
                }
            }

            CxFlexColumn {
                flexGrow: 1

                SidebarLabel {
                    text: "COLUMN-GAP"
                }

                SidebarTextField {
                    placeholderText: "0"
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.columnGap = undefined
                            } else {
                                currentItem.columnGap = text
                            }
                        }
                    }
                }
            }
        }
    }
}
