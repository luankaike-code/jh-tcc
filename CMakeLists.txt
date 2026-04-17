cmake_minimum_required(VERSION 3.16)

project(flashdraws VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appflashdraws
    source/backend/utils/filesGrabber/filesGrabber.cpp
    source/backend/utils/timer/timer.cpp
)

qt_add_qml_module(appflashdraws
    URI flashdraws
    VERSION 1.0

    SOURCES
        source/backend/main.cpp
        source/backend/utils/filesGrabber/filesGrabber.h source/backend/utils/filesGrabber/filesGrabber.cpp
        source/backend/utils/timer/timer.h source/backend/utils/timer/timer.cpp
    QML_FILES
        source/frontend/Main.qml
        source/frontend/components/flashDrawWindow/FlashDrawWindow.qml
        source/frontend/components/homeWindow/HomeWindow.qml
        source/frontend/components/flashDrawSessionWindow/FlashDrawSessionWindow.qml
        source/frontend/components/draggableArea/DraggableArea.qml
        source/frontend/components/inputs/Input.qml
        source/frontend/components/inputs/InputNumber.qml
        source/frontend/components/magnitudeDisplay/MagnitudeDisplay.qml
        source/frontend/components/magnitudeDisplay/MagnitudeObj.qml
)

if(UNIX AND NOT APPLE)
    add_compile_definitions(__float80=long\ double)
endif()

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appflashdraws PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appflashdraws
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_include_directories(appflashdraws PRIVATE
    source/backend/utils/filesGrabber
    source/backend/utils/timer
)

target_link_libraries(appflashdraws
    PRIVATE Qt6::Quick
)

install(TARGETS appflashdraws
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
