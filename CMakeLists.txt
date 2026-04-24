cmake_minimum_required(VERSION 3.16)

project(flashdraws VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

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
    RESOURCES
        aplication.qrc
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

## RELEASE CONFIGURATION

if(WIN32)
    set(CPACK_NSIS_DISPLAY_NAME "FlashDraws")
    set(CPACK_NSIS_PACKAGE_NAME "FlashDraws")

    # GET ALL DLL`S
    if (CMAKE_BUILD_TYPE STREQUAL "Release")
        ADD_CUSTOM_COMMAND(
          TARGET appflashdraws
          POST_BUILD
          COMMAND
            CD ${CMAKE_CURRENT_BINARY_DIR} &&
            ${WINDEPLOYQT_EXECUTABLE} --pdb appflashdraws.exe
               --verbose 1 --dir . --plugindir plugins --compiler-runtime
        )
    endif()
elseif(UNIX AND NOT APPLE)
    install(TARGETS appflashdraws
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        PERMISSIONS
            OWNER_READ OWNER_WRITE OWNER_EXECUTE
            GROUP_READ GROUP_EXECUTE
            WORLD_READ WORLD_EXECUTE
    )

    set(CPACK_PACKAGE_NAME "flashdraws")
    set(CPACK_PACKAGE_CONTACT "luankaikemacksantos@gmail.com")
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A app to make flash draws")

    # RPM (FEDORA) CONFIGURATION
    set(CPACK_RPM_PACKAGE_ARCHITECTURE "x86_64")
        set(CPACK_RPM_PACKAGE_LICENSE "MIT")
endif()

include(CPack)
