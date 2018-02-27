#-------------------------------------------------
#
# Project created by QtCreator 2017-04-05T12:14:21
#
#-------------------------------------------------

QT       += core gui svg widgets printsupport sql opengl
CONFIG   += console
DEFINES  += QCUSTOMPLOT_USE_OPENGL
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
    simulationcontrol.cpp \
    trafficlight.cpp \
    lightwidget.cpp \
    qcustomplot.cpp \
    vehiclesgenerator.cpp \
    lightwidgetleft.cpp \
    trafficcontroller.cpp \
    trafficdetector.cpp \
    generator.cpp \
    visualizepanel.cpp \
    workerthread.cpp

HEADERS  += mainwindow.h \
    graphicsview.h \
    vehicle.h \
    road.h \
    simulationscene.h \
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
    visualizepanel.h \
    workerthread.h

FORMS    += mainwindow.ui \
    simulationcontrol.ui \
    visualizepanel.ui

RESOURCES += \
    resource.qrc
