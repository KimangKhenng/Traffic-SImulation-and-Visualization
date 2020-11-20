cmake_minimum_required(VERSION 3.1.0)

project(IntersectionRoadSimulationandVisualization VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5
    COMPONENTS
    Widgets
    Core
    Gui
    Printsupport
    Opengl
    Svg
    REQUIRED)

add_executable(IntersectionRoadSimulationandVisualization
    Entities/TrafficLight/lightwidget.h
    Entities/TrafficLight/lightwidgetleft.h
    Entities/TrafficLight/trafficlight.h
    Entities/Vehicle/vehicle.h
    Entities/Vehicle/vehiclesight.h
    Entities/trafficcontroller.h
    Entities/trafficdetector.h
    UI/graphicsview.h
    UI/mainwindow.h
    UI/simulationscene.h
    UI/visualizepanel.h
    Utilities/generator.h
    Utilities/qcustomplot.h
    Utilities/road.h
    Utilities/simulationcontrol.h
    Utilities/vehiclesgenerator.h
    commonenum.h
    UI/simulationcontrolwidget.h
    UI/uimainwindow.h
    UI/aboutwidget.h
    Utilities/roadintersectionsimulation.h
    UI/helpwidget.h
    Utilities/qlightboxwidget.h
    UI/intropage.h
    UI/simulationsetup.h
    Entities/TrafficLight/lightwidget.cpp
    Entities/TrafficLight/lightwidgetleft.cpp
    Entities/TrafficLight/trafficlight.cpp
    Entities/Vehicle/vehicle.cpp
    Entities/Vehicle/vehiclesight.cpp
    Entities/trafficcontroller.cpp
    Entities/trafficdetector.cpp
    UI/graphicsview.cpp
    UI/mainwindow.cpp
    UI/simulationscene.cpp
    UI/visualizepanel.cpp
    Utilities/generator.cpp
    Utilities/qcustomplot.cpp
    Utilities/road.cpp
    Utilities/simulationcontrol.cpp
    Utilities/vehiclesgenerator.cpp
    main.cpp
    UI/simulationcontrolwidget.cpp
    UI/uimainwindow.cpp
    UI/aboutwidget.cpp
    Utilities/roadintersectionsimulation.cpp
    UI/helpwidget.cpp
    Utilities/qlightboxwidget.cpp
    UI/intropage.cpp
    UI/simulationsetup.cpp
    UI/mainwindow.ui
    UI/visualizepanel.ui
    Utilities/simulationcontrol.ui
    UI/simulationcontrolwidget.ui
    UI/uimainwindow.ui
    UI/aboutwidget.ui
    UI/helpwidget.ui
    UI/intropage.ui
    UI/simulationsetup.ui
    resources.qrc
)

target_link_libraries(IntersectionRoadSimulationandVisualization
    Qt5::Widgets
    Qt5::Core
    Qt5::Svg
    Qt5::Gui
    Qt5::Printsupport
    Qt5::Opengl
    )
# set up a mapping so that the Release configuration for the Qt imported target is
# used in the COVERAGE CMake configuration.
set_target_properties(
    Qt5::Widgets
    Qt5::Core
    Qt5::Svg
    Qt5::Gui
    Qt5::Printsupport
    Qt5::Opengl
    PROPERTIES MAP_IMPORTED_CONFIG_COVERAGE "RELEASE")
