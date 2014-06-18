#ifndef TREET_H
#define TREET_H

#include "../../../LSystem/terminal.h"
#include "../../Base/mesh.h"
#include "../../Base/meshfactory.h"

class TrunkT: public LSystem::Terminal<MeshBase::Mesh>
{
public:
    TrunkT();
    TrunkT(const TrunkT&);
    virtual MeshBase::Mesh symbol(QVector<double>);
    virtual TrunkT* clone(LSystem::Grammar<MeshBase::Mesh>*) const;
};

class BranchT: public LSystem::Terminal<MeshBase::Mesh>
{
public:
    BranchT();
    BranchT(const BranchT&);
    virtual MeshBase::Mesh symbol(QVector<double>);
    virtual BranchT *clone(LSystem::Grammar<MeshBase::Mesh>*) const;
};

#endif // TREET_H
