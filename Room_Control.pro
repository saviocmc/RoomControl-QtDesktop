#-------------------------------------------------
#
# Project created by QtCreator 2015-01-04T18:12:20
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Room_Control
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    MCU_Connector.cpp

HEADERS  += mainwindow.h \
    SwitchButton.h \
    MCU_Connector.h \
    Titlebar.h

FORMS    += mainwindow.ui

RESOURCES += \
    Images.qrc
