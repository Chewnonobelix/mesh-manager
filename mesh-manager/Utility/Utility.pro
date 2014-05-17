#-------------------------------------------------
#
# Project created by QtCreator 2014-05-17T15:01:35
#
#-------------------------------------------------

QT       -= gui

TARGET = Utility
TEMPLATE = lib

DEFINES += UTILITY_LIBRARY

SOURCES += \
    perlinnoise.cpp \
    point3d.cpp

HEADERS +=\
        utility_global.h \
    perlinnoise.h \
    point3d.h \
    vector.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
