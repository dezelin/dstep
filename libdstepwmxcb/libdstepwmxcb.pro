#
# Copyright (c) 2015 Aleksandar Dezelin
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#

QT       += testlib dbus

QT       -= gui

TARGET = dstepwmxcb
TEMPLATE = lib

DEFINES += LIBDSTEPWMXCB_LIBRARY

SOURCES += libdstepwmxcb.cpp \
    dstepwmxcbobjectfactory.cpp \
    dstepwmxcbplugin.cpp \
    dstepwmxcbeventloop.cpp \
    dstepwmxcbwindowdecorator.cpp \
    dstepwmxcbwindowmanager.cpp \
    dstepwmxcbwindowtheme.cpp \
    dstepwmxcb.cpp

HEADERS += libdstepwmxcb.h\
        libdstepwmxcb_global.h \
    dstepwmxcbobjectfactory.h \
    dstepwmxcbplugin.h \
    dstepwmxcbeventloop.h \
    dstepwmxcbwindowdecorator.h \
    dstepwmxcbwindowmanager.h \
    dstepwmxcbwindowtheme.h \
    dstepwmxcb.h

OTHER_FILES += \
    dstepwmxcb.json

unix {
    target.path = $$[QT_INSTALL_PLUGINS]/dstepwm
    INSTALLS += target

    CONFIG(debug, debug|release) {
        QMAKE_CXXFLAGS += -ggdb
    }
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libdstepwm/release/ -ldstepwm
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libdstepwm/debug/ -ldstepwm
else:unix: LIBS += -L$$OUT_PWD/../libdstepwm/ -ldstepwm

INCLUDEPATH += $$PWD/../libdstepwm
DEPENDPATH += $$PWD/../libdstepwm

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libdstepcommon/release/ -ldstepcommon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libdstepcommon/debug/ -ldstepcommon
else:unix: LIBS += -L$$OUT_PWD/../libdstepcommon/ -ldstepcommon

INCLUDEPATH += $$PWD/../libdstepcommon
DEPENDPATH += $$PWD/../libdstepcommon

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += xcb
