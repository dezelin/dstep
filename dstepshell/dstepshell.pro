#-------------------------------------------------
#
# Project created by QtCreator 2015-03-18T16:29:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dstepshell
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libdstepshell/release/ -ldstepshell
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libdstepshell/debug/ -ldstepshell
else:unix: LIBS += -L$$OUT_PWD/../libdstepshell/ -ldstepshell

INCLUDEPATH += $$PWD/../libdstepshell
DEPENDPATH += $$PWD/../libdstepshell
