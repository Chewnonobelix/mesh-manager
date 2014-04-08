#include "generateur.h"
#include "meshfactory.h"

#include <cmath>
#include <iostream>

Generateur::Generateur()
{
}

Mesh Generateur::generateurAlumette ()
{
    Mesh m = MeshFactory::sphere(5);
    m.redimensionner(0.8,0.8,1.2);
    m.redimensionner(0.1, 0.1,0.1);
    Mesh m2 = MeshFactory::cylindre(9,1,4);
    m2.rotation(3, 45);
    m2.redimensionner(0.1, 0.1,0.1);
    return Mesh::concatenation(m, m2, 0.95);
}

Mesh Generateur::generateurAlumette (int i)
{
    Mesh m = MeshFactory::sphere(4);
    m.redimensionner(0.8,0.8,1.2);
    m.redimensionner(0.1, 0.1,0.1);
    Mesh m2 = MeshFactory::cylindre(9,1,4);
    m2.rotation(3, 45);
    m2.redimensionner(0.1, 0.1,0.1);
    return Mesh::concatenation(m, m2, 0.95);
}

Mesh Generateur::generateurColonne ()
{
    Mesh m = MeshFactory::cone();
    Mesh mC = MeshFactory::cone();
    mC.rotation(0, 180);
    //Mesh m2 = Mesh::cylinder(9.9,1,32);
    Mesh m2 = MeshFactory::cylindreComplexe(9.9,1,360);

    Mesh r = Mesh::concatenation(m, m2, -0.01);
    Mesh r2 = Mesh::concatenation(mC, r, 1.01);
    r2.redimensionner(0.1,0.1, 0.1);
    return r2;
}

Mesh Generateur::generateurDalle (double taille)
{
    Mesh cube = MeshFactory::cube();
    cube.redimensionner(taille,taille,taille/10);
    cube.normaliseMesh();
    return cube;
}

