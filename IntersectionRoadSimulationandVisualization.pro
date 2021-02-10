#-------------------------------------------------
#
# Project created by QtCreator 2017-04-05T12:14:21
#
#-------------------------------------------------

QT       += core gui svg widgets printsupport opengl
CONFIG   += static

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IntersectionRoadSimulationandVisualization
TEMPLATE = app

RESOURCES += \
    resource.qrc

HEADERS += \
    Entities/TrafficLight/lightwidget.h \
    Entities/TrafficLight/lightwidgetleft.h \
    Entities/TrafficLight/trafficlight.h \
    Entities/Vehicle/vehicle.h \
    Entities/Vehicle/vehiclesight.h \
    Entities/trafficcontroller.h \
    Entities/trafficdetector.h \
    UI/graphicsview.h \
    UI/mainwindow.h \
    UI/simulationscene.h \
    UI/visualizepanel.h \
    Utilities/generator.h \
    Utilities/qcustomplot.h \
    Utilities/road.h \
    Utilities/simulationcontrol.h \
    Utilities/vehiclesgenerator.h \
    commonenum.h \
    UI/simulationcontrolwidget.h \
    UI/uimainwindow.h \
    UI/aboutwidget.h \
    Utilities/roadintersectionsimulation.h \
    UI/helpwidget.h \
    Utilities/qlightboxwidget.h \
    UI/intropage.h \
    UI/simulationsetup.h

SOURCES += \
    Entities/TrafficLight/lightwidget.cpp \
    Entities/TrafficLight/lightwidgetleft.cpp \
    Entities/TrafficLight/trafficlight.cpp \
    Entities/Vehicle/vehicle.cpp \
    Entities/Vehicle/vehiclesight.cpp \
    Entities/trafficcontroller.cpp \
    Entities/trafficdetector.cpp \
    UI/graphicsview.cpp \
    UI/mainwindow.cpp \
    UI/simulationscene.cpp \
    UI/visualizepanel.cpp \
    Utilities/generator.cpp \
    Utilities/qcustomplot.cpp \
    Utilities/road.cpp \
    Utilities/simulationcontrol.cpp \
    Utilities/vehiclesgenerator.cpp \
    main.cpp \
    UI/simulationcontrolwidget.cpp \
    UI/uimainwindow.cpp \
    UI/aboutwidget.cpp \
    Utilities/roadintersectionsimulation.cpp \
    UI/helpwidget.cpp \
    Utilities/qlightboxwidget.cpp \
    UI/intropage.cpp \
    UI/simulationsetup.cpp

FORMS += \
    UI/mainwindow.ui \
    UI/visualizepanel.ui \
    Utilities/simulationcontrol.ui \
    UI/simulationcontrolwidget.ui \
    UI/uimainwindow.ui \
    UI/aboutwidget.ui \
    UI/helpwidget.ui \
    UI/intropage.ui \
    UI/simulationsetup.ui

DISTFILES += \
    CMakeLists.txt
