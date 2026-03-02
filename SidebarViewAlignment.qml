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
                case Flexbox.FlexStart:
                    return 0
                case Flexbox.Center:
                    return 1
                case Flexbox.FlexEnd:
                    return 2
                case Flexbox.SpaceBetween:
                    return 3
                case Flexbox.SpaceAround:
                    return 4
                case Flexbox.SpaceEvenly:
                    return 5
                }

                return 0
            }

            onCurrentIndexChanged: {
                if (currentItem) {
                    switch (currentIndex) {
                    case 0:
                        currentItem.Flexbox.justifyContent = Flexbox.FlexStart
                        break
                    case 1:
                        currentItem.Flexbox.justifyContent = Flexbox.Center
                        break
                    case 2:
                        currentItem.Flexbox.justifyContent = Flexbox.FlexEnd
                        break
                    case 3:
                        currentItem.Flexbox.justifyContent = Flexbox.SpaceBetween
                        break
                    case 4:
                        currentItem.Flexbox.justifyContent = Flexbox.SpaceAround
                        break
                    case 5:
                        currentItem.Flexbox.justifyContent = Flexbox.SpaceEvenly
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
                case Flexbox.Auto:
                    return 0
                case Flexbox.FlexStart:
                    return 1
                case Flexbox.Center:
                    return 2
                case Flexbox.FlexEnd:
                    return 3
                case Flexbox.Stretch:
                    return 4
                case Flexbox.Baseline:
                    return 5
                case Flexbox.SpaceBetween:
                    return 6
                case Flexbox.SpaceAround:
                    return 7
                }

                return 0
            }

            onCurrentIndexChanged: {
                if (currentItem) {
                    switch (currentIndex) {
                    case 0:
                        currentItem.Flexbox.alignItems = Flexbox.Auto
                        break
                    case 1:
                        currentItem.Flexbox.alignItems = Flexbox.FlexStart
                        break
                    case 2:
                        currentItem.Flexbox.alignItems = Flexbox.Center
                        break
                    case 3:
                        currentItem.Flexbox.alignItems = Flexbox.FlexEnd
                        break
                    case 4:
                        currentItem.Flexbox.alignItems = Flexbox.Stretch
                        break
                    case 5:
                        currentItem.Flexbox.alignItems = Flexbox.Baseline
                        break
                    case 6:
                        currentItem.Flexbox.alignItems = Flexbox.SpaceBetween
                        break
                    case 7:
                        currentItem.Flexbox.alignItems = Flexbox.SpaceAround
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
                case Flexbox.Auto:
                    return 0
                case Flexbox.FlexStart:
                    return 1
                case Flexbox.Center:
                    return 2
                case Flexbox.FlexEnd:
                    return 3
                case Flexbox.Stretch:
                    return 4
                case Flexbox.Baseline:
                    return 5
                case Flexbox.SpaceBetween:
                    return 6
                case Flexbox.SpaceAround:
                    return 7
                }

                return 0
            }

            onCurrentIndexChanged: {
                if (currentItem) {
                    switch (currentIndex) {
                    case 0:
                        currentItem.Flexbox.alignSelf = Flexbox.Auto
                        break
                    case 1:
                        currentItem.Flexbox.alignSelf = Flexbox.FlexStart
                        break
                    case 2:
                        currentItem.Flexbox.alignSelf = Flexbox.Center
                        break
                    case 3:
                        currentItem.Flexbox.alignSelf = Flexbox.FlexEnd
                        break
                    case 4:
                        currentItem.Flexbox.alignSelf = Flexbox.Stretch
                        break
                    case 5:
                        currentItem.Flexbox.alignSelf = Flexbox.Baseline
                        break
                    case 6:
                        currentItem.Flexbox.alignSelf = Flexbox.SpaceBetween
                        break
                    case 7:
                        currentItem.Flexbox.alignSelf = Flexbox.SpaceAround
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
                case Flexbox.Auto:
                    return 0
                case Flexbox.FlexStart:
                    return 1
                case Flexbox.Center:
                    return 2
                case Flexbox.FlexEnd:
                    return 3
                case Flexbox.Stretch:
                    return 4
                case Flexbox.Baseline:
                    return 5
                case Flexbox.SpaceBetween:
                    return 6
                case Flexbox.SpaceAround:
                    return 7
                }

                return 0
            }

            onCurrentIndexChanged: {
                if (currentItem) {
                    switch (currentIndex) {
                    case 0:
                        currentItem.Flexbox.alignContent = Flexbox.Auto
                        break
                    case 1:
                        currentItem.Flexbox.alignContent = Flexbox.FlexStart
                        break
                    case 2:
                        currentItem.Flexbox.alignContent = Flexbox.Center
                        break
                    case 3:
                        currentItem.Flexbox.alignContent = Flexbox.FlexEnd
                        break
                    case 4:
                        currentItem.Flexbox.alignContent = Flexbox.Stretch
                        break
                    case 5:
                        currentItem.Flexbox.alignContent = Flexbox.Baseline
                        break
                    case 6:
                        currentItem.Flexbox.alignContent = Flexbox.SpaceBetween
                        break
                    case 7:
                        currentItem.Flexbox.alignContent = Flexbox.SpaceAround
                        break
                    }
                }
            }
        }
    }
}
