
#include "../LSystem/grammar.h"
#include "../Utility/mathutils.h"
#include "../Mesh/Advance/Tree/grammartree.h"
#include "../Mesh/Base/mesh.h"
#include "../Mesh/Base/transformation.h"
#include "../Mesh/Base/meshfactory.h"
#include "../Mesh/Advance/generateur.h"
#include "../Mesh/Advance/City/citygrammar.h"

#include <QList>
#include <QDebug>
#include <QDir>
#include <QTime>

using namespace LSystem;

namespace test0
{
MeshBase::Mesh superTube()
{
    MeshBase::Mesh c1 = MeshBase::MeshFactory::cylindre(1,1,30);
    MeshBase::Mesh c2 = MeshBase::MeshFactory::cylindre(1,1,30);
    MeshBase::Mesh c3 = MeshBase::MeshFactory::cylindre(1,1,30);
    MeshBase::Mesh c4 = MeshBase::MeshFactory::cylindre(1,1,30);
    MeshBase::Mesh c5 = MeshBase::MeshFactory::cylindre(1,1,30);
    MeshBase::Mesh c6 = MeshBase::MeshFactory::cylindre(1,1,30);
    MeshBase::Mesh c7 = MeshBase::MeshFactory::cylindre(1,1,30);
    MeshBase::Mesh c8 = MeshBase::MeshFactory::cylindre(1,1,30);
    MeshBase::Mesh c9 = MeshBase::MeshFactory::cylindre(1,1,30);
    MeshBase::Mesh c10 = MeshBase::MeshFactory::cylindre(1,1,30);
    MeshBase::Mesh c11 = MeshBase::MeshFactory::cylindre(1,1,30);

    c2.translation(0,0,1);
    c3.translation(0,0,2);
    c4.translation(0,0,3);
    c5.translation(0,0,4);
    c6.translation(0,0,5);
    c7.translation(0,0,6);
    c8.translation(0,0,7);
    c9.translation(0,0,8);
    c10.translation(0,0,9);
    c11.translation(0,0,10);

    c1 += c2;
    c1 += c3;
    c1 += c4;
    c1 += c5;
    c1 += c6;
    c1 += c7;
    c1 += c8;
    c1 += c9;
    c1 += c10;
    c1 += c11;
    //    c1.redimensionner(1,1,-50);
    return c1;
}

void scriptFormeBase(QString dirName)
{
    MeshBase::Mesh cube1 = MeshBase::MeshFactory::cube(2,3,4);
    cube1.writeObj(dirName+"cube1.obj");
    qDebug()<<"Génération cube ok";
    MeshBase::Mesh s7 = MeshBase::MeshFactory::sphere(7);
    s7.writeObj(dirName+"spherep7.obj");
    qDebug()<<"Génération sphere precision 7 ok";
    MeshBase::Mesh s5 = MeshBase::MeshFactory::sphere(5);
    s5.writeObj(dirName+"spherep5.obj");
    qDebug()<<"Génération sphere precision 5 ok";
    MeshBase::Mesh s3 = MeshBase::MeshFactory::sphere(3);
    s3.writeObj(dirName+"spherep3.obj");
    qDebug()<<"Génération sphere precision 3 ok";
    MeshBase::Mesh s1 = MeshBase::MeshFactory::sphere();
    s1.writeObj(dirName+"spherep1.obj");
    qDebug()<<"Génération sphere precision 1 ok";
    MeshBase::Mesh t = MeshBase::MeshFactory::tetrahedre(1);
    t.writeObj(dirName+"tetrahedre.obj");
    qDebug()<<"Génération tetrahedre ok";
    MeshBase::Mesh cylinder1 = MeshBase::MeshFactory::cylindre();
    cylinder1.writeObj(dirName+"\\cylinder1.obj");
    qDebug()<<"Génération cylindre ok";
}

void testRotation(QString dirName)
{
    MeshBase::Mesh cx, cy, cz;
    cx = MeshBase::MeshFactory::cylindre(1,1, 30);
    cy = MeshBase::MeshFactory::cylindre(1,1, 30);
    cz = MeshBase::MeshFactory::cylindre(1,1, 30);

    cx.writeObj(dirName + "Init.obj");
    cx.rotation(90, 0, 0);
    cx.writeObj(dirName + "cx.obj");
    cy.rotation(0, 90, 0);
    cy.writeObj(dirName + "cy.obj");
    cz.rotation(0, 0, 90);
    cz.writeObj(dirName + "cz.obj");
}
void testTapering(QString dirName)
{
    MeshBase::Mesh sz = superTube();
    MeshBase::TransformationBarr::taperingZ(sz, 4,3, 8, 4);

    sz.writeObj(dirName + "taperingZ.obj");
}

void testTwist(QString dirName)
{
    MeshBase::Mesh sz = superTube();
    MeshBase::TransformationBarr::twistingZ(sz, 45, 10);

    sz.writeObj(dirName + "twistZ.obj");
}

void testMulti(QString dirname)
{
    MeshBase::Mesh m = superTube();

    MeshBase::TransformationBarr::taperingZ(m, 4,3, 8, 4);
    MeshBase::TransformationBarr::twistingZ(m, 10, 10);
    MeshBase::TransformationBarr::bendingY(m, 5, 3, 7, 0.5);
    m.writeObj(dirname + "multi1.obj");
}

void testBending(QString dirName)
{
    MeshBase::Mesh sy = superTube();
    //sy.rotation();
    MeshBase::TransformationBarr::bendingY(sy, 5, 3, 7, 0.5);

    sy.writeObj(dirName + "bendY.obj");
}

void testQuentin(QString dirName)
{
    MeshBase::Mesh temple = MeshAdvance::Generateur::generateurTemple(5);
    //    Mesh eau = Generateur::planGouteEau(100);

    //    eau.writeObj(dirName + "eau.obj");
    temple.writeObj(dirName + "temple.obj");
}

void procTest0()
{
    QDir d;
    d.mkdir("Forme_base");
    d.mkdir("Tapering");
        scriptFormeBase("Forme_base\\");
    d.mkdir("rotate");
    d.mkdir("quentin");
    d.mkdir("twist");
    d.mkdir("bending");
    d.mkdir("multi");
        testRotation("rotate\\");
    testTapering("Tapering\\");
        testQuentin("quentin\\");
    testTwist("twist\\");

    testBending("bending\\");
    testMulti("multi\\");
}
}

