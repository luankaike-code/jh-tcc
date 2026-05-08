cmake_minimum_required(VERSION 3.16)

project(flashdraws VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appflashdraws
    source/backend/utils/filesGrabber/filesGrabber.cpp
    source/backend/componentsQml/timer/timer.cpp
    source/backend/utils/clipboard/clipboard.cpp
    source/backend/componentsQml/homeWindowBackend/homeWindowBackend.cpp
    source/backend/applicationBackend/applicationBackend.cpp
    source/backend/componentsQml/imagesWindowBackend/imagesWindowBackend.cpp
)

qt_add_qml_module(appflashdraws
    URI flashdraws
    VERSION 1.0

    SOURCES
        source/backend/main.cpp
        source/backend/utils/filesGrabber/filesGrabber.h source/backend/utils/filesGrabber/filesGrabber.cpp
        source/backend/componentsQml/timer/timer.h source/backend/componentsQml/timer/timer.cpp
        source/backend/utils/clipboard/clipboard.h source/backend/utils/clipboard/clipboard.cpp

        source/backend/applicationBackend/applicationBackend.hpp source/backend/applicationBackend/applicationBackend.cpp

        source/backend/componentsQml/homeWindowBackend/homeWindowBackend.h source/backend/componentsQml/homeWindowBackend/homeWindowBackend.cpp

        source/backend/componentsQml/imagesWindowBackend/imagesWindowBackend.h source/backend/componentsQml/imagesWindowBackend/imagesWindowBackend.cpp
    QML_FILES
        source/frontend/Main.qml
        source/frontend/components/defaultWindow/DefaultWindow.qml

        source/frontend/components/homeWindow/HomeWindow.qml

        source/frontend/components/draggableArea/DraggableArea.qml
        source/frontend/components/inputs/Input.qml
        source/frontend/components/inputs/InputNumber.qml
        source/frontend/components/magnitudeDisplay/MagnitudeDisplay.qml
        source/frontend/components/magnitudeDisplay/MagnitudeObj.qml
        source/frontend/components/toggleButton/ToggleButton.qml
        source/frontend/components/imageButton/ImageButton.qml

        source/frontend/components/flashDrawSessionWrapper/FlashDrawSessionWrapper.qml
        source/frontend/components/flashDrawSessionWrapper/components/dialogConfirmFinishSession/DialogConfirmFinishSession.qml
        source/frontend/components/flashDrawSessionWrapper/components/flashDrawSessionControlWindow/FlashDrawSessionControlWindow.qml
        source/frontend/components/flashDrawSessionWrapper/components/imagesWindow/ImagesWindow.qml
    RESOURCES
        application.qrc
        assets/pause.svg
        assets/play.svg
        assets/double_arrow.svg
        assets/exit.svg
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
    source/backend/componentsQml/timer
    source/backend/utils/clipboard
    source/backend/componentsQml/homeWindowBackend
    source/backend/applicationBackend/
    source/backend/componentsQml/imagesWindowBackend/
)

target_link_libraries(appflashdraws
    PRIVATE Qt6::Quick
)
target_link_libraries(appflashdraws PRIVATE Qt6::Widgets)

install(TARGETS appflashdraws
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

## RELEASE CONFIGURATION

if(WIN32)
    set(CPACK_NSIS_DISPLAY_NAME "FlashDraws")
    set(CPACK_NSIS_PACKAGE_NAME "FlashDraws")

    # GET ALL DEPENDENCIES
    install(CODE "
        set(EXE_PATH \"\$ENV{DESTDIR}\${CMAKE_INSTALL_PREFIX}/bin/appflashdraws.exe\")
        set(QML_DIR \"${CMAKE_CURRENT_SOURCE_DIR}\")

        execute_process(
            COMMAND \"${WINDEPLOYQT_EXECUTABLE}\"
                    --compiler-runtime
                    --verbose 1
                    --qmldir \"\${QML_DIR}\"
                    \"\${EXE_PATH}\"
            RESULT_VARIABLE deploy_result
        )
    ")
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

    install(FILES flashdraws.desktop
        DESTINATION share/applications
        PERMISSIONS
            OWNER_READ OWNER_WRITE
            GROUP_READ WORLD_READ
            WORLD_READ WORLD_EXECUTE
    )

    set(CPACK_PACKAGE_NAME "flashdraws")
    set(CPACK_PACKAGE_CONTACT "luankaikemacksantos@gmail.com")
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A app to make flash draws")

    # RPM (FEDORA) CONFIGURATION
    set(CPACK_RPM_PACKAGE_ARCHITECTURE "x86_64")
    set(CPACK_RPM_PACKAGE_REQUIRES
        "qt6-qtdeclarative, qt6-qtbase-gui, qt6-qtimageformats"
    )
    set(CPACK_RPM_PACKAGE_AUTOREQ ON)
    set(CPACK_RPM_PACKAGE_LICENSE "MIT")

    # DEB (DEBIAN) CONFIGURATION
    set(CPACK_DEBIAN_PACKAGE_SECTION "devel")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS
        "qml6-module-qtquick"
        "qml6-module-qtquick-controls"
        "qml6-module-qtquick-layouts"
        "qml6-module-qtquick-templates"
        "qml6-module-qtquick-effects"
        "qt6-image-formats-plugins"
        "qt6-qpa-plugins"
    )
    set(CPACK_DEBIAN_PACKAGE_GENERATE_SHLIBS ON)
endif()

include(CPack)
