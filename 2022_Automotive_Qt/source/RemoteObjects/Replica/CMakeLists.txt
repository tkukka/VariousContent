cmake_minimum_required(VERSION 3.16)

project(Replica VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick RemoteObjects REQUIRED)

set(HEADERS
        dashboard.h
)

set(SOURCES
        main.cpp
        dashboard.cpp
)

qt_add_executable(appReplica
    ${HEADERS}
    ${SOURCES}
)

qt_add_qml_module(appReplica
    URI Replica
    VERSION 1.0
    QML_FILES 
        main.qml
    RESOURCES
        images/Gauge.png
)

qt_add_repc_replicas(appReplica
    ../car.rep
)

set_target_properties(appReplica PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(appReplica
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(appReplica
    PRIVATE Qt6::Quick Qt::RemoteObjects)
