cmake_minimum_required(VERSION 3.16)

project(RoboticFinger VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        RoboticFinger.cpp
        RoboticFinger.h
        RoboticFinger.ui
        Model.cpp
        Model.h
        ControlSystem.cpp
        ControlSystem.h
        PlotCanvas.cpp
        PlotCanvas.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(RoboticFinger
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}         
    )
else()
    add_executable(RoboticFinger
        ${PROJECT_SOURCES}
    )
endif()

target_include_directories(RoboticFinger PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(RoboticFinger PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(RoboticFinger PROPERTIES
    ${BUNDLE_ID_OPTION}
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS RoboticFinger
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(RoboticFinger)
endif()
