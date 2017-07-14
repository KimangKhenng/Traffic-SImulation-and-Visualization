#-------------------------------------------------
#
# Project created by QtCreator 2017-04-05T12:14:21
#
#-------------------------------------------------

QT       += core gui svg widgets printsupport
CONFIG   += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IntersectionRoadSimulationandVisualization
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    graphicsview.cpp \
    vehicle.cpp \
    road.cpp \
    simulationscene.cpp \
    datawidget.cpp \
    simulationcontrol.cpp \
    road_ui.cpp \
    trafficlight.cpp \
    lightwidget.cpp \
    traffic_light_widget.cpp \
    trafficsignalcontrol.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    graphicsview.h \
    vehicle.h \
    road.h \
    simulationscene.h \
    datawidget.h \
    simulationcontrol.h \
    road_ui.h \
    trafficlight.h \
    lightwidget.h \
    traffic_light_widget.h \
    trafficsignalcontrol.h \
    qcustomplot.h

FORMS    += mainwindow.ui \
    datawidget.ui \
    simulationcontrol.ui

RESOURCES += \
    resource.qrc