namespace test1
{
class R1;
class R3;
class R2;
class T1;
class T2;
class AxiomTest;

class T1: public Terminal<QList<char>>
{
public:
    T1(): Terminal("A"){}
    T1(const T1& t): Terminal(t){}

    QList<char> symbol(QVector<double>)
    {
        return QList<char>({'A'});
    }

    T1* clone(Grammar<QList<char>> *) const
    {
        return new T1;
    }
};

class T2: public Terminal<QList<char>>
{
public:
    T2(): Terminal("B"){}
    T2(const T2& t): Terminal(t){}
    QList<char> symbol(QVector<double>)
    {
        return QList<char>({'B'});
    }
    T2* clone(Grammar<QList<char>> *) const
    {
        return new T2;
    }
};

class R3: public NonTerminal<QList<char>>
{
public:
    R3(): NonTerminal("R3") {}
    R3(const R3& t): NonTerminal(t){}
    QList<char> productionRules(QVector<double> params)
    {
        switch((int)params[0])
        {
        case 0:
            return T2().symbol({0,0});
            break;

        case -1:
            return T1().symbol({0,0});
            break;
        default:
            return productionRules({params[0] - 1, 0}) + productionRules({params[0]-2,0});
        }
    }

    R3* clone(Grammar<QList<char>> *) const
    {
        return new R3;
    }

};

class R2: public NonTerminal<QList<char>>
{
    R3 r3;

public:
    R2(): NonTerminal("R2") {}
    R2(const R2& t): NonTerminal(t){}
    QList<char> productionRules(QVector<double> params)
    {
        switch((int)params[0])
        {
        case 0:
            return T1().symbol({0,0});
            break;
        case -1:
            return T2().symbol({0,0});
            break;

        default:
            return r3.productionRules({params[0] - 1, 0}) + productionRules({params[0]-2,0});

        }
    }

    R2* clone(Grammar<QList<char>> *) const
    {
        return new R2;
    }

};

class R1: public NonTerminal<QList<char>>
{
    R2 r2;
    R3 r3;

public:
    R1(): NonTerminal("R1") {}
    R1(const R1& t): NonTerminal(t){}

