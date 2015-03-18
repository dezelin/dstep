#-------------------------------------------------
#
# Project created by QtCreator 2015-03-18T16:15:02
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = dstepwm
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libdstepwm/release/ -ldstepwm
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libdstepwm/debug/ -ldstepwm
else:unix: LIBS += -L$$OUT_PWD/../libdstepwm/ -ldstepwm

INCLUDEPATH += $$PWD/../libdstepwm
DEPENDPATH += $$PWD/../libdstepwm
