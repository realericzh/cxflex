cmake_minimum_required(VERSION 3.16)

project(Flexbox VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

file(GLOB_RECURSE YOGA_SOURCES "yoga/*.cpp")

qt_add_executable(Flexbox
    Main/main.cpp

    # Flexbox Core Code -->
    ${YOGA_SOURCES}

    Flexbox.h
    Flexbox_p.h
    Flexbox.cpp
    # <-- Flexbox Core Code

    Main/FlexboxApp.h
    Main/FlexboxApp_p.h
    Main/FlexboxApp.cpp
    Main/SyntaxHighlighter.h
    Main/SyntaxHighlighter_p.h
    Main/SyntaxHighlighter.cpp
)

target_include_directories(Flexbox PRIVATE ${Qt6Quick_PRIVATE_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/Main)

qt_add_qml_module(Flexbox
    URI Flexbox
    QML_FILES
        Main/Main.qml
        Main/TestBox0.qml
        Main/TestBox1.qml
        Main/PreviewBox.qml
        Main/TextViewer.qml
        Main/CodeViewer.qml
        Main/Playground/SwipeButton.qml
        Main/Playground/PickableItem.qml
        Main/Playground/Sidebar.qml
        Main/Playground/SidebarButton.qml
        Main/Playground/SidebarCenter.qml
        Main/Playground/SidebarComboBox.qml
        Main/Playground/SidebarLabel.qml
        Main/Playground/SidebarRadioButton.qml
        Main/Playground/SidebarTextField.qml
        Main/Playground/SidebarViewAlignment.qml
        Main/Playground/SidebarViewFlex.qml
        Main/Playground/SidebarViewLayout.qml
        Main/Playground/Playground.qml
        Main/Styling/AlignContentView.qml
        Main/Styling/AlignContentCode.qml
        Main/Styling/AlignItemsView.qml
        Main/Styling/AlignItemsCode.qml
        Main/Styling/AspectRatioView.qml
        Main/Styling/AspectRatioCode.qml
        Main/Styling/DisplayView.qml
        Main/Styling/DisplayCode.qml
        Main/Styling/FlexBasisGrowShrinkView.qml
        Main/Styling/FlexBasisGrowShrinkCode1.qml
        Main/Styling/FlexBasisGrowShrinkCode2.qml
        Main/Styling/FlexBasisGrowShrinkCode3.qml
        Main/Styling/FlexDirectionView.qml
        Main/Styling/FlexDirectionCode.qml
        Main/Styling/FlexWrapView.qml
        Main/Styling/FlexWrapCode.qml
        Main/Styling/GapView.qml
        Main/Styling/GapCode.qml
        Main/Styling/InsetsView.qml
        Main/Styling/InsetsCode.qml
        Main/Styling/JustifyContentView.qml
        Main/Styling/JustifyContentCode.qml
        Main/Styling/LayoutDirectionView.qml
        Main/Styling/LayoutDirectionCode.qml
        Main/Styling/MarginPaddingBorderView.qml
        Main/Styling/MarginPaddingBorderCode.qml
        Main/Styling/PositionView.qml
        Main/Styling/PositionCode.qml
        Main/Styling/MinMaxWidthHeightView.qml
        Main/Styling/MinMaxWidthHeightCode.qml
        Main/Styling/WidthHeightView.qml
        Main/Styling/WidthHeightCode.qml
    RESOURCES
        Main/Fonts/CascadiaMono-VariableFont_wght.ttf
        Main/Fonts/Rubik-VariableFont_wght.ttf
        Main/Styling/AlignContentView.txt
        Main/Styling/AlignItemsView.txt
        Main/Styling/AspectRatioView.txt
        Main/Styling/DisplayView.txt
        Main/Styling/FlexBasisGrowShrinkView1.txt
        Main/Styling/FlexBasisGrowShrinkView2.txt
        Main/Styling/FlexBasisGrowShrinkView3.txt
        Main/Styling/FlexDirectionView.txt
        Main/Styling/FlexWrapView.txt
        Main/Styling/GapView.txt
        Main/Styling/InsetsView.txt
        Main/Styling/JustifyContentView.txt
        Main/Styling/LayoutDirectionView.txt
        Main/Styling/MarginPaddingBorderView.txt
        Main/Styling/PositionView.txt
        Main/Styling/MinMaxWidthHeightView.txt
        Main/Styling/WidthHeightView.txt
)

target_link_libraries(Flexbox PRIVATE Qt6::Quick)
