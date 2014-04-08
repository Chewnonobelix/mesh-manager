#-------------------------------------------------
#
# Project created by QtCreator 2014-03-25T16:29:54
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = synthese_Quentin
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    point3d.cpp \
    mesh.cpp \
    generateur.cpp \
    meshfactory.cpp \
    transformation.cpp \
    batiment.cpp

HEADERS += \
    point3d.h \
    vector.h \
    mesh.h \
    generateur.h \
    meshfactory.h \
    transformation.h \
    batiment.h
