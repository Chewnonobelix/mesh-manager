#include "cityt.h"

MaisonT::MaisonT(): Terminal("Maison") {}
MaisonT::MaisonT(const MaisonT& m): Terminal(m) {}
MeshBase::Mesh MaisonT::symbol(QVector<double> p)
{
    qDebug()<<"Maison";
    MeshBase::Mesh ret = MeshBase::MeshFactory::cylindre();
    ret.redimensionner(0.1,0.1,0.1);
    ret.translation(p[0], p[1], p[2]);
    return ret;
}

MaisonT* MaisonT::clone(LSystem::Grammar<MeshBase::Mesh> * parent) const
{
    MaisonT* ret = new MaisonT(*this);
    ret->m_parent = parent;
    return ret;
}

ImmeubleT::ImmeubleT(): Terminal("Immeuble") {}
ImmeubleT::ImmeubleT(const ImmeubleT& i): Terminal(i) {}
MeshBase::Mesh ImmeubleT::symbol(QVector<double> p)
{
    qDebug()<<"Immeuble";
    MeshBase::Mesh ret = MeshBase::MeshFactory::cube();
    ret.redimensionner(0.1,0.1,MathUtility::Math::alea(0.1,2.0));
    ret.translation(p[0], p[1], p[2]);
    return ret;
}

ImmeubleT* ImmeubleT::clone(LSystem::Grammar<MeshBase::Mesh> * parent) const
{
    ImmeubleT* ret = new ImmeubleT(*this);
    ret->m_parent = parent;
    return ret;
}


AutreT::AutreT(): Terminal("Autre") {}
AutreT::AutreT(const AutreT& a): Terminal(a) {}
MeshBase::Mesh AutreT::symbol(QVector<double> p)
{
    qDebug()<<"Autre";
    MeshBase::Mesh ret = MeshBase::MeshFactory::cone();
    ret.redimensionner(0.1,0.1,0.1);
    ret.translation(p[0], p[1], p[2]);
    return ret;
}

AutreT* AutreT::clone(LSystem::Grammar<MeshBase::Mesh> * parent) const
{
    AutreT* ret = new AutreT(*this);
    ret->m_parent = parent;
    return ret;
}

PlaceT::PlaceT(): Terminal("Place") {}
PlaceT::PlaceT(const PlaceT& p): Terminal(p) {}
MeshBase::Mesh PlaceT::symbol(QVector<double> p)
{
    qDebug()<<"Place";
    MeshBase::Mesh ret = MeshBase::MeshFactory::cone();
    ret.redimensionner(0.1,0.1,0.1);
    ret.translation(p[0], p[1], p[2]);
    return ret;
}


PlaceT* PlaceT::clone(LSystem::Grammar<MeshBase::Mesh> * parent) const
{
    PlaceT* ret = new PlaceT(*this);
    ret->m_parent = parent;
    return ret;
}

AvenueT::AvenueT(): Terminal("Avenue") {}
AvenueT::AvenueT(const AvenueT& a): Terminal(a) {}
MeshBase::Mesh AvenueT::symbol(QVector<double>)
{
    qDebug()<<"Avenue";
    return MeshBase::Mesh();
}

AvenueT* AvenueT::clone(LSystem::Grammar<MeshBase::Mesh> * parent) const
{
    AvenueT* ret = new AvenueT(*this);
    ret->m_parent = parent;
    return ret;
}

RueT::RueT(): Terminal("Rue") {}
RueT::RueT(const RueT& r): Terminal(r) {}
MeshBase::Mesh RueT::symbol(QVector<double>)
{
    qDebug()<<"Rue";
    return MeshBase::Mesh();
}

RueT* RueT::clone(LSystem::Grammar<MeshBase::Mesh> * parent) const
{
    RueT* ret = new RueT(*this);
    ret->m_parent = parent;
    return ret;
}
