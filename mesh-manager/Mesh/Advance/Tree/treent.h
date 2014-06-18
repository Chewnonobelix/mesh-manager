#ifndef TRUNKNT_H
#define TRUNKNT_H

#include "../../../LSystem/axiom.h"
#include "../../../LSystem/nonterminal.h"
#include "../../../LSystem/grammar.h"
#include "../../Base/meshfactory.h"
#include "../../../Utility/mathutils.h"
/*
 * Ordre des paramètres:
 * Le 1er paramètre de la méthode start et productionRule de TreeAxiom, TrunkNT et BranchNT corresnpond à l'âge de l'arbre (nb d'itération de la génération),
 * 0. Age de l'arbre (nb itération)
 * 1. hauteur maximal d'un segment de tronc
 * 2. nb d'"étage" de branche
 * 3. si les branche pousse par deux
 * 4. borne inférieur angle ax (en °)
 * 5. borne supérieur angle ax (en °)
 * 6. longueur maximal d'une branche
 * 7. nb d'"étage" de branche
 * 8. si les branch pousse par deux
 */

class TreeAxiom: public LSystem::Axiom<MeshBase::Mesh>
{
public:
    TreeAxiom();
    TreeAxiom(const TreeAxiom&);

    MeshBase::Mesh start(QVector<double>);
    TreeAxiom* clone(LSystem::Grammar<MeshBase::Mesh> *) const;
};

class TrunkNT: public LSystem::NonTerminal<MeshBase::Mesh>
{
public:
    TrunkNT();
    TrunkNT(const TrunkNT&);

    MeshBase::Mesh productionRules(QVector<double>);
    TrunkNT* clone(LSystem::Grammar<MeshBase::Mesh> *) const;
};

class BranchNT: public LSystem::NonTerminal<MeshBase::Mesh>
{
public:
    BranchNT();
    BranchNT(const BranchNT&);

    MeshBase::Mesh productionRules(QVector<double>);
    BranchNT* clone(LSystem::Grammar<MeshBase::Mesh> *) const;
};

#endif // TRUNKNT_H
