#-------------------------------------------------
#
# Project created by QtCreator 2014-05-17T14:44:02
#
#-------------------------------------------------

QT       -= gui

TARGET = Mesh
TEMPLATE = lib

DEFINES += MESH_LIBRARY

SOURCES += \
    generateur.cpp \
    mesh.cpp \
    meshfactory.cpp \
    terraincontinu.cpp \
    terraindiscret.cpp \
    transformation.cpp \
    pairbruitdistance.cpp

HEADERS +=\
        mesh_global.h \
    generateur.h \
    mesh.h \
    meshfactory.h \
    terraincontinu.h \
    terraindiscret.h \
    transformation.h \
    pairbruitdistance.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
