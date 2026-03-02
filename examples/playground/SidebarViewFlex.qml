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
            text: "DIRECTION"
        }

        ButtonGroup {
            id: directionButtonGroup
            buttons: directionRow.children
        }

        Item {
            id: directionRow

            Flexbox.flexDirection: Flexbox.FlexDirectionRow

            SidebarRadioButton {
                radiusPosition: -1

                text: "inherit"
                checked: currentItem && currentItem.Flexbox.direction === Flexbox.DirectionInherit
                onClicked: {
                    if (currentItem) {
                        currentItem.Flexbox.direction = Flexbox.DirectionInherit
                    }
                }
            }

            SidebarRadioButton {
                radiusPosition: 0

                text: "ltr"
                checked: currentItem && currentItem.Flexbox.direction === Flexbox.DirectionLTR
                onClicked: {
                    if (currentItem) {
                        currentItem.Flexbox.direction = Flexbox.DirectionLTR
                    }
                }
            }

            SidebarRadioButton {
                radiusPosition: 1

                text: "rtl"
                checked: currentItem && currentItem.Flexbox.direction === Flexbox.DirectionRTL
                onClicked: {
                    if (currentItem) {
                        currentItem.Flexbox.direction = Flexbox.DirectionRTL
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

                switch (currentItem.Flexbox.flexDirection) {
                case Flexbox.FlexDirectionColumn:
                    return 0
                case Flexbox.FlexDirectionColumnReverse:
                    return 1
                case Flexbox.FlexDirectionRow:
                    return 2
                case Flexbox.FlexDirectionRowReverse:
                    return 3
                }

                return 0
            }

            onCurrentIndexChanged: {
                if (currentItem) {
                    switch (currentIndex) {
                    case 0:
                        currentItem.Flexbox.flexDirection = Flexbox.FlexDirectionColumn
                        break
                    case 1:
                        currentItem.Flexbox.flexDirection = Flexbox.FlexDirectionColumnReverse
                        break
                    case 2:
                        currentItem.Flexbox.flexDirection = Flexbox.FlexDirectionRow
                        break
                    case 3:
                        currentItem.Flexbox.flexDirection = Flexbox.FlexDirectionRowReverse
                        break
                    }
                }
            }
        }

        Item {
            Flexbox.flexDirection: Flexbox.FlexDirectionRow
            Flexbox.gap: 15

            Item {
                Flexbox.flexDirection: Flexbox.FlexDirectionColumn
                Flexbox.flexGrow: 1

                SidebarLabel {
                    text: "BASIS"
                }

                SidebarTextField {
                    enabled: currentItem && currentItem != rootItem
                    placeholderText: "auto"
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.Flexbox.flexBasis = undefined
                            } else {
                                currentItem.Flexbox.flexBasis = text
                            }
                        }
                    }
                }
            }

            Item {
                Flexbox.flexDirection: Flexbox.FlexDirectionColumn
                Flexbox.flexGrow: 1

                SidebarLabel {
                    text: "GROW"
                }

                SidebarTextField {
                    enabled: currentItem && currentItem != rootItem
                    placeholderText: "0"
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.Flexbox.flexGrow = undefined
                            } else {
                                currentItem.Flexbox.flexGrow = text
                            }
                        }
                    }
                }
            }

            Item {
                Flexbox.flexDirection: Flexbox.FlexDirectionColumn
                Flexbox.flexGrow: 1

                SidebarLabel {
                    text: "SHRINK"
                }

                SidebarTextField {
                    enabled: currentItem && currentItem != rootItem
                    placeholderText: "1"
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.Flexbox.flexShrink = undefined
                            } else {
                                currentItem.Flexbox.flexShrink = text
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

        Item {
            id: flexWrapRow

            Flexbox.flexDirection: Flexbox.FlexDirectionRow

            SidebarRadioButton {
                radiusPosition: -1

                text: "no wrap"
                checked: currentItem && currentItem.Flexbox.flexWrap === Flexbox.WrapNoWrap
                onClicked: {
                    if (currentItem) {
                        currentItem.Flexbox.flexWrap = Flexbox.WrapNoWrap
                    }
                }
            }

            SidebarRadioButton {
                radiusPosition: 0

                text: "wrap"
                checked: currentItem && currentItem.Flexbox.flexWrap === Flexbox.WrapWrap
                onClicked: {
                    if (currentItem) {
                        currentItem.Flexbox.flexWrap = Flexbox.WrapWrap
                    }
                }
            }

            SidebarRadioButton {
                radiusPosition: 1

                text: "wrap reverse"
                checked: currentItem && currentItem.Flexbox.flexWrap === Flexbox.WrapWrapReverse
                onClicked: {
                    if (currentItem) {
                        currentItem.Flexbox.flexWrap = Flexbox.WrapWrapReverse
                    }
                }
            }
        }

        Item {
            Flexbox.flexDirection: Flexbox.FlexDirectionRow
            Flexbox.gap: 15

            Item {
                Flexbox.flexDirection: Flexbox.FlexDirectionColumn
                Flexbox.flexGrow: 1

                SidebarLabel {
                    text: "GAP"
                }

                SidebarTextField {
                    placeholderText: "0"
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.Flexbox.gap = undefined
                            } else {
                                currentItem.Flexbox.gap = text
                            }
                        }
                    }
                }
            }

            Item {
                Flexbox.flexDirection: Flexbox.FlexDirectionColumn
                Flexbox.flexGrow: 1

                SidebarLabel {
                    text: "ROW-GAP"
                }

                SidebarTextField {
                    placeholderText: "0"
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.Flexbox.rowGap = undefined
                            } else {
                                currentItem.Flexbox.rowGap = text
                            }
                        }
                    }
                }
            }

            Item {
                Flexbox.flexDirection: Flexbox.FlexDirectionColumn
                Flexbox.flexGrow: 1

                SidebarLabel {
                    text: "COLUMN-GAP"
                }

                SidebarTextField {
                    placeholderText: "0"
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.Flexbox.columnGap = undefined
                            } else {
                                currentItem.Flexbox.columnGap = text
                            }
                        }
                    }
                }
            }
        }
    }
}