    QList<char> productionRules(QVector<double> params)
    {
        switch((int)params[0])
        {
        case 0:
            return T1().symbol({0,0}) + T2().symbol({0,0});
            break;
        case -1:
            return T2().symbol({0,0});
            break;

        default:
            return r3.productionRules({params[0] - 1, 0}) + r2.productionRules({params[0],0});
        }
    }

    R1* clone(Grammar<QList<char>> *) const
    {
        return new R1;
    }

};

class AxiomTest: public Axiom<QList<char>>
{
    R1 r1;
    R2 r2;
    R3 r3;

public:
    AxiomTest(): Axiom()
    {}
    AxiomTest(const AxiomTest& t): AxiomTest(t){}

    QList<char> start(QVector<double> params)
    {
        return r1.productionRules({params[0]  + 3,0 }) + r2.productionRules({params[0]  + 2,0}) + r3.productionRules({params[0]  + 3, 0}) +
                T1().symbol({0,0}) + T2().symbol({0,0});
    }

    AxiomTest* clone(Grammar<QList<char>> *) const
    {
        return new AxiomTest;
    }

};

void test1()
{
    AxiomTest t;

    qDebug()<<"1"<<t.start({1,0});
    qDebug()<<"2"<<t.start({2,0});
    qDebug()<<"4"<<t.start({4,0});
}
}

namespace test2
{
class AxiomTest2: public Axiom<QList<char>>
{
public:
    AxiomTest2(): Axiom() {}
    AxiomTest2(const AxiomTest2& a): Axiom(a) {}

    QList<char> start(QVector<double> params)
    {
        return m_parent->productionRule("R1")->productionRules({params[0]+2, 0}) +
                m_parent->terminalSymbol("D")->symbol({0,0});
    }

    AxiomTest2* clone(Grammar<QList<char> > * parent) const
    {
        AxiomTest2* janus = new AxiomTest2(*this);
        janus->m_parent = parent;
        return janus;
    }
};

class R1: public NonTerminal<QList<char>>
{
public:
    R1(): NonTerminal("R1") {}
    R1(const R1& t): NonTerminal(t){}
    QList<char> productionRules(QVector<double> params)
    {
        switch((int)params[0])
        {
        case 0:
            return m_parent->terminalSymbol("D")->symbol({0,0}) +
                    m_parent->terminalSymbol("E")->symbol({0,0})+
                    m_parent->terminalSymbol("E")->symbol({0,0});
            break;

        default:
            return m_parent->productionRule("R3")->productionRules({params[0]-1, 0}) +
                    m_parent->productionRule("R4")->productionRules({params[0]-1, 0}) +
                    m_parent->productionRule("R3")->productionRules({params[0]-1, 0});
        }
    }

    R1* clone(Grammar<QList<char> > * parent) const
    {
        R1* janus = new R1(*this);
        janus->m_parent = parent;
        return janus;
    }
};

class R2: public NonTerminal<QList<char>>
{
public:
    R2(): NonTerminal("R2") {}
    R2(const R2& t): NonTerminal(t){}
    QList<char> productionRules(QVector<double> params)
    {
        switch((int)params[0])
        {
        case 0:
            return m_parent->terminalSymbol("D")->symbol({0,0}) +
                    m_parent->terminalSymbol("F")->symbol({0,0})+
                    m_parent->terminalSymbol("E")->symbol({0,0});
            break;

        default:
            return m_parent->productionRule("R3")->productionRules({params[0]-1, 0}) +
                    m_parent->productionRule("R4")->productionRules({params[0]-1, 0}) +
                    m_parent->productionRule("R4")->productionRules({params[0]-1, 0});
        }
    }

    R2* clone(Grammar<QList<char> > * parent) const
    {
        R2* janus = new R2(*this);
        janus->m_parent = parent;
        return janus;
    }
};

class R3: public NonTerminal<QList<char>>
{
public:
    R3(): NonTerminal("R3") {}
    R3(const R3& t): NonTerminal(t){}
    QList<char> productionRules(QVector<double> params)
    {
        switch((int)params[0])
        {
        case 0:
            return m_parent->terminalSymbol("F")->symbol({0,0}) +
                    m_parent->terminalSymbol("E")->symbol({0,0});
            break;

        default:
            return m_parent->productionRule("R4")->productionRules({params[0]-1, 0}) +
                    m_parent->productionRule("R4")->productionRules({params[0]-1, 0});
        }
    }

