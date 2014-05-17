#-------------------------------------------------
#
# Project created by QtCreator 2014-05-17T14:43:30
#
#-------------------------------------------------

QT       -= gui

TARGET = LSystem
TEMPLATE = lib

DEFINES += LSYSTEM_LIBRARY

SOURCES +=

HEADERS +=\
        lsystem_global.h \
    axiom.h \
    grammar.h \
    nonterminal.h \
    terminal.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
