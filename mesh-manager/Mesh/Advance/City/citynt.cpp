#include "citynt.h"

CityAxiom::CityAxiom(): Axiom() {}
CityAxiom::CityAxiom(const CityAxiom& c): Axiom(c) {}
MeshBase::Mesh CityAxiom::start(QVector<double> param)
{
    return m_parent->productionRule("Avenue")->productionRules(param);
}

CityAxiom* CityAxiom::clone(LSystem::Grammar<MeshBase::Mesh> * parent) const
{
    CityAxiom* ret = new CityAxiom(*this);
    ret->m_parent = parent;
    return ret;
}

QuartierNT::QuartierNT(): NonTerminal("Quartier") {}
QuartierNT::QuartierNT(const QuartierNT& q): NonTerminal(q) {}
MeshBase::Mesh QuartierNT::productionRules(QVector<double>)
{
    return MeshBase::Mesh();
}

QuartierNT* QuartierNT::clone(LSystem::Grammar<MeshBase::Mesh> * parent) const
{
    QuartierNT* ret = new QuartierNT(*this);
    ret->m_parent = parent;
    return ret;
}

AvenueNT::AvenueNT(): NonTerminal("Avenue")
{}

AvenueNT::AvenueNT(const AvenueNT & a): NonTerminal(a) {}

MeshBase::Mesh AvenueNT::productionRules(QVector<double> param)
{
//    qDebug()<<"Avenue NT";
    double longeur = MathUtility::Math::alea(100.0, 5000.0);
    double largeur = MathUtility::Math::alea(0.0,100.0);
    int orientation2 = MathUtility::Math::alea(0,2);
    int orientation3 = MathUtility::Math::alea(0,2);
    int orientation4 = MathUtility::Math::alea(0,2);

    if(orientation2 == 0)
    {
        orientation2 = -1;
    }

    if(orientation3 == 0)
    {
        orientation3 = -1;
    }

    if(orientation4 == 0)
    {
        orientation4 = -1;
    }

    Geometry::Point3D p1, p2, p3, p4;
    p1.setX(param[0]);
    p1.setY(param[1]);
    p1.setZ(param[2]);

    p2.setX(MathUtility::Math::alea(0.0, longeur));
    p2.setY(orientation2*MathUtility::Math::alea(0.0, largeur));
    p2.setZ(0);

    p3.setX(MathUtility::Math::alea(0.0, longeur));
    p3.setY(orientation3*MathUtility::Math::alea(0.0, largeur));
    p3.setZ(0);

    p4.setX(longeur);
    p4.setY(orientation4*largeur);
    p4.setZ(0);


    calcBezier courbe(p1,p2,p3,p4, longeur/10);
    MeshBase::Mesh a =  m_parent->terminalSymbol("Avenue")->symbol({p1.getX(), p1.getY(), p1.getZ(),
                                                                   p2.getX(), p2.getY(), p2.getZ(),
                                                                   p3.getX(), p3.getY(), p3.getZ(),
                                                                   p4.getX(), p4.getY(), p4.getZ(), longeur/10.0 });
    QVector<Geometry::Point3D> tab = courbe.tabPoints();
    for(int i = 0; i < tab.size(); i ++)
    {
        if(i%3 == 0)
        {
            double angle = MathUtility::Math::alea(0,180);
            int o = MathUtility::Math::alea(0,2);
            MeshBase::Mesh r, t;
            Triplet tr(tab[i]);
            QString id;

            switch (MathUtility::Math::alea(0,3))
            {
            case 0: //Batiment
                t = batiment(id);
                a.addAssoc(id, t, tr);
                break;
            case 1: //Rue
                if(o == 0)
                {
                    o = -1;
                }
                r = m_parent->productionRule("Rue")->productionRules({tab[i].getX(), tab[i].getY(), tab[i].getZ()});
                r.rotation(0,0,o*angle);
                a += r;
                break;
            case 2: //Avenue
                if(o == 0)
                {
                    o = -1;
                }
                r = m_parent->productionRule("Avenue")->productionRules({tab[i].getZ(), tab[i].getY(), tab[i].getZ()});
                r.rotation(0,0,o*angle);
                a += r;

                break;
            }
        }
        else
        {
            MeshBase::Mesh t;
            Triplet tr(tab[i]);
            QString id;

            t = batiment(id);
            a.addAssoc(id, t, tr);
        }
    }

    return a;
}

