#ifndef CITYT_H
#define CITYT_H

#include "../../../LSystem/terminal.h"
#include "../../Base/mesh.h"
#include "../../Base/meshfactory.h"
#include "../../Advance/generateur.h"

#include <QDebug>

class MaisonT: public LSystem::Terminal<MeshBase::Mesh>
{
public:
   MaisonT();
   MaisonT(const MaisonT&);
   MeshBase::Mesh symbol(QVector<double>);
   MaisonT* clone(LSystem::Grammar<MeshBase::Mesh> *) const;
};

class ImmeubleT: public LSystem::Terminal<MeshBase::Mesh>
{
public:
   ImmeubleT();
   ImmeubleT(const ImmeubleT&);
   MeshBase::Mesh symbol(QVector<double>);
   ImmeubleT* clone(LSystem::Grammar<MeshBase::Mesh> *) const;
};

class AutreT: public LSystem::Terminal<MeshBase::Mesh>
{
public:
   AutreT();
   AutreT(const AutreT&);
   MeshBase::Mesh symbol(QVector<double>);
   AutreT* clone(LSystem::Grammar<MeshBase::Mesh> *) const;
};

class PlaceT: public LSystem::Terminal<MeshBase::Mesh>
{
public:
   PlaceT();
   PlaceT(const PlaceT&);
   MeshBase::Mesh symbol(QVector<double>);
   PlaceT* clone(LSystem::Grammar<MeshBase::Mesh> *) const;
};

class AvenueT: public LSystem::Terminal<MeshBase::Mesh>
{
public:
   AvenueT();
   AvenueT(const AvenueT&);
   MeshBase::Mesh symbol(QVector<double>);
   AvenueT* clone(LSystem::Grammar<MeshBase::Mesh> *) const;
};

class RueT: public LSystem::Terminal<MeshBase::Mesh>
{
public:
   RueT();
   RueT(const RueT&);
   MeshBase::Mesh symbol(QVector<double>);
   RueT* clone(LSystem::Grammar<MeshBase::Mesh> *) const;
};

#endif // CITYT_H
