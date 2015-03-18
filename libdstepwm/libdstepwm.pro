#-------------------------------------------------
#
# Project created by QtCreator 2015-03-18T17:14:01
#
#-------------------------------------------------

QT       += testlib dbus

QT       -= gui

TARGET = dstepwm
TEMPLATE = lib

DEFINES += LIBDSTEPWM_LIBRARY

SOURCES += libdstepwm.cpp

HEADERS += libdstepwm.h\
        libdstepwm_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
