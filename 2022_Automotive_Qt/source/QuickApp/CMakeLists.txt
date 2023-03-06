cmake_minimum_required(VERSION 3.16)

project(QuickApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

set(HEADERS
    odometer.h
    car.h
    powerindicator.h
)

set(SOURCES
    main.cpp
    odometer.cpp
    car.cpp
    powerindicator.cpp
)

qt_add_executable(appQuickApp
    ${HEADERS}
    ${SOURCES}
)

qt_add_qml_module(appQuickApp
    URI QuickApp
    VERSION 1.0
    QML_FILES
        main.qml
        SpeedGauge.qml
        SignalPane.qml
        Throttle.qml
        BatteryLevel.qml
        ControlWindow.qml
    RESOURCES
        images/needleyellow.png
        images/speedgauge.png
        images/gaugeCenterBig.png
        images/turnleft_off.png
        images/turnleft_on.png
        images/turnright_off.png
        images/turnright_on.png
        images/parkingbrake_off.png
        images/parkingbrake_on.png
        images/Icon_Battery_OFF.png
        images/Icon_Battery_Green.png
        images/Icon_Battery_Yellow.png
        images/Icon_Battery_Red.png
)

set_target_properties(appQuickApp PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(appQuickApp
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(appQuickApp
    PRIVATE Qt6::Quick)
