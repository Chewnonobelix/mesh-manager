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
    Mesh sx = superTube(), sy = superTube(), sz = superTube();
    TransformationBarr::taperingX(sx, 1,5, 9, 4);
    TransformationBarr::taperingY(sy, 3,5, 9, 4);
    TransformationBarr::taperingZ(sz, 4,3, 8, 4);

    sx.writeObj(dirName + "taperingX.obj");
    sy.writeObj(dirName + "taperingY.obj");
    sz.writeObj(dirName + "taperingZ.obj");
}

void testTwist(QString dirName)
{
    Mesh sx = superTube(), sy = superTube(), sz = superTube();
    TransformationBarr::twistingX(sx, 10, 10);
    TransformationBarr::twistingY(sy, 10, 10);
    TransformationBarr::twistingZ(sz, 45, 10);

    sx.writeObj(dirName + "twistX.obj");
    sy.writeObj(dirName + "twistY.obj");
    sz.writeObj(dirName + "twistZ.obj");
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
//    testRotation("rotate\\");
//    testTapering("Tapering\\");
//    testQuentin("quentin\\");
    testTwist("twist\\");
    return 0;
}
