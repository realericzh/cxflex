import QtQuick
import QtQuick.Controls

import Flexbox

ScrollView {
    id: scrollView

    Item {
        Flexbox.flexDirection: Flexbox.Column

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

            Flexbox.flexDirection: Flexbox.Row

            SidebarRadioButton {
                radiusPosition: -1

                text: "inherit"
                checked: currentItem && currentItem.Flexbox.direction === Flexbox.Inherit
                onClicked: {
                    if (currentItem) {
                        currentItem.Flexbox.direction = Flexbox.Inherit
                    }
                }
            }

            SidebarRadioButton {
                radiusPosition: 0

                text: "ltr"
                checked: currentItem && currentItem.Flexbox.direction === Flexbox.LTR
                onClicked: {
                    if (currentItem) {
                        currentItem.Flexbox.direction = Flexbox.LTR
                    }
                }
            }

            SidebarRadioButton {
                radiusPosition: 1

                text: "rtl"
                checked: currentItem && currentItem.Flexbox.direction === Flexbox.RTL
                onClicked: {
                    if (currentItem) {
                        currentItem.Flexbox.direction = Flexbox.RTL
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
                case Flexbox.Column:
                    return 0
                case Flexbox.ColumnReverse:
                    return 1
                case Flexbox.Row:
                    return 2
                case Flexbox.RowReverse:
                    return 3
                }

                return 0
            }

            onCurrentIndexChanged: {
                if (currentItem) {
                    switch (currentIndex) {
                    case 0:
                        currentItem.Flexbox.flexDirection = Flexbox.Column
                        break
                    case 1:
                        currentItem.Flexbox.flexDirection = Flexbox.ColumnReverse
                        break
                    case 2:
                        currentItem.Flexbox.flexDirection = Flexbox.Row
                        break
                    case 3:
                        currentItem.Flexbox.flexDirection = Flexbox.RowReverse
                        break
                    }
                }
            }
        }

        Item {
            Flexbox.flexDirection: Flexbox.Row
            Flexbox.gap: 15

            Item {
                Flexbox.flexDirection: Flexbox.Column
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
                Flexbox.flexDirection: Flexbox.Column
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
                Flexbox.flexDirection: Flexbox.Column
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

            Flexbox.flexDirection: Flexbox.Row

            SidebarRadioButton {
                radiusPosition: -1

                text: "no wrap"
                checked: currentItem && currentItem.Flexbox.flexWrap === Flexbox.NoWrap
                onClicked: {
                    if (currentItem) {
                        currentItem.Flexbox.flexWrap = Flexbox.NoWrap
                    }
                }
            }

            SidebarRadioButton {
                radiusPosition: 0

                text: "wrap"
                checked: currentItem && currentItem.Flexbox.flexWrap === Flexbox.Wrap
                onClicked: {
                    if (currentItem) {
                        currentItem.Flexbox.flexWrap = Flexbox.Wrap
                    }
                }
            }

            SidebarRadioButton {
                radiusPosition: 1

                text: "wrap reverse"
                checked: currentItem && currentItem.Flexbox.flexWrap === Flexbox.WrapReverse
                onClicked: {
                    if (currentItem) {
                        currentItem.Flexbox.flexWrap = Flexbox.WrapReverse
                    }
                }
            }
        }

        Item {
            Flexbox.flexDirection: Flexbox.Row
            Flexbox.gap: 15

            Item {
                Flexbox.flexDirection: Flexbox.Column
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
                Flexbox.flexDirection: Flexbox.Column
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
                Flexbox.flexDirection: Flexbox.Column
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
