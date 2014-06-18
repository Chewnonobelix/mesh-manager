#include "treet.h"

TrunkT::TrunkT(): Terminal("TrunkT") {}

TrunkT::TrunkT(const TrunkT& t): Terminal(t) {}

MeshBase::Mesh TrunkT::symbol(QVector<double>)
{
    return MeshBase::MeshFactory::cylindre();
}

TrunkT* TrunkT::clone(LSystem::Grammar<MeshBase::Mesh>* parent) const
{
    TrunkT* ret = new TrunkT(*this);
    ret->m_parent = parent;
    return ret;
}

BranchT::BranchT(): Terminal("BranchT") {}

BranchT::BranchT(const BranchT& b): Terminal(b) {}

MeshBase::Mesh BranchT::symbol(QVector<double>)
{
    return MeshBase::MeshFactory::cube(1, 1, 1);
}

BranchT* BranchT::clone(LSystem::Grammar<MeshBase::Mesh> * parent) const
{
    BranchT* ret = new BranchT(*this);
    ret->m_parent = parent;
    return ret;
}