Mesh Generateur::generateurBaseColonnes (double taille)
{
    int nb_Col = 5;

    Mesh colone = generateurColonne();
    Mesh meshTerrain = generateurDalle(taille);
    //meshTerrain.translation(taille/2, taille/2, 0);
    for ( int  i = 0 ; i < nb_Col +1 ; i++ )
    {
        Mesh coloneA = colone.copie();
        coloneA.redimensionner(taille/2,taille/2,taille/2);
        coloneA.translation(0,0,( -taille / 2 ));
        coloneA.translation(( -taille / 4 ) + i * ( taille/nb_Col ) /2, ( - taille ) /4,0);


        Mesh coloneB = colone.copie();
        coloneB.redimensionner(taille/2,taille/2,taille/2);
        coloneB.translation(0,0,( -taille / 2 ));
        coloneB.translation(( - taille / 4 ) + i * ( taille/nb_Col ) /2, (  taille ) /4,0);

        meshTerrain += coloneA;
        meshTerrain += coloneB;
    }

    Mesh meshToiture = generateurDalle(taille * 1.1);
    meshToiture.redimensionner(1,1,0.1);
    meshToiture.translation(0,0, - taille /2 - taille /100);

    meshTerrain += meshToiture;

    return meshTerrain;
}

 Mesh Generateur::generateurCoque (double taille)
 {
     Mesh coque;
     for (int i = 0 ; i < taille ; i ++)
     {
         Mesh nouvellePartie;
         for ( int j = 0 ; j < taille/5 ; j ++)
         {
             if ( j == 0)
             {
                 Mesh nouvelleAlummette = Generateur::generateurAlumette(1);
                 nouvellePartie += nouvelleAlummette;
             }
             else
             {
                 Mesh nouvelleAlummetteGauche = Generateur::generateurAlumette(1);
                 Mesh nouvelleAlummetteDroite = Generateur::generateurAlumette(1);
                 nouvelleAlummetteGauche.translation(0.005*j*j,0.01*j*j,0);
                 nouvelleAlummetteDroite.translation(-0.005*j*j,0.01*j*j ,0);
                 nouvellePartie += nouvelleAlummetteGauche;
                 nouvellePartie += nouvelleAlummetteDroite;
             }
         }
         coque = Mesh::concatenation(nouvellePartie,coque,1);
     }


     return coque;
 }

 Mesh Generateur::planGouteEau ( double precision )
 {
    Mesh a = MeshFactory::planComplexe(precision);
    a.redimensionner(10,10,1);
    a.translation(-5,-5,0);

    for (int i = 0 ; i < a.m_tabPoint.size() ; i ++)
    {
        double z = sin ( sqrt(a.m_tabPoint[i].getX()*a.m_tabPoint[i].getX() + a.m_tabPoint[i].getY()*a.m_tabPoint[i].getY()))
                / sqrt ( 1 + a.m_tabPoint[i].getX()*a.m_tabPoint[i].getX()+a.m_tabPoint[i].getY()*a.m_tabPoint[i].getY());
        a.m_tabPoint[i] = Point3D(a.m_tabPoint[i].getX(), a.m_tabPoint[i].getY(),z);
        a.m_tabNorme[i] = Vector(a.m_tabNorme[i][0], a.m_tabNorme[i][1],z);
    }
    return a;
 }

 Mesh Generateur::cylindreComplexe (double longueur, double rayon, double precision)
 {
     Mesh a;
//     /*double */rayon = diametre/2;
     double ratio = (2 * 3.14116) / precision;

     // Points sur l'axe
     a.m_tabPoint.push_back(Point3D(0,0,0));
     a.m_tabPoint.push_back(Point3D(0,0,longueur));

     // Points de base pour faire fonctionner l'algorithme
     a.m_tabPoint.push_back(Point3D(rayon,0,0));
     a.m_tabPoint.push_back(Point3D(rayon,0,longueur));

     // Normales de bases
     a.m_tabNorme.push_back(Vector(0,0,0));
     a.m_tabNorme.push_back(Vector(0,0,longueur));
     a.m_tabNorme.push_back(Vector(rayon,0,0));
     a.m_tabNorme.push_back(Vector(rayon,0,longueur));

     for (int i = 1 ; i <= precision ; i++){
         // IdP1 = 2 * ( i + 1)
         // IdP2 = 2 * ( i + 1) + 1
         double angle = i * ( ratio);
         double x = rayon * cos ( angle);
         double y = rayon * sin ( angle);

         // Bas
         a.m_tabPoint.push_back(Point3D(x,y,0));
         a.m_tabNorme.push_back(Vector(x,y,0));

         //Haut
         a.m_tabPoint.push_back(Point3D(x,y,longueur));
         a.m_tabNorme.push_back(Vector(x,y,longueur));

         // Triangle Bas
         a.m_tabTopologie.push_back(0);
         a.m_tabTopologie.push_back(1);//Normale
         a.m_tabTopologie.push_back(a.m_tabPoint.size()-2);
         a.m_tabTopologie.push_back(a.m_tabNorme.size()-2);//Normale
         a.m_tabTopologie.push_back(a.m_tabPoint.size()-4);
         a.m_tabTopologie.push_back(a.m_tabNorme.size()-4);//Normale


         // Triangle Haut
         a.m_tabTopologie.push_back(1);
         a.m_tabTopologie.push_back(0);//Normale
         a.m_tabTopologie.push_back(a.m_tabPoint.size()-1);
         a.m_tabTopologie.push_back(a.m_tabNorme.size()-1);//Normale
         a.m_tabTopologie.push_back(a.m_tabPoint.size()-3);
         a.m_tabTopologie.push_back(a.m_tabNorme.size()-3);//Normale


         /**
          * // Triangle Corps 1 ( base bas )*/
         a.m_tabTopologie.push_back(a.m_tabPoint.size()-2);
         a.m_tabTopologie.push_back(a.m_tabNorme.size()-2);//Normale
         a.m_tabTopologie.push_back(a.m_tabPoint.size()-4);
         a.m_tabTopologie.push_back(a.m_tabNorme.size()-4);//Normale
         a.m_tabTopologie.push_back(a.m_tabPoint.size()-1);
         a.m_tabTopologie.push_back(a.m_tabNorme.size()-1);//Normale


         // Triangle Corps 2 ( base haut)
         a.m_tabTopologie.push_back(a.m_tabPoint.size()-1);
         a.m_tabTopologie.push_back(a.m_tabNorme.size()-1);//Normale
         a.m_tabTopologie.push_back(a.m_tabPoint.size()-3);
         a.m_tabTopologie.push_back(a.m_tabNorme.size()-3);//Normale
         a.m_tabTopologie.push_back(a.m_tabPoint.size()-4);
         a.m_tabTopologie.push_back(a.m_tabNorme.size()-4);//Normale

     }
     return a;
 }

 Mesh Generateur::maisonSimple ( double tailleMax)
{
    double hauteur = 1.0 + tailleMax* (((double)(rand()%10)) / 10.0);
    double largeur = 1.0 + tailleMax *(((double)(rand()%10)) / 10.0);
    double longueur= 1.0 + tailleMax *(((double)(rand()%10)) / 10.0);
    Mesh maison = MeshFactory::rectangleComplexe(12,1,1 );
    maison.rotation(1,90);
    maison.redimensionner(longueur, largeur, hauteur);
    //maison.translation(1,1, - hauteur/2 );
    Mesh toit = Generateur::toitSimpleFez();
    toit.redimensionner(longueur,largeur,1);
    toit.translation(longueur/2,largeur/2, - hauteur - 1);

    maison = Mesh::concatenation(toit,maison, 1);

    /*while (maison.) {

    }*/

    return maison;
}


