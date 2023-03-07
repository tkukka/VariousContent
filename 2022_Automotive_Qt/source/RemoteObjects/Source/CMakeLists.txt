cmake_minimum_required(VERSION 3.16)

project(Source VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick RemoteObjects REQUIRED)

set(HEADERS
        car.h
        controller.h
)

set(SOURCES
        main.cpp
        car.cpp
        controller.cpp
)

qt_add_executable(appSource
    ${HEADERS}
    ${SOURCES}
)

qt_add_qml_module(appSource
    URI Source
    VERSION 1.0
    QML_FILES 
        main.qml
    RESOURCES
        images/Car.png
)

qt_add_repc_sources(appSource
    ../car.rep
)

set_target_properties(appSource PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(appSource
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(appSource
    PRIVATE Qt6::Quick Qt::RemoteObjects)
