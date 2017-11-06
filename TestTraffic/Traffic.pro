#-------------------------------------------------
#
# Project created by QtCreator 2017-10-31T10:11:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Traffic
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    graphicsview.cpp \
    lightwidget.cpp \
    lightwidgetleft.cpp \
    trafficlight.cpp \
    trafficcontroller.cpp \
    trafficdetector.cpp \
    vehicle.cpp

HEADERS  += mainwindow.h \
    graphicsview.h \
    lightwidget.h \
    lightwidgetleft.h \
    trafficlight.h \
    trafficcontroller.h \
    trafficdetector.h \
    vehicle.h \
    road.h

FORMS    += mainwindow.ui
