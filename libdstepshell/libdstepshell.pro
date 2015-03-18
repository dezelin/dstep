#-------------------------------------------------
#
# Project created by QtCreator 2015-03-18T17:12:37
#
#-------------------------------------------------

QT       += testlib dbus

QT       -= gui

TARGET = dstepshell
TEMPLATE = lib

DEFINES += LIBDSTEPSHELL_LIBRARY

SOURCES += libdstepshell.cpp

HEADERS += libdstepshell.h\
        libdstepshell_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
