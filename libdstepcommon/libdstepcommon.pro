#-------------------------------------------------
#
# Project created by QtCreator 2015-03-23T02:27:24
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = dstepcommon
TEMPLATE = lib

DEFINES += LIBDSTEPCOMMON_LIBRARY

SOURCES += libdstepcommon.cpp

HEADERS += libdstepcommon.h\
        libdstepcommon_global.h \
    callonce.h \
    singleton.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
