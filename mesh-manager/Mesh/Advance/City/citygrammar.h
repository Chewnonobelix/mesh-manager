#ifndef CITYGRAMMAR_H
#define CITYGRAMMAR_H

#include "cityt.h"
#include "citynt.h"
#include "../../../LSystem/grammar.h"

class CityGrammar: public LSystem::Grammar<MeshBase::Mesh>
{
public:
    CityGrammar();
};

#endif // CITYGRAMMAR_H