Mesh Generateur::generateurTemple ( double taille )
{

    Mesh temple = Generateur::generateurBaseColonnes(taille);
    std::cout <<"colonesBases passée"<<std::endl;


    Mesh meshToiture = generateurDalle(taille);
    meshToiture.redimensionner(1,1,0.1);
    double valTranslate = - temple.getMaxZ() ;
    meshToiture.translation(0,0, valTranslate );
    temple += meshToiture;
        std::cout <<"oiture passée"<<std::endl;
    Mesh pentadre = Generateur::pentaedrePyramidal();
    pentadre.translation(-0.5,-0.5,0);
    pentadre.rotation(0,180);
    pentadre.redimensionner(taille/10, taille, taille/10 );
    pentadre.translation(taille/20,taille/2, valTranslate );
    temple += pentadre;

    std::cout <<"pentaedre passée"<<std::endl;

    double angle =9.4;

    Mesh tuiles = Generateur::generateurPlanOnduleeTuile();
    tuiles.redimensionner(taille, taille/2,1);
    Mesh tuile2 = tuiles;
    tuile2.rotation(0,angle);
    tuile2.translation(0,taille/2 + 0.035,-temple.getMaxZ() + 0.087);
    tuile2.redimensionner(0.8, 1,1);
    tuile2.translation(taille/10, 0,0);
    temple += tuile2;

    std::cout <<"tuiles passée"<<std::endl;

    Mesh cylindreArrond = MeshFactory::cylindre(taille*0.99,taille/45, 32);
    cylindreArrond.rotation(1,90);
    cylindreArrond.translation(0.005,taille/2 , - temple.getMaxZ()+ taille/85);
    temple += cylindreArrond;
    std::cout <<"cylindre passée"<<std::endl;



    Mesh cylindreArrondBord = MeshFactory::cylindre(taille,taille/45, 32);
    cylindreArrondBord.rotation(1,90);
    cylindreArrondBord.translation(0,0 , - taille/2);
    temple += cylindreArrondBord;
    cylindreArrondBord.translation(0,taille, 0);
    temple += cylindreArrondBord;

    tuiles.rotation(0,-angle);
    tuiles.translation(0,0,-temple.getMaxZ() + 0.5);
    tuiles.redimensionner(0.8, 1,1);
    tuiles.translation(taille/10, 0,0);
    temple += tuiles;


    pentadre.translation(taille -taille/10,0, 0 );
    temple += pentadre;

    return temple;
}


Mesh Generateur::pentaedrePyramidal ()
{
    Mesh forme;

    forme.m_tabPoint.push_back(Point3D(0,0,0));
    forme.m_tabPoint.push_back(Point3D(0,1,0));
    forme.m_tabPoint.push_back(Point3D(1,0,0));
    forme.m_tabPoint.push_back(Point3D(1,1,0));
    forme.m_tabPoint.push_back(Point3D(0,0.5,1));
    forme.m_tabPoint.push_back(Point3D(1,0.5,1));

    forme.m_tabNorme.push_back(Vector(0,0,1));
    forme.m_tabNorme.push_back(Vector(0,0,-1));
    forme.m_tabNorme.push_back(Vector(0,1,0));
    forme.m_tabNorme.push_back(Vector(0,-1,0));
    forme.m_tabNorme.push_back(Vector(1,0,0));
    forme.m_tabNorme.push_back(Vector(-1,0,0));

    // face A
    forme.m_tabTopologie.push_back(0);
    forme.m_tabTopologie.push_back(5);
    forme.m_tabTopologie.push_back(1);
    forme.m_tabTopologie.push_back(5);
    forme.m_tabTopologie.push_back(4);
    forme.m_tabTopologie.push_back(5);

    // Face b
    forme.m_tabTopologie.push_back(2);
    forme.m_tabTopologie.push_back(4);
    forme.m_tabTopologie.push_back(3);
    forme.m_tabTopologie.push_back(4);
    forme.m_tabTopologie.push_back(5);
    forme.m_tabTopologie.push_back(4);

    // Face c
    forme.m_tabTopologie.push_back(0);
    forme.m_tabTopologie.push_back(1);
    forme.m_tabTopologie.push_back(1);
    forme.m_tabTopologie.push_back(1);
    forme.m_tabTopologie.push_back(3);
    forme.m_tabTopologie.push_back(1);

    //Face d
    forme.m_tabTopologie.push_back(0);
    forme.m_tabTopologie.push_back(1);
    forme.m_tabTopologie.push_back(3);
    forme.m_tabTopologie.push_back(1);
    forme.m_tabTopologie.push_back(2);
    forme.m_tabTopologie.push_back(1);


    //Face e
    forme.m_tabTopologie.push_back(0);
    forme.m_tabTopologie.push_back(3);
    forme.m_tabTopologie.push_back(2);
    forme.m_tabTopologie.push_back(3);
    forme.m_tabTopologie.push_back(4);
    forme.m_tabTopologie.push_back(3);

    //Face f
    forme.m_tabTopologie.push_back(2);
    forme.m_tabTopologie.push_back(3);
    forme.m_tabTopologie.push_back(5);
    forme.m_tabTopologie.push_back(3);
    forme.m_tabTopologie.push_back(4);
    forme.m_tabTopologie.push_back(3);



    //Face g
    forme.m_tabTopologie.push_back(1);
    forme.m_tabTopologie.push_back(3);
    forme.m_tabTopologie.push_back(3);
    forme.m_tabTopologie.push_back(3);
    forme.m_tabTopologie.push_back(4);
    forme.m_tabTopologie.push_back(3);

    //Face h
    forme.m_tabTopologie.push_back(4);
    forme.m_tabTopologie.push_back(3);
    forme.m_tabTopologie.push_back(3);
    forme.m_tabTopologie.push_back(3);
    forme.m_tabTopologie.push_back(5);
    forme.m_tabTopologie.push_back(3);

    return forme;
}

