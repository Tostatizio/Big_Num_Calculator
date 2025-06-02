cmake_minimum_required(VERSION 3.16)

project(BigNumCalculator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick QuickControls2 Widgets)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appBigNumCalculator
    main.cpp
)

qt_add_qml_module(appBigNumCalculator
    URI BigNumCalculator
    VERSION 1.0
    QML_FILES Main.qml Components/BasicNumpad.qml  Components/MenuItem.qml Components/NumpadButton.qml Components/SideMenuItem.qml
    SOURCES  Modules/backhelper.cpp Modules/backhelper.h
    RESOURCES Assets/menu_icon.png
    RESOURCES
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appBigNumCalculator PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appBigNumCalculator
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appBigNumCalculator
    PRIVATE Qt6::Quick
)
target_link_libraries(appBigNumCalculator
    PRIVATE Qt6::QuickControls2
)
target_link_libraries(appBigNumCalculator
    PRIVATE Qt6::Widgets
)

include(GNUInstallDirs)
install(TARGETS appBigNumCalculator
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
