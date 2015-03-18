#-------------------------------------------------
#
# Project created by QtCreator 2015-03-18T17:31:54
#
#-------------------------------------------------

QT       += testlib dbus

QT       -= gui

TARGET = dstepwmxcb
TEMPLATE = lib

DEFINES += LIBDSTEPWMXCB_LIBRARY

SOURCES += libdstepwmxcb.cpp

HEADERS += libdstepwmxcb.h\
        libdstepwmxcb_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
