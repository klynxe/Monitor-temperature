#-------------------------------------------------
#
# Project created by QtCreator 2019-10-03T20:51:13
#
#-------------------------------------------------

QT       += core gui serialport

CONFIG += c++17

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Monitor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    devicevalue.cpp \
    devicesetting.cpp \
    dialogselectport.cpp \
    workport.cpp \
    threadobject.cpp \
    packagesend.cpp \
    packageget.cpp \
    sleeper.cpp

HEADERS  += mainwindow.h \
    devicevalue.h \
    devicesetting.h \
    dialogselectport.h \
    workport.h \
    threadobject.h \
    packagesend.h \
    packageget.h \
    sleeper.h

FORMS    += mainwindow.ui \
    dialogselectport.ui

RESOURCES += \
    resource.qrc
