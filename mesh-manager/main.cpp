#include <QCoreApplication>
#include <iostream>
#include <QDir>
#include "generateur.h"
#include "meshfactory.h"
#include "transformation.h"

Mesh superTube()
{
    Mesh c1 = MeshFactory::cylindre(1,1,30);
        Mesh c2 = MeshFactory::cylindre(1,1,30);
        Mesh c3 = MeshFactory::cylindre(1,1,30);
        Mesh c4 = MeshFactory::cylindre(1,1,30);
        Mesh c5 = MeshFactory::cylindre(1,1,30);
        Mesh c6 = MeshFactory::cylindre(1,1,30);
        Mesh c7 = MeshFactory::cylindre(1,1,30);
        Mesh c8 = MeshFactory::cylindre(1,1,30);
        Mesh c9 = MeshFactory::cylindre(1,1,30);
        Mesh c10 = MeshFactory::cylindre(1,1,30);
        Mesh c11 = MeshFactory::cylindre(1,1,30);

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
    Mesh cube1 = MeshFactory::cube(2,3,4);
    cube1.writeObj(dirName+"cube1.obj");
    qDebug()<<"Génération cube ok";
    Mesh s7 = MeshFactory::sphere(7);
    s7.writeObj(dirName+"spherep7.obj");
    qDebug()<<"Génération sphere precision 7 ok";
    Mesh s5 = MeshFactory::sphere(5);
    s5.writeObj(dirName+"spherep5.obj");
    qDebug()<<"Génération sphere precision 5 ok";
    Mesh s3 = MeshFactory::sphere(3);
    s3.writeObj(dirName+"spherep3.obj");
    qDebug()<<"Génération sphere precision 3 ok";
    Mesh s1 = MeshFactory::sphere();
    s1.writeObj(dirName+"spherep1.obj");
    qDebug()<<"Génération sphere precision 1 ok";
    Mesh t = MeshFactory::tetrahedre(1);
    t.writeObj(dirName+"tetrahedre.obj");
    qDebug()<<"Génération tetrahedre ok";
    Mesh cylinder1 = MeshFactory::cylindre();
    cylinder1.writeObj(dirName+"\\cylinder1.obj");
    qDebug()<<"Génération cylindre ok";
}

void testRotation(QString dirName)
{
    Mesh cx, cy, cz;
    cx = MeshFactory::cylindre(1,1, 30);
    cy = MeshFactory::cylindre(1,1, 30);
    cz = MeshFactory::cylindre(1,1, 30);

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
    Mesh sz = superTube();
    TransformationBarr::taperingZ(sz, 4,3, 8, 4);

    sz.writeObj(dirName + "taperingZ.obj");
}

void testTwist(QString dirName)
{
    Mesh sz = superTube();
    TransformationBarr::twistingZ(sz, 45, 10);

    sz.writeObj(dirName + "twistZ.obj");
}

void testMulti(QString dirname)
{
    Mesh m = superTube();

    TransformationBarr::taperingZ(m, 4,3, 8, 4);
    TransformationBarr::twistingZ(m, 10, 10);
    TransformationBarr::bendingY(m, 5, 3, 7, 0.5);
    m.writeObj(dirname + "multi1.obj");
}

void testBending(QString dirName)
{
    Mesh sy = superTube();
    //sy.rotation();
    TransformationBarr::bendingY(sy, 5, 3, 7, 0.5);

    sy.writeObj(dirName + "bendY.obj");
}

void testQuentin(QString dirName)
{
    Mesh temple = Generateur::generateurTemple(5);
//    Mesh eau = Generateur::planGouteEau(100);

//    eau.writeObj(dirName + "eau.obj");
    temple.writeObj(dirName + "temple.obj");
}

int main(int argc, char *argv[])
{
    QDir d;
    d.mkdir("Forme_base");
    d.mkdir("Tapering");
//    scriptFormeBase("Forme_base\\");
    d.mkdir("rotate");
    d.mkdir("quentin");
    d.mkdir("twist");
    d.mkdir("bending");
    d.mkdir("multi");
//    testRotation("rotate\\");
    testTapering("Tapering\\");
//    testQuentin("quentin\\");
    testTwist("twist\\");

    testBending("bending\\");
    testMulti("multi\\");
    return 0;
}
