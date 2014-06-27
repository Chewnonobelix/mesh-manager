TEMPLATE = app


QMAKE_CXXFLAGS += -std=c++11

HEADERS += \
    LSystem/axiom.h \
    LSystem/grammar.h \
    LSystem/nonterminal.h \
    LSystem/terminal.h \
    Mesh/Advance/Terrain/pairbruitdistance.h \
    Mesh/Advance/Terrain/terraincontinu.h \
    Mesh/Advance/Terrain/terraindiscret.h \
    Mesh/Advance/Tree/grammartree.h \
    Mesh/Advance/Tree/treent.h \
    Mesh/Advance/Tree/treet.h \
    Mesh/Advance/generateur.h \
    Mesh/Base/mesh.h \
    Mesh/Base/meshfactory.h \
    Mesh/Base/transformation.h \
    Utility/mathutils.h \
    Utility/perlinnoise.h \
    Utility/point3d.h \
    Utility/vector.h \
    Mesh/Advance/City/citynt.h \
    Mesh/Advance/City/cityt.h \
    Mesh/Advance/City/citygrammar.h \
    Utility/calcbezier.h \
    Mesh/Advance/batiment.h \
    Mesh/Base/association.h \
    Utility/triangle3d.h

SOURCES += \
    Mesh/Advance/Terrain/pairbruitdistance.cpp \
    Mesh/Advance/Terrain/terraincontinu.cpp \
    Mesh/Advance/Terrain/terraindiscret.cpp \
    Mesh/Advance/Tree/grammartree.cpp \
    Mesh/Advance/Tree/treent.cpp \
    Mesh/Advance/Tree/treet.cpp \
    Mesh/Advance/generateur.cpp \
    Mesh/Base/mesh.cpp \
    Mesh/Base/meshfactory.cpp \
    Mesh/Base/transformation.cpp \
    test/main.cpp \
    Utility/mathutils.cpp \
    Utility/perlinnoise.cpp \
    Utility/point3d.cpp \
#    main.cpp
    Mesh/Advance/City/citynt.cpp \
    Mesh/Advance/City/cityt.cpp \
    Mesh/Advance/City/citygrammar.cpp \
    Utility/calcbezier.cpp \
    Mesh/Advance/batiment.cpp \
    Mesh/Base/association.cpp \
    Utility/triangle3d.cpp
