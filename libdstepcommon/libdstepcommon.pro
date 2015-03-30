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
    singleton.h \
    dsteppimpl.h \
    dstepdebug.h

unix {
    target.path = /usr/lib
    INSTALLS += target

    QMAKE_CXXFLAGS += -std=c++11 -Wall -pedantic
    CONFIG(debug, debug|release) {
        QMAKE_CXXFLAGS += -ggdb
    }
}