    R3* clone(Grammar<QList<char> > * parent) const
    {
        R3* janus = new R3(*this);
        janus->m_parent = parent;
        return janus;
    }
};

class R4: public NonTerminal<QList<char>>
{
public:
    R4(): NonTerminal("R4") {}
    R4(const R4& t): NonTerminal(t){}
    QList<char> productionRules(QVector<double> params)
    {
        switch((int)params[0])
        {
        case 0:
            return m_parent->terminalSymbol("F")->symbol({0,0}) +
                    m_parent->terminalSymbol("F")->symbol({0,0})+
                    m_parent->terminalSymbol("F")->symbol({0,0});
            break;

        default:
            return m_parent->productionRule("R1")->productionRules({params[0]-1}) +
                    m_parent->productionRule("R2")->productionRules({params[0]-1}) +
                    m_parent->productionRule("R3")->productionRules({params[0]-1});
        }
    }
    R4* clone(Grammar<QList<char> > * parent) const
    {
        R4* janus = new R4(*this);
        janus->m_parent = parent;
        return janus;
    }
};

class T1: public Terminal<QList<char>>
{
public:
    T1(): Terminal("D") {}
    T1(const T1& t): Terminal(t){}
    QList<char> symbol(QVector<double>)
    {
        return QList<char>({'D'});
    }
    T1* clone(Grammar<QList<char> > * parent) const
    {
        T1* janus = new T1(*this);
        janus->m_parent = parent;
        return janus;
    }
};

class T2: public Terminal<QList<char>>
{
public:
    T2(): Terminal("E") {}
    T2(const T2& t): Terminal(t){}
    QList<char> symbol(QVector<double>)
    {
        return QList<char>({'E'});
    }
    T2* clone(Grammar<QList<char> > * parent) const
    {
        T2* janus = new T2(*this);
        janus->m_parent = parent;
        return janus;
    }

};

class T3: public Terminal<QList<char>>
{
public:
    T3(): Terminal("F") {}
    T3(const T3& t): Terminal(t){}
    QList<char> symbol(QVector<double>)
    {
        return QList<char>({'F'});
    }

    T3* clone(Grammar<QList<char> > * parent) const
    {
        T3* janus = new T3(*this);
        janus->m_parent = parent;
        return janus;
    }
};

void test2()
{
    Grammar<QList<char>> g;
    AxiomTest2 a;
    T1 t1;
    T2 t2;
    T3 t3;
    R1 r1;
    R2 r2;
    R3 r3;
    R4 r4;

    g.setAxiom(&a);
    g.addProductionRule("R1", &r1);
    g.addProductionRule("R2", &r2);
    g.addProductionRule("R3", &r3);
    g.addProductionRule("R4", &r4);
    g.addTerminalSymbol("D", &t1);
    g.addTerminalSymbol("E", &t2);
    g.addTerminalSymbol("F", &t3);
    qDebug()<<"test 1"<<g.generation({1});
    qDebug()<<"test 2"<<g.generation({2});
    qDebug()<<"test 3"<<g.generation({3});
    qDebug()<<"test 4"<<g.generation({4});
}
}

namespace testArbre1
{
void proc()
{
    GrammarTree gt;
    QVector<double> p(9);
    p[0] = 5;
    p[1] = 0.5;
    p[2] = 1;
    p[3] = true;
    p[4] = 45;
    p[5] = 30;
    p[6] = 0.3;
    p[7] = 2;
    p[8] = true;

    QTime timer;
    timer.start();
    for(int j = 0; j < 10; j ++)
    {
        QString d ("set arbre "+QString::number(j)+"/");
        QDir di;
        di.mkdir(d);
        for(int i = 0; i < 10; i++)
        {
            timer.restart();
            MeshBase::Mesh m = gt.generation(p);
            qDebug()<<"Génération de l'arbre "<<(j*10+i)<<"en"<<timer.elapsed()<<"ms";
            m.writeObj(d+"treeTest" + QString::number(i) + ".obj");
        }
    }
}
}

namespace testCity
{
    void test()
    {
        CityGrammar g;
        g.generation({0.0,0.0,0.0});
    }
}
int main (int, char**)
{
//    test0::procTest0();
//    test1::test1();
//    test2::test2();
//    testArbre1::proc();
    testCity::test();
    return 0;
}
