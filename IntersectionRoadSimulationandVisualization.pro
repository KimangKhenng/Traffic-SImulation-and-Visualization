#-------------------------------------------------
#
# Project created by QtCreator 2017-04-05T12:14:21
#
#-------------------------------------------------

QT       += core gui svg widgets printsupport sql opengl
CONFIG   += console
win32{
LIBS +=  -lfreeglut -lopengl32 -lglu32
}

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
    trafficlight.cpp \
    lightwidget.cpp \
    qcustomplot.cpp \
    vehiclesgenerator.cpp \
    lightwidgetleft.cpp \
    trafficcontroller.cpp \
    trafficdetector.cpp \
    generator.cpp \
    toolpanel.cpp \
    visualizepanel.cpp

HEADERS  += mainwindow.h \
    graphicsview.h \
    vehicle.h \
    road.h \
    simulationscene.h \
    datawidget.h \
    simulationcontrol.h \
    trafficlight.h \
    lightwidget.h \
    qcustomplot.h \
    commonenum.h \
    vehiclesgenerator.h \
    lightwidgetleft.h \
    trafficcontroller.h \
    trafficdetector.h \
    generator.h \
    toolpanel.h \
    visualizepanel.h

FORMS    += mainwindow.ui \
    datawidget.ui \
    simulationcontrol.ui \
    toolpanel.ui \
    visualizepanel.ui

RESOURCES += \
    resource.qrc
