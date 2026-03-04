import QtQuick
import QtQuick.Controls

import Flexbox

ScrollView {
    id: scrollView

    ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

    Item {
        Flexbox.flexDirection: Flexbox.Column

        Flexbox.padding: 15

        width: scrollView.width - 15

        SidebarLabel {
            text: "WIDTH x HEIGHT"
        }

        Item {
            Flexbox.flexDirection: Flexbox.Row
            Flexbox.columnGap: 15

            SidebarTextField {
                Flexbox.flexGrow: 1

                placeholderText: "auto"
                text: {
                    if (currentItem == null) {
                        return ""
                    }

                    if (currentItem.Flexbox.width === "auto") {
                        return "auto"
                    }
                    if (currentItem.Flexbox.width === undefined) {
                        return ""
                    }

                    return currentItem.Flexbox.width
                }

                onTextChanged: {
                    if (currentItem) {
                        if (text === "") {
                            currentItem.Flexbox.width = undefined
                        } else if (text === "auto") {
                            currentItem.Flexbox.width = "auto"
                        } else {
                            currentItem.Flexbox.width = text
                        }
                    }
                }
            }

            SidebarTextField {
                Flexbox.flexGrow: 1

                placeholderText: "auto"
                text: {
                    if (currentItem == null) {
                        return ""
                    }

                    if (currentItem.Flexbox.height === "auto") {
                        return "auto"
                    }
                    if (currentItem.Flexbox.height === undefined) {
                        return ""
                    }

                    return currentItem.Flexbox.height
                }

                onTextChanged: {
                    if (currentItem) {
                        if (text === "") {
                            currentItem.Flexbox.height = undefined
                        } else if (text === "auto") {
                            currentItem.Flexbox.height = "auto"
                        } else {
                            currentItem.Flexbox.height = text
                        }
                    }
                }
            }
        }

        SidebarLabel {
            text: "MAX-WIDTH x MAX-HEIGHT"
        }

        Item {
            Flexbox.flexDirection: Flexbox.Row
            Flexbox.columnGap: 15

            SidebarTextField {
                Flexbox.flexGrow: 1

                placeholderText: "undefined"
                text: {
                    if (currentItem == null) {
                        return ""
                    }

                    if (currentItem.Flexbox.maximumWidth === undefined) {
                        return ""
                    }

                    return currentItem.Flexbox.maximumWidth
                }

                onTextChanged: {
                    if (currentItem) {
                        if (text === "") {
                            currentItem.Flexbox.maximumWidth = undefined
                        } else {
                            currentItem.Flexbox.maximumWidth = text
                        }
                    }
                }
            }

            SidebarTextField {
                Flexbox.flexGrow: 1

                placeholderText: "undefined"
                text: {
                    if (currentItem == null) {
                        return ""
                    }

                    if (currentItem.Flexbox.maximumHeight === undefined) {
                        return ""
                    }

                    return currentItem.Flexbox.maximumHeight
                }

                onTextChanged: {
                    if (currentItem) {
                        if (text === "") {
                            currentItem.Flexbox.maximumHeight = undefined
                        } else {
                            currentItem.Flexbox.maximumHeight = text
                        }
                    }
                }
            }
        }

        SidebarLabel {
            text: "MIN-WIDTH x MIN-HEIGHT"
        }

        Item {
            Flexbox.flexDirection: Flexbox.Row
            Flexbox.columnGap: 15

            SidebarTextField {
                Flexbox.flexGrow: 1

                placeholderText: "undefined"
                text: {
                    if (currentItem == null) {
                        return ""
                    }

                    if (currentItem.Flexbox.minimumWidth === undefined) {
                        return ""
                    }

                    return currentItem.Flexbox.minimumWidth
                }

                onTextChanged: {
                    if (currentItem) {
                        if (text === "") {
                            currentItem.Flexbox.minimumWidth = undefined
                        } else {
                            currentItem.Flexbox.minimumWidth = text
                        }
                    }
                }
            }

            SidebarTextField {
                Flexbox.flexGrow: 1

                placeholderText: "undefined"
                text: {
                    if (currentItem == null) {
                        return ""
                    }

                    if (currentItem.Flexbox.minimumHeight === undefined) {
                        return ""
                    }

                    return currentItem.Flexbox.minimumHeight
                }

                onTextChanged: {
                    if (currentItem) {
                        if (text === "") {
                            currentItem.Flexbox.minimumHeight = undefined
                        } else {
                            currentItem.Flexbox.minimumHeight = text
                        }
                    }
                }
            }
        }

        SidebarLabel {
            text: "ASPECT RATIO"
        }

        SidebarTextField {
            placeholderText: "undefined"
            onTextChanged: {
                if (currentItem) {
                    if (text === "") {
                        currentItem.Flexbox.aspectRatio = undefined
                    } else {
                        currentItem.Flexbox.aspectRatio = text
                    }
                }
            }
        }

        Item {
            Flexbox.flexDirection: Flexbox.Row
            Flexbox.columnGap: 15

            Flexbox.topMargin: 20

            Flexbox.justifyContent: Flexbox.Center

            Item {
                Flexbox.flexDirection: Flexbox.Column

                Flexbox.justifyContent: Flexbox.Center

                SidebarTextField {
                    Flexbox.width: 55
                    center: true
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.Flexbox.leftPadding = undefined
                            } else {
                                currentItem.Flexbox.leftPadding = text
                            }
                        }
                    }
                }
            }

            Item {
                Flexbox.flexDirection: Flexbox.Column

                Flexbox.justifyContent: Flexbox.Center

                SidebarTextField {
                    Flexbox.width: 55
                    center: true
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.Flexbox.topPadding = undefined
                            } else {
                                currentItem.Flexbox.topPadding = text
                            }
                        }
                    }
                }
                SidebarCenter {
                    text: "PADDING"
                }
                SidebarTextField {
                    Flexbox.width: 55
                    center: true
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.Flexbox.bottomPadding = undefined
                            } else {
                                currentItem.Flexbox.bottomPadding = text
                            }
                        }
                    }
                }
            }

            Item {
                Flexbox.flexDirection: Flexbox.Column

                Flexbox.justifyContent: Flexbox.Center

                SidebarTextField {
                    Flexbox.width: 55
                    center: true
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.Flexbox.rightPadding = undefined
                            } else {
                                currentItem.Flexbox.rightPadding = text
                            }
                        }
                    }
                }
            }
        }

        Item {
            Flexbox.flexDirection: Flexbox.Row
            Flexbox.columnGap: 15

            Flexbox.topMargin: 20

            Flexbox.justifyContent: Flexbox.Center

            Item {
                Flexbox.flexDirection: Flexbox.Column

                Flexbox.justifyContent: Flexbox.Center

                SidebarTextField {
                    Flexbox.width: 55
                    center: true
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.Flexbox.leftBorder = undefined
                            } else {
                                currentItem.Flexbox.leftBorder = text
                            }
                        }
                    }
                }
            }

            Item {
                Flexbox.flexDirection: Flexbox.Column

                Flexbox.justifyContent: Flexbox.Center
                Flexbox.alignItems: Flexbox.Center

                SidebarTextField {
                    Flexbox.width: 55
                    center: true
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.Flexbox.topBorder = undefined
                            } else {
                                currentItem.Flexbox.topBorder = text
                            }
                        }
                    }
                }
                SidebarCenter {
                    text: "BORDER"
                }
                SidebarTextField {
                    Flexbox.width: 55
                    center: true
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.Flexbox.bottomBorder = undefined
                            } else {
                                currentItem.Flexbox.bottomBorder = text
                            }
                        }
                    }
                }
            }

            Item {
                Flexbox.flexDirection: Flexbox.Column

                Flexbox.justifyContent: Flexbox.Center

                SidebarTextField {
                    Flexbox.width: 55
                    center: true
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.Flexbox.rightBorder = undefined
                            } else {
                                currentItem.Flexbox.rightBorder = text
                            }
                        }
                    }
                }
            }
        }

        Item {
            Flexbox.flexDirection: Flexbox.Row
            Flexbox.columnGap: 15

            Flexbox.topMargin: 20

            Flexbox.justifyContent: Flexbox.Center

            Item {
                Flexbox.flexDirection: Flexbox.Column

                Flexbox.justifyContent: Flexbox.Center

                SidebarTextField {
                    enabled: currentItem && currentItem != rootItem
                    Flexbox.width: 55
                    center: true
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.Flexbox.leftMargin = undefined
                            } else {
                                currentItem.Flexbox.leftMargin = text
                            }
                        }
                    }
                }
            }

            Item {
                Flexbox.flexDirection: Flexbox.Column

                Flexbox.justifyContent: Flexbox.Center

                SidebarTextField {
                    enabled: currentItem && currentItem != rootItem
                    Flexbox.width: 55
                    center: true
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.Flexbox.topMargin = undefined
                            } else {
                                currentItem.Flexbox.topMargin = text
                            }
                        }
                    }
                }
                SidebarCenter {
                    text: "MARGIN"
                }
                SidebarTextField {
                    enabled: currentItem && currentItem != rootItem
                    Flexbox.width: 55
                    center: true
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.Flexbox.bottomMargin = undefined
                            } else {
                                currentItem.Flexbox.bottomMargin = text
                            }
                        }
                    }
                }
            }

            Item {
                Flexbox.flexDirection: Flexbox.Column

                Flexbox.justifyContent: Flexbox.Center

                SidebarTextField {
                    enabled: currentItem && currentItem != rootItem
                    Flexbox.width: 55
                    center: true
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.Flexbox.rightMargin = undefined
                            } else {
                                currentItem.Flexbox.rightMargin = text
                            }
                        }
                    }
                }
            }
        }

        SidebarLabel {
            text: "DISPLAY"
        }

        ButtonGroup {
            id: displayButtonGroup
            buttons: displayRow.children
        }

        Item {
            id: displayRow

            Flexbox.flexDirection: Flexbox.Row

            SidebarRadioButton {
                radiusPosition: -1

                enabled: currentItem && currentItem != rootItem

                text: "flex"
                checked: currentItem && currentItem.Flexbox.display === Flexbox.Flex
                onClicked: {
                    if (currentItem) {
                        currentItem.Flexbox.display = Flexbox.Flex
                    }
                }
            }

            SidebarRadioButton {
                radiusPosition: 1

                Flexbox.leftMargin: -1

                enabled: currentItem && currentItem != rootItem

                text: "none"
                checked: currentItem && currentItem.Flexbox.display === Flexbox.None
                onClicked: {
                    if (currentItem) {
                        currentItem.Flexbox.display = Flexbox.None
                    }
                }
            }

            SidebarRadioButton {
                radiusPosition: 1

                Flexbox.leftMargin: -1

                enabled: currentItem && currentItem != rootItem

                text: "contents"
                checked: currentItem && currentItem.Flexbox.display === Flexbox.Contents
                onClicked: {
                    if (currentItem) {
                        currentItem.Flexbox.display = Flexbox.Contents
                    }
                }
            }
        }
    }
}
