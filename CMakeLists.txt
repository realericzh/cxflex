cmake_minimum_required(VERSION 3.16)

project(Flexbox VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

file(GLOB_RECURSE YOGA_SOURCES "yoga/*.cpp")

qt_add_executable(Flexbox
    main.cpp

    ${YOGA_SOURCES}

    # Flexbox Core Code -->
    Flexbox/Flexbox.h
    Flexbox/Flexbox_p.h
    Flexbox/Flexbox.cpp
    # <-- Flexbox Core Code

    SyntaxHighlighter.h
    SyntaxHighlighter_p.h
    SyntaxHighlighter.cpp
)

target_include_directories(Flexbox PRIVATE ${Qt6Quick_PRIVATE_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/Flexbox)

qt_add_qml_module(Flexbox
    URI Flexbox
    QML_FILES
        Main.qml
        SwipeButton.qml
        PickableItem.qml
        Sidebar.qml
        SidebarButton.qml
        SidebarCenter.qml
        SidebarComboBox.qml
        SidebarLabel.qml
        SidebarRadioButton.qml
        SidebarTextField.qml
        SidebarViewAlignment.qml
        SidebarViewFlex.qml
        SidebarViewLayout.qml
        Playground.qml
        TestBox0.qml
        TestBox1.qml
        SourceCodeViewer.qml
        Styling/AlignContentView.qml
        Styling/AlignContentCode.qml
        Styling/AlignItemsView.qml
        Styling/AlignItemsCode.qml
        Styling/AspectRatioView.qml
        Styling/AspectRatioCode.qml
        Styling/DisplayView.qml
        Styling/DisplayCode.qml
        Styling/FlexBasisGrowShrinkView.qml
        Styling/FlexBasisGrowShrinkCode1.qml
        Styling/FlexBasisGrowShrinkCode2.qml
        Styling/FlexBasisGrowShrinkCode3.qml
        Styling/FlexDirectionView.qml
        Styling/FlexDirectionCode.qml
        Styling/FlexWrapView.qml
        Styling/FlexWrapCode.qml
        Styling/GapView.qml
        Styling/GapCode.qml
        Styling/InsetsView.qml
        Styling/InsetsCode.qml
        Styling/JustifyContentView.qml
        Styling/JustifyContentCode.qml
        Styling/LayoutDirectionView.qml
        Styling/LayoutDirectionCode.qml
        Styling/MarginPaddingBorderView.qml
        Styling/MarginPaddingBorderCode.qml
        Styling/PositionView.qml
        Styling/PositionCode.qml
        Styling/MinMaxWidthHeightView.qml
        Styling/MinMaxWidthHeightCode.qml
        Styling/WidthHeightView.qml
        Styling/WidthHeightCode.qml

    RESOURCES fonts/FiraCode-Regular.ttf
)

target_link_libraries(Flexbox PRIVATE Qt6::Quick)
