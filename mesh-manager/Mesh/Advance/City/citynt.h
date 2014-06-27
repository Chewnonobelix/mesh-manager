#ifndef CITYNT_H
#define CITYNT_H

#include "../../../LSystem/nonterminal.h"
#include "../../Base/mesh.h"
#include "../../../LSystem/grammar.h"
#include "../../../Utility/calcbezier.h"
#include "../../../Utility/point3d.h"
#include "../../../Utility/mathutils.h"
#include "../../../LSystem/axiom.h"


class CityAxiom: public LSystem::Axiom<MeshBase::Mesh>
{
  public:
    CityAxiom();
    CityAxiom(const CityAxiom&);
    MeshBase::Mesh start(QVector<double>);
    CityAxiom* clone(LSystem::Grammar<MeshBase::Mesh> *) const;
};

class QuartierNT: public LSystem::NonTerminal<MeshBase::Mesh>
{
public:
   QuartierNT();
   QuartierNT(const QuartierNT&);
   MeshBase::Mesh productionRules(QVector<double>);
   QuartierNT* clone(LSystem::Grammar<MeshBase::Mesh> *) const;
};

class AvenueNT: public LSystem::NonTerminal<MeshBase::Mesh>
{
public:
   AvenueNT();
   AvenueNT(const AvenueNT&);
   /**
    * @brief productionRules
    * Param 0 à 2 point de départ de l'avenue
    */
   MeshBase::Mesh productionRules(QVector<double>);
   AvenueNT* clone(LSystem::Grammar<MeshBase::Mesh> *) const;
   MeshBase::Mesh batiment(QString&);
};

class RueNT: public LSystem::NonTerminal<MeshBase::Mesh>
{
public:
   RueNT();
   RueNT(const RueNT&);
   /**
    * @brief productionRules
    * Param 0 à 2 point de départ de la rue
    */
   MeshBase::Mesh productionRules(QVector<double>);
   RueNT* clone(LSystem::Grammar<MeshBase::Mesh> *) const;
   MeshBase::Mesh batiment(QString&);
};

#endif // CITYNT_H