MeshBase::Mesh AvenueNT::batiment(QString& nom)
{
    MeshBase::Mesh ret;

    switch(MathUtility::Math::alea(0,3))
    {
    case 0:
        nom = "Immeuble";
        ret = m_parent->terminalSymbol("Immeuble")->symbol({0.0, 0.0, 0.0});
        break;
    case 1:
        nom = "Maison";
        ret = m_parent->terminalSymbol("Maison")->symbol({0.0, 0.0, 0.0});
        break;
    case 2:
        nom = "Autre";
        ret = m_parent->terminalSymbol("Autre")->symbol({0.0, 0.0, 0.0});
        break;
    }

    return ret;
}

AvenueNT* AvenueNT::clone(LSystem::Grammar<MeshBase::Mesh> * parent) const
{
    AvenueNT* ret = new AvenueNT(*this);
    ret->m_parent = parent;
    return ret;
}


RueNT::RueNT(): NonTerminal("Rue") {}
RueNT::RueNT(const RueNT& r): NonTerminal(r) {}

MeshBase::Mesh RueNT::productionRules(QVector<double> param)
{

//    qDebug()<<"Rue NT";
    double longeur = MathUtility::Math::alea(100.0, 5000.0);
    double largeur = MathUtility::Math::alea(0.0,100.0);
    int orientation2 = MathUtility::Math::alea(0,2);
    int orientation3 = MathUtility::Math::alea(0,2);
    int orientation4 = MathUtility::Math::alea(0,2);

    if(orientation2 == 0)
    {
        orientation2 = -1;
    }

    if(orientation3 == 0)
    {
        orientation3 = -1;
    }

    if(orientation4 == 0)
    {
        orientation4 = -1;
    }

    Geometry::Point3D p1, p2, p3, p4;
    p1.setX(param[0]);
    p1.setY(param[1]);
    p1.setZ(param[2]);

    p2.setX(MathUtility::Math::alea(0.0, longeur));
    p2.setY(orientation2*MathUtility::Math::alea(0.0, largeur));
    p2.setZ(0);

    p3.setX(MathUtility::Math::alea(0.0, longeur));
    p3.setY(orientation3*MathUtility::Math::alea(0.0, largeur));
    p3.setZ(0);

    p4.setX(longeur);
    p4.setY(orientation4*largeur);
    p4.setZ(0);

    calcBezier courbe(p1,p2,p3,p4, longeur/10);
    MeshBase::Mesh a =  m_parent->terminalSymbol("Rue")->symbol({p1.getX(), p1.getY(), p1.getZ(),
                                                                   p2.getX(), p2.getY(), p2.getZ(),
                                                                   p3.getX(), p3.getY(), p3.getZ(),
                                                                   p4.getX(), p4.getY(), p4.getZ(), longeur/10.0});
    QVector<Geometry::Point3D> tab = courbe.tabPoints();
    for(int i = 0; i < tab.size(); i ++)
    {
        if(i%3 == 0)
        {
            double angle = MathUtility::Math::alea(0,180);
            int o = MathUtility::Math::alea(0,2);
            MeshBase::Mesh r, t;
            Triplet tr(tab[i]);
            QString id;

            switch (MathUtility::Math::alea(0,3))
            {
            case 0: //Batiment
                t = batiment(id);
                a.addAssoc(id, t, tr);
                break;
            case 1: //Rue
                if(o == 0)
                {
                    o = -1;
                }
                r = m_parent->productionRule("Rue")->productionRules({tab[i].getX(), tab[i].getY(), tab[i].getZ()});
                r.rotation(0,0,o*angle);
                a += r;
                break;
            }
        }
        else
        {
            MeshBase::Mesh t;
            Triplet tr(tab[i]);
            QString id;

            t = batiment(id);
            a.addAssoc(id, t, tr);
        }
    }

    return a;
}

RueNT* RueNT::clone(LSystem::Grammar<MeshBase::Mesh> * parent) const
{
    RueNT* ret = new RueNT(*this);
    ret->m_parent = parent;
    return ret;
}

MeshBase::Mesh RueNT::batiment(QString& nom)
{
    MeshBase::Mesh ret;

    switch(MathUtility::Math::alea(0,3))
    {
    case 0:
        nom = "Immeuble";
        ret = m_parent->terminalSymbol("Immeuble")->symbol({0.0,0.0,0.0});
        break;
    case 1:
        nom = "Maison";
        ret = m_parent->terminalSymbol("Maison")->symbol({0.0,0.0,0.0});
        break;
    case 2:
        nom = "Autre";
        ret = m_parent->terminalSymbol("Autre")->symbol({0.0,0.0,0.0});
        break;
    }

    return ret;
}