Mesh Generateur::generateurPlanOnduleeTuile()
{
    int precision = 128;
    Mesh plan = MeshFactory::planComplexe(precision);
    for (int i = 0 ; i < plan.m_tabPoint.size() ; i+=(precision+1))
    {
        double dist = i * precision;
        double elevation = sin ( dist * precision ) / 50;
        for (int j = 1 ; j <= precision ; j ++)
        {
            plan.m_tabPoint[i+j].setZ(elevation);
        }
    }

    plan.normaliseMesh();
    return plan;
}

Mesh Generateur::generateurColoneStyle()
{
    Mesh rectangle= MeshFactory::rectangleComplexe(10,10,1);
    Mesh rectangle1= MeshFactory::rectangleComplexe(10,10,1);
    rectangle.translation(-0.5,-0.5,-5);
    rectangle1.translation(-0.5,-0.5,-5);

//    TransformationBarr::taperingY(rectangle,-5,5,0,1);
//    TransformationBarr::taperingY(rectangle1,-5,5,0,1);

//    Mesh cylindre1 = MeshFactory::cylindreComplexe(20,1,10,20,1);
//    Mesh cylindre2 = MeshFactory::cylindreComplexe(20,1,10,20,1);

//    cylindre1.translation(0,0,-10);
//    cylindre2.translation(0,0,-10);

//    TransformationBarr::twistingY(rectangle,20);
//    TransformationBarr::twistingY(rectangle1,20);

    rectangle.translation(0,10,0);
    rectangle1.translation(0,-10,0);

//    cylindre1.translation(0,-3,0);
//    cylindre2.translation(0,3,0);

//    cylindre1.rotation(0,90);
//    cylindre2.rotation(0,90);

    rectangle += rectangle1;
//    rectangle += cylindre1;
//    rectangle += cylindre2;

    return rectangle;
}


Mesh Generateur::generateurGemeau()
{
    Mesh rectangle= MeshFactory::rectangleComplexe(10,10,1);
    Mesh rectangle1= MeshFactory::rectangleComplexe(10,10,1);
    rectangle.translation(-0.5,-0.5,-5);
    rectangle1.translation(-0.5,-0.5,-5);

//    TransformationBarr::taperingY(rectangle,-5,5,0,1);
//    TransformationBarr::taperingY(rectangle1,-5,5,0,1);

//    Mesh cylindre1 = Mesh::cylindreComplexe(20,1,10,20,1);
//    Mesh cylindre2 = Mesh::cylindreComplexe(20,1,10,20,1);

//    cylindre1.translation(0,0,-10);
//    cylindre2.translation(0,0,-10);

//    TransformationBarr::twistingZ(cylindre1,20);
//    TransformationBarr::twistingZ(cylindre2,20);


    rectangle.translation(0,10,0);
    rectangle1.translation(0,-10,0);

//    cylindre1.translation(0,-3,0);
//    cylindre2.translation(0,3,0);

//    cylindre1.rotation(0,90);
//    cylindre2.rotation(0,90);

    rectangle += rectangle1;
//    rectangle += cylindre1;
//    rectangle += cylindre2;

    return rectangle;
}

Mesh Generateur::toitSimpleFez()
{
    Mesh m = MeshFactory::fez(1,4,2,4);
    m.rotation(2, 45);
    //double x = sqrt(2);
    //m.translation(x,-x,-2);
    double facteur = 1.0606601717798212866012665431573;
    m.redimensionner(facteur,facteur,1);
    m.redimensionner(1.0/3.0,1.0/3.0,0.5);
    return m;
}

