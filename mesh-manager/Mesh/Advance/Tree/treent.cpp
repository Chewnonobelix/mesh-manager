#include "treent.h"

TreeAxiom::TreeAxiom(): Axiom() {}
TreeAxiom::TreeAxiom(const TreeAxiom& t): Axiom(t) {}

TreeAxiom* TreeAxiom::clone(LSystem::Grammar<MeshBase::Mesh> * parent) const
{
    TreeAxiom* ret = new TreeAxiom(*this);
    ret->m_parent = parent;
    return ret;
}

MeshBase::Mesh TreeAxiom::start(QVector<double> param)
{
    MeshBase::Mesh ret = m_parent->productionRule("TrunkNT")->productionRules(param);
    return ret;
}

TrunkNT::TrunkNT(): NonTerminal("TrunkNT") {}
TrunkNT::TrunkNT(const TrunkNT& t): NonTerminal(t) {}

MeshBase::Mesh TrunkNT::productionRules(QVector<double> param)
{
    if(param[0] < 0)
    {
        param[0] = 0;
    }
    MeshBase::Mesh ret;
    switch((int)param[0])
    {
    case 0:
        ret = m_parent->terminalSymbol("TrunkT")->symbol(param);
        ret.redimensionner(0.1,0.1,param[1]);
        break;
    default:

        MeshBase::Mesh t2 = m_parent->terminalSymbol("TrunkT")->symbol(param);

        double a = MathUtility::Math::alea(0.1, param[1]);
        double ax = MathUtility::Math::alea(param[4], param[5]);
        int inter = a/param[2];
        t2.redimensionner(0.1,0.1,a*param[0]);
        param[0]--;
        for(int i = 0; i < (int)param[2]; i++)
        {
            QVector<double> split = param.mid(4);
            split.push_front(param[0]);
            MeshBase::Mesh add = m_parent->productionRule("BranchNT")->productionRules(split);
            //Placement d'une nouvelle branche au centre du ième étage d'un segment de tronc
            add.translation(.1,0,0.1*(inter*i + inter/2.0));
            //rotation
            double az = MathUtility::Math::alea(0.0, 360.0);
            add.rotation(ax,0, az);
            t2 += add;
            if((bool)param[3])
            {
                add = m_parent->productionRule("BranchNT")->productionRules(split);
                //Placement d'une nouvelle branche au centre du ième étage d'un segment de tronc
                add.translation(0.1,0,0.1*(inter*i + inter/2.0));
                //rotation
                add.rotation(ax,0,az+180);
                t2 += add;
            }
        }

        MeshBase::Mesh t = m_parent->productionRule("TrunkNT")->productionRules(param);
        t2.translation(0,0,-(a*(param[0]+1)));
        ret = t + t2;
    }

    return ret;
}

TrunkNT* TrunkNT::clone(LSystem::Grammar<MeshBase::Mesh> * parent) const
{
    TrunkNT* ret = new TrunkNT(*this);
    ret->m_parent = parent;
    return ret;
}

BranchNT::BranchNT(): NonTerminal("BranchNT") {}
BranchNT::BranchNT(const BranchNT& b): NonTerminal(b) {}

MeshBase::Mesh BranchNT::productionRules(QVector<double> param)
{
    if(param[0] < 0)
    {
        param[0] = 0;
    }

    MeshBase::Mesh ret;
    switch((int)param[0])
    {
    case 0:
        ret = m_parent->terminalSymbol("BranchT")->symbol(param);
        ret.redimensionner(0.1,0.1,param[3]);
        break;
    default:

        MeshBase::Mesh t2 = m_parent->terminalSymbol("BranchT")->symbol(param);

        double a = MathUtility::Math::alea(0.1, param[3]);
        double ax = MathUtility::Math::alea(param[1], param[2]);
        int inter = a/param[2];
        t2.redimensionner(0.1,0.1,a*param[0]);
        param[0]--;

        for(int i = 0; i < (int)param[4]; i++)
        {
            MeshBase::Mesh add = m_parent->productionRule("BranchNT")->productionRules(param);
            //Placement d'une nouvelle branche au centre du ième étage d'un segment de tronc
            add.translation(0.1,0,0.1*(inter*i + inter/2.0));
            //rotation
            double az = MathUtility::Math::alea(0.0, 360.0);
            add.rotation(ax,0,az);
            t2 += add;
            if((bool)param[5])
            {
                add = m_parent->productionRule("BranchNT")->productionRules(param);
                //Placement d'une nouvelle branche au centre du ième étage d'un segment de tronc
                add.translation(0.1,0,0.1*(inter*i + inter/2.0));
                //rotation
                add.rotation(ax,0,az);
                t2 += add;
            }
        }

        MeshBase::Mesh t = m_parent->productionRule("BranchNT")->productionRules(param);
        t2.translation(0,0,-a*(param[0]+1));
        ret = t + t2;
    }

    return ret;
}

BranchNT* BranchNT::clone(LSystem::Grammar<MeshBase::Mesh> * parent) const
{
    BranchNT* ret = new BranchNT(*this);
    ret->m_parent = parent;
    return ret;
}
