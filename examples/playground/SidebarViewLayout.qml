import QtQuick
import QtQuick.Controls

import CxFlex

ScrollView {
    id: scrollView

    CxFlexColumn {
        width: scrollView.width - 15

        padding: 15

        SidebarLabel {
            text: "WIDTH x HEIGHT"
        }

        CxFlexRow {
            columnGap: 15

            SidebarTextField {
                CxFlexible.flexGrow: 1

                placeholderText: "auto"
                text: {
                    if (currentItem == null) {
                        return ""
                    }

                    if (currentItem.preferredWidth === "auto") {
                        return ""
                    }

                    return currentItem.preferredWidth
                }

                onTextChanged: {
                    if (currentItem) {
                        if (text === "") {
                            currentItem.preferredWidth = undefined
                        } else {
                            currentItem.preferredWidth = text
                        }
                    }
                }
            }

            SidebarTextField {
                CxFlexible.flexGrow: 1

                placeholderText: "auto"
                text: {
                    if (currentItem == null) {
                        return ""
                    }

                    if (currentItem.preferredHeight === "auto") {
                        return ""
                    }

                    return currentItem.preferredHeight
                }

                onTextChanged: {
                    if (currentItem) {
                        if (text === "") {
                            currentItem.preferredHeight = undefined
                        } else {
                            currentItem.preferredHeight = text
                        }
                    }
                }
            }
        }

        SidebarLabel {
            text: "MAX-WIDTH x MAX-HEIGHT"
        }

        CxFlexRow {
            columnGap: 15

            SidebarTextField {
                CxFlexible.flexGrow: 1

                placeholderText: "none"
                text: {
                    if (currentItem == null) {
                        return ""
                    }

                    if (currentItem.maximumWidth === undefined) {
                        return ""
                    }

                    return currentItem.maximumWidth
                }

                onTextChanged: {
                    if (currentItem) {
                        if (text === "") {
                            currentItem.maximumWidth = undefined
                        } else {
                            currentItem.maximumWidth = text
                        }
                    }
                }
            }

            SidebarTextField {
                CxFlexible.flexGrow: 1

                placeholderText: "none"
                text: {
                    if (currentItem == null) {
                        return ""
                    }

                    if (currentItem.maxHeight === undefined) {
                        return ""
                    }

                    return currentItem.maxHeight
                }

                onTextChanged: {
                    if (currentItem) {
                        if (text === "") {
                            currentItem.maxHeight = undefined
                        } else {
                            currentItem.maxHeight = text
                        }
                    }
                }
            }
        }

        SidebarLabel {
            text: "MIN-WIDTH x MIN-HEIGHT"
        }

        CxFlexRow {
            columnGap: 15

            SidebarTextField {
                CxFlexible.flexGrow: 1

                placeholderText: "0"
                text: {
                    if (currentItem == null) {
                        return ""
                    }

                    if (currentItem.minimumWidth === undefined) {
                        return ""
                    }

                    return currentItem.minimumWidth
                }

                onTextChanged: {
                    if (currentItem) {
                        if (text === "") {
                            currentItem.minimumWidth = undefined
                        } else {
                            currentItem.minimumWidth = text
                        }
                    }
                }
            }

            SidebarTextField {
                CxFlexible.flexGrow: 1

                placeholderText: "0"
                text: {
                    if (currentItem == null) {
                        return ""
                    }

                    if (currentItem.minHeight === undefined) {
                        return ""
                    }

                    return currentItem.minHeight
                }

                onTextChanged: {
                    if (currentItem) {
                        if (text === "") {
                            currentItem.minHeight = undefined
                        } else {
                            currentItem.minHeight = text
                        }
                    }
                }
            }
        }

        SidebarLabel {
            text: "ASPECT RATIO"
        }

        SidebarTextField {
            placeholderText: "auto"
            onTextChanged: {
                if (currentItem) {
                    if (text === "") {
                        currentItem.aspectRatio = undefined
                    } else {
                        currentItem.aspectRatio = text
                    }
                }
            }
        }

        CxFlexRow {
            columnGap: 10

            marginTop: 20

            justifyContent: CxFlex.JustifyCenter

            CxFlexColumn {
                justifyContent: CxFlex.JustifyCenter

                SidebarTextField {
                    CxFlexible.preferredWidth: 55
                    center: true
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.leftPadding = undefined
                            } else {
                                currentItem.leftPadding = text
                            }
                        }
                    }
                }
            }

            CxFlexColumn {
                justifyContent: CxFlex.JustifyCenter

                SidebarTextField {
                    CxFlexible.preferredWidth: 55
                    center: true
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.topPadding = undefined
                            } else {
                                currentItem.topPadding = text
                            }
                        }
                    }
                }
                SidebarCenter {
                    text: "PADDING"
                }
                SidebarTextField {
                    CxFlexible.preferredWidth: 55
                    center: true
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.bottomPadding = undefined
                            } else {
                                currentItem.bottomPadding = text
                            }
                        }
                    }
                }
            }

            CxFlexColumn {
                justifyContent: CxFlex.JustifyCenter

                SidebarTextField {
                    CxFlexible.preferredWidth: 55
                    center: true
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.rightPadding = undefined
                            } else {
                                currentItem.rightPadding = text
                            }
                        }
                    }
                }
            }
        }

        CxFlexRow {
            columnGap: 10

            marginTop: 20

            justifyContent: CxFlex.JustifyCenter

            CxFlexColumn {
                justifyContent: CxFlex.JustifyCenter

                SidebarTextField {
                    CxFlexible.preferredWidth: 55
                    center: true
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.leftBorder = undefined
                            } else {
                                currentItem.leftBorder = text
                            }
                        }
                    }
                }
            }

            CxFlexColumn {
                justifyContent: CxFlex.JustifyCenter
                alignItems: CxFlex.AlignCenter

                SidebarTextField {
                    CxFlexible.preferredWidth: 55
                    center: true
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.topBorder = undefined
                            } else {
                                currentItem.topBorder = text
                            }
                        }
                    }
                }
                SidebarCenter {
                    text: "BORDER"
                }
                SidebarTextField {
                    CxFlexible.preferredWidth: 55
                    center: true
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.bottomBorder = undefined
                            } else {
                                currentItem.bottomBorder = text
                            }
                        }
                    }
                }
            }

            CxFlexColumn {
                justifyContent: CxFlex.JustifyCenter

                SidebarTextField {
                    CxFlexible.preferredWidth: 55
                    center: true
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.rightBorder = undefined
                            } else {
                                currentItem.rightBorder = text
                            }
                        }
                    }
                }
            }
        }

        CxFlexRow {
            columnGap: 10

            marginTop: 20

            justifyContent: CxFlex.JustifyCenter

            CxFlexColumn {
                justifyContent: CxFlex.JustifyCenter

                SidebarTextField {
                    enabled: currentItem && currentItem != rootItem
                    CxFlexible.preferredWidth: 55
                    center: true
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.leftMargin = undefined
                            } else {
                                currentItem.leftMargin = text
                            }
                        }
                    }
                }
            }

            CxFlexColumn {
                justifyContent: CxFlex.JustifyCenter

                SidebarTextField {
                    enabled: currentItem && currentItem != rootItem
                    CxFlexible.preferredWidth: 55
                    center: true
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.topMargin = undefined
                            } else {
                                currentItem.topMargin = text
                            }
                        }
                    }
                }
                SidebarCenter {
                    text: "MARGIN"
                }
                SidebarTextField {
                    enabled: currentItem && currentItem != rootItem
                    CxFlexible.preferredWidth: 55
                    center: true
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.bottomMargin = undefined
                            } else {
                                currentItem.bottomMargin = text
                            }
                        }
                    }
                }
            }

            CxFlexColumn {
                justifyContent: CxFlex.JustifyCenter

                SidebarTextField {
                    enabled: currentItem && currentItem != rootItem
                    CxFlexible.preferredWidth: 55
                    center: true
                    onTextChanged: {
                        if (currentItem) {
                            if (text === "") {
                                currentItem.rightMargin = undefined
                            } else {
                                currentItem.rightMargin = text
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

        CxFlexRow {
            id: displayRow

            SidebarRadioButton {
                radiusPosition: -1

                enabled: currentItem && currentItem != rootItem

                text: "flex"
                checked: currentItem && currentItem.visible
                onClicked: {
                    if (currentItem) {
                        currentItem.visible = true
                    }
                }
            }

            SidebarRadioButton {
                radiusPosition: 1

                CxFlexible.marginLeft: -1

                enabled: currentItem && currentItem != rootItem

                text: "none"
                checked: currentItem && !currentItem.visible
                onClicked: {
                    if (currentItem) {
                        currentItem.visible = false
                    }
                }
            }
        }
    }
}
