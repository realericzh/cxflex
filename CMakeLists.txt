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
    Flexbox/Flexbox.h Flexbox/Flexbox_p.h Flexbox/Flexbox.cpp

    # <-- Flexbox Core Code
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
)

target_link_libraries(Flexbox PRIVATE Qt6::Quick)
