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
    McuConnector.cpp \
    MainWindow.cpp

HEADERS  += \
    SwitchButton.h \
    Titlebar.h \
    McuConnector.h \
    MainWindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    Images.qrc
