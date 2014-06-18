#ifndef GRAMMARTREE_H
#define GRAMMARTREE_H

#include "../../../LSystem/grammar.h"
#include "../../Base/mesh.h"
#include "treent.h"
#include "treet.h"

class GrammarTree: public LSystem::Grammar<MeshBase::Mesh>
{
public:
    GrammarTree();
};

#endif // GRAMMARTREE_H
