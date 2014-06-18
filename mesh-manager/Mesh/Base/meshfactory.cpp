#include "meshfactory.h"

using namespace MeshBase;

MeshFactory::MeshFactory()
{
}

Mesh MeshFactory::tetrahedre(double h)
{
    Mesh t;

    double l = 2*h/sqrt(3);

    double x = sqrt((l*l) - (h*h));
    t.m_tabPoint<<Geometry::Point3D(0,0,0)<<Geometry::Point3D(l,0,0)<<Geometry::Point3D(x,h, 0)<<Geometry::Point3D(x,h/2,h);

    t.m_tabNorme<<Geometry::Vector(0,0,0)<<Geometry::Vector(l,0,0)<<Geometry::Vector(x,h, 0)<<Geometry::Vector(x,h/2,h);

    t.m_tabTopologie<<0<<0<<1<<1<<2<<2;
    t.m_tabTopologie<<0<<0<<3<<3<<2<<2;
    t.m_tabTopologie<<0<<0<<1<<1<<3<<3;
    t.m_tabTopologie<<3<<3<<1<<1<<2<<2;

    t.corrigeNormales();
    return t;
}

Mesh MeshFactory::poufCube(double grand, double petit)
{
    Mesh c = MeshFactory::cube(petit);
    double ratio = grand/petit;

    for(int i = 0; i < ceil(c.m_tabPoint.size() / 2.0); i ++)
    {
        c.m_tabPoint[i*2] *= ratio;
    }

    c.corrigeNormales();
    return c;
}

Mesh MeshFactory::fez(double grand,double petit, double h, int p)
{
    Mesh c = MeshFactory::cylindre(h,petit,p);
    double ratio = grand/petit;

    for(int i = 0; i < ceil(c.m_tabPoint.size() / 2.0); i ++)
    {
        c.m_tabPoint[i*2] *= ratio;
    }

    c.corrigeNormales();
    return c;
}

Mesh MeshFactory::rectangleComplexe ( int precision, double longueur, double largeur)
{
    Mesh rectangle;

    Mesh faceTete = MeshFactory::planComplexe(precision);
    rectangle += faceTete;

    Mesh faceQueue = faceTete.copie();
    faceQueue.translation(0,0,1);
    rectangle += faceQueue;

    Mesh facetop = faceTete.copie();
    facetop.rotation(0,90);
    rectangle += facetop;

    Mesh facetop2 = faceTete.copie();
    facetop2.rotation(0,90);
    facetop2.translation(0,1,0);
    rectangle += facetop2;

    Mesh faceCote = faceTete.copie();
    faceCote.rotation(1,-90);
    rectangle += faceCote;

    Mesh faceCote2 = faceCote.copie();
    faceCote2.translation(1,0,0);
    rectangle += faceCote2;

    rectangle.redimensionner(largeur, largeur, longueur);
    return rectangle;
}

Mesh MeshFactory::cubeComplexe ( int precision, double taille)
{
    return rectangleComplexe (precision, taille, taille );
}

Mesh MeshFactory::planComplexe ( int precision)
{
    Mesh cube;
    double dist = (double)1/ (double)precision;
    cube.m_tabPoint.reserve((precision+1)*(precision+1));

    for (int i = 0 ; i <= precision ; i ++)
    {
        for (int j = 0 ; j <= precision ; ++j )
        {
            cube.m_tabPoint.push_back(Geometry::Point3D(dist*i,j*dist,0));

            cube.m_tabNorme.push_back(Geometry::Vector(dist*i,j*dist,0));
            if ( i && j )
            {
                int tailleP = cube.m_tabPoint.size()-1;
                int tailleN = cube.m_tabNorme.size()-1;

                // Triangle Base Haut
                cube.m_tabTopologie.push_back(tailleP-1);
                cube.m_tabTopologie.push_back(tailleN-1);


                cube.m_tabTopologie.push_back(tailleP - precision -1);
                cube.m_tabTopologie.push_back(tailleN - precision -1);

                cube.m_tabTopologie.push_back(tailleP - precision -2 );
                cube.m_tabTopologie.push_back(tailleN - precision -2 );


                // Triangle Base Bas : Bon
                cube.m_tabTopologie.push_back(tailleP);
                cube.m_tabTopologie.push_back(tailleN);

                cube.m_tabTopologie.push_back(tailleP - precision -1);
                cube.m_tabTopologie.push_back(tailleN - precision -1);


                cube.m_tabTopologie.push_back(tailleP-1);
                cube.m_tabTopologie.push_back(tailleN-1);
            }
        }
    }

    return cube;
}

Mesh MeshFactory::sphere(int precision)
{
    Mesh s;

    s.m_tabPoint.push_back(Geometry::Point3D(0,0,1));
    s.m_tabPoint.push_back(Geometry::Point3D(1,0,0));
    s.m_tabPoint.push_back(Geometry::Point3D(0,1,0));
    s.m_tabPoint.push_back(Geometry::Point3D(-1,0,0));
    s.m_tabPoint.push_back(Geometry::Point3D(0,-1,0));
    s.m_tabPoint.push_back(Geometry::Point3D(0,0,-1));


    s.m_tabNorme<<Geometry::Vector(0,0,1)<<Geometry::Vector(0,0,-1)
               <<Geometry::Vector(0,1,0)<<Geometry::Vector(0,-1,0)
              <<Geometry::Vector(1,0,0)<<Geometry::Vector(-1,0,0);

    s.m_tabTopologie<<1<<4<<5<<1<<2<<2;
    s.m_tabTopologie<<2<<2<<5<<1<<3<<5;
    s.m_tabTopologie<<3<<5<<5<<1<<4<<3;
    s.m_tabTopologie<<4<<3<<5<<1<<1<<4;

    s.m_tabTopologie<<1<<4<<0<<0<<4<<3;
    s.m_tabTopologie<<4<<3<<0<<0<<3<<5;
    s.m_tabTopologie<<3<<5<<0<<0<<2<<2;
    s.m_tabTopologie<<2<<2<<0<<0<<1<<4;

    s.subDivideSpherePoint(precision);

    s.corrigeNormales();
    return s;
}

Mesh MeshFactory::demiTore(double rayon, double rTube,int precision)
{
    Mesh meshRet;
    double ratio = (2 * 3.14116) / precision;

    for (int i = 0 ; i <= precision; i++ )
    {
        // Plan 2D
        double theta = i * ( ratio);
        for ( int j = 0 ; j <= precision/2 ; j ++)
        {
            double phi = j * ( ratio);
            double x = ( rayon +rTube*cos(phi) ) * cos ( theta);
            double y = ( rayon +rTube*cos(phi) ) * sin ( theta);
            double z = rTube*sin(phi) ;

            meshRet.m_tabPoint.push_back(Geometry::Point3D(x, y, z));
            meshRet.m_tabNorme.push_back(Geometry::Vector(x, y, z));
            if (i > 0 ){
                int pos = meshRet.m_tabPoint.size()-1;
                int posN = meshRet.m_tabNorme.size()-1;

                // Triangle sens ArriÃ¨re
                meshRet.m_tabTopologie.push_back(pos);
                meshRet.m_tabTopologie.push_back(posN);

                meshRet.m_tabTopologie.push_back(pos-1);
                meshRet.m_tabTopologie.push_back(posN-1);


                meshRet.m_tabTopologie.push_back(pos - precision);
                meshRet.m_tabTopologie.push_back(posN- precision);

                //Triangle sens avant
                meshRet.m_tabTopologie.push_back(pos);
                meshRet.m_tabTopologie.push_back(posN);

                meshRet.m_tabTopologie.push_back(pos-precision + 1);
                meshRet.m_tabTopologie.push_back(posN-precision + 1);


                meshRet.m_tabTopologie.push_back(pos - precision);
                meshRet.m_tabTopologie.push_back(posN- precision);

            }
        }
    }
    return meshRet;
}

/**
  Tore
 * @brief tore
 * @return
 */
Mesh MeshFactory::tore(double rayon, double rTube,int precision)
{
    /**
     * @brief méthode : ( wikipèdia EN )
     * x(\theta, \varphi) =  (R + r \cos \varphi) \cos{\theta}
        y(\theta, \varphi) =  (R + r \cos \varphi) \sin{\theta}
        z(\theta, \varphi) =  r \sin \varphi
        where
        Î¸, Ï? are angles which make a full circle, starting at 0 and ending at 2Ï?, so that their values start and end at the same point,
        R is the distance from the center of the tube to the center of the torus,
        r is the radius of the tube
     */
    Mesh a;
    double ratio = (2 * 3.14116) / precision;

    for (int i = 0 ; i <= precision; i++ )
    {
        // Plan 2D
        double theta = i * ( ratio);
        for ( int j = 0 ; j <= precision ; j ++)
        {
            double phi = j * ( ratio);
            double x = ( rayon +rTube*cos(phi) ) * cos ( theta);
            double y = ( rayon +rTube*cos(phi) ) * sin ( theta);
            double z = rTube*sin(phi) ;

            a.m_tabPoint.push_back(Geometry::Point3D(x, y, z));
            a.m_tabNorme.push_back(Geometry::Vector(x, y, z));
            if (i > 0 ){
                int pos = a.m_tabPoint.size()-1;
                int posN = a.m_tabNorme.size()-1;

                // Triangle sens ArriÃ¨re
                a.m_tabTopologie.push_back(pos);
                a.m_tabTopologie.push_back(posN);

                a.m_tabTopologie.push_back(pos-1);
                a.m_tabTopologie.push_back(posN-1);


                a.m_tabTopologie.push_back(pos - precision);
                a.m_tabTopologie.push_back(posN- precision);

                //Triangle sens avant
                a.m_tabTopologie.push_back(pos);
                a.m_tabTopologie.push_back(posN);

                a.m_tabTopologie.push_back(pos-precision + 1);
                a.m_tabTopologie.push_back(posN-precision + 1);


                a.m_tabTopologie.push_back(pos - precision);
                a.m_tabTopologie.push_back(posN- precision);

            }
        }
    }
    //for ( int i =

    return a;
}


/** Cone taille 1
 * @brief cone
 * @return
 */
Mesh MeshFactory::cone()
{
    Mesh a;
    int taille=1, rayon = 1, precision = 64;
    double ratio = (2 * 3.14116) / precision;

    // Points sur l'axe
    a.m_tabPoint.push_back(Geometry::Point3D(0,0,0));
    a.m_tabPoint.push_back(Geometry::Point3D(0,0,taille));
    // Points de base pour faire fonctionner l'algorithme
    a.m_tabPoint.push_back(Geometry::Point3D(rayon,0,0));


    // Normales de bases
    a.m_tabNorme.push_back(Geometry::Vector(0,0,-1));
    a.m_tabNorme.push_back(Geometry::Vector(0,0,1));
    a.m_tabNorme.push_back(Geometry::Vector(rayon,0,0));


    for (int i = 1 ; i <= precision ; i++){
        // IdP1 = 2 * ( i + 1)
        // IdP2 = 2 * ( i + 1) + 1
        double angle = i * ( ratio);
        double x = rayon * cos ( angle);
        double y = rayon * sin ( angle);

        // Bas
        a.m_tabPoint.push_back(Geometry::Point3D(x,y,0));
        a.m_tabNorme.push_back(Geometry::Vector(x,y,0));
        //a.m_tabNorme.push_back(fillGeometry::Vector(a.m_tabNorme.at(0), );
        //a.m_tabNorme.at(0)

        // Triangle Bas
        a.m_tabTopologie.push_back(0);
        a.m_tabTopologie.push_back(1);//Normale
        a.m_tabTopologie.push_back(a.m_tabPoint.size()-2);
        a.m_tabTopologie.push_back(a.m_tabPoint.size()-1);//Normale
        a.m_tabTopologie.push_back(a.m_tabPoint.size()-1);
        a.m_tabTopologie.push_back(a.m_tabPoint.size()-2);//Normale



        /**
         * // Triangle Corps 1 ( base bas )*/
        a.m_tabTopologie.push_back(1);
        a.m_tabTopologie.push_back(1);//Normale
        a.m_tabTopologie.push_back(a.m_tabPoint.size()-2);
        a.m_tabTopologie.push_back(a.m_tabNorme.size()-1);//Normale
        a.m_tabTopologie.push_back(a.m_tabPoint.size()-1);
        a.m_tabTopologie.push_back(a.m_tabNorme.size()-2);//Normale
    }

    return a;
}

/**
 * @brief cylinder Créer un cylindre de longueur l et de rayon r
 * @param longueur l
 * @param rayon r
 * @param precision nombre de points sur le rayon
 * @return cylinder
 */
Mesh MeshFactory::cylindre(double longueur, double diametre, int precision)
{
    Mesh a;
    double rayon = diametre/2;
    double ratio = (2 * 3.14116) / precision;

    // Points sur l'axe
    a.m_tabPoint.push_back(Geometry::Point3D(0,0,0));
    a.m_tabPoint.push_back(Geometry::Point3D(0,0,longueur));

    // Points de base pour faire fonctionner l'algorithme
    a.m_tabPoint.push_back(Geometry::Point3D(rayon,0,0));
    a.m_tabPoint.push_back(Geometry::Point3D(rayon,0,longueur));

    for (int i = 1 ; i <= precision ; i++){
        // IdP1 = 2 * ( i + 1)
        // IdP2 = 2 * ( i + 1) + 1

        double angle = i * ( ratio);
        double x = rayon * cos ( angle);
        double y = rayon * sin ( angle);
        // Bas
        Geometry::Point3D ptBas = Geometry::Point3D(x,y,0);

        //Haut
        Geometry::Point3D ptHaut = Geometry::Point3D(x,y,longueur);

        // Bas
        a.m_tabPoint.push_back(ptBas);

        //Haut
        a.m_tabPoint.push_back(ptHaut);

        // Triangle Bas
        a.m_tabNorme.push_back(Mesh::getNormeTriangle( a.m_tabPoint[a.m_tabPoint.size()-2], a.m_tabPoint[0], a.m_tabPoint[a.m_tabPoint.size()-4] ));
        a.m_tabTopologie.push_back(0);
        a.m_tabTopologie.push_back(a.m_tabNorme.size()-1);//Normale
        a.m_tabTopologie.push_back(a.m_tabPoint.size()-2);
        a.m_tabTopologie.push_back(a.m_tabNorme.size()-1);//Normale
        a.m_tabTopologie.push_back(a.m_tabPoint.size()-4);
        a.m_tabTopologie.push_back(a.m_tabNorme.size()-1);//Normale

        // Triangle Haut
        a.m_tabNorme.push_back(Mesh::getNormeTriangle( a.m_tabPoint[a.m_tabPoint.size()-1], a.m_tabPoint[1], a.m_tabPoint[a.m_tabPoint.size()-3] ));

        a.m_tabTopologie.push_back(1);
        a.m_tabTopologie.push_back(a.m_tabNorme.size()-1);//Normale
        a.m_tabTopologie.push_back(a.m_tabPoint.size()-3);
        a.m_tabTopologie.push_back(a.m_tabNorme.size()-1);//Normale
        a.m_tabTopologie.push_back(a.m_tabPoint.size()-1);
        a.m_tabTopologie.push_back(a.m_tabNorme.size()-1);//Normale


        /**
             * // Triangle Corps 1 ( base bas )*/
        a.m_tabNorme.push_back(Mesh::getNormeTriangle(a.m_tabPoint[a.m_tabPoint.size()-2], a.m_tabPoint[a.m_tabPoint.size()-1], a.m_tabPoint[a.m_tabPoint.size()-4] ));

        a.m_tabTopologie.push_back(a.m_tabPoint.size()-4);
        a.m_tabTopologie.push_back(a.m_tabNorme.size()-1);//Normale
        a.m_tabTopologie.push_back(a.m_tabPoint.size()-2);
        a.m_tabTopologie.push_back(a.m_tabNorme.size()-1);//Normale
        a.m_tabTopologie.push_back(a.m_tabPoint.size()-1);
        a.m_tabTopologie.push_back(a.m_tabNorme.size()-1);//Normale

        // Triangle Corps 2 ( base haut)
        a.m_tabNorme.push_back(Mesh::getNormeTriangle(a.m_tabPoint[a.m_tabPoint.size()-3], a.m_tabPoint[a.m_tabPoint.size()-1], a.m_tabPoint[a.m_tabPoint.size()-4] ));

        a.m_tabTopologie.push_back(a.m_tabPoint.size()-1);
        a.m_tabTopologie.push_back(a.m_tabNorme.size()-1);//Normale
        a.m_tabTopologie.push_back(a.m_tabPoint.size()-3);
        a.m_tabTopologie.push_back(a.m_tabNorme.size()-1);//Normale
        a.m_tabTopologie.push_back(a.m_tabPoint.size()-4);
        a.m_tabTopologie.push_back(a.m_tabNorme.size()-1);//Normale
    }
    return a;
}

/** Cylindre taille 1
 * @brief cylinder
 * @return
 */
Mesh MeshFactory::cylindre()
{
    Mesh m = MeshFactory::cylindre(1,1,64);
//    m.redimensionner(0.25,0.25,0.25);
    return m;
}

/**
  Cube taille 1
 * @brief cube
 * @param size
 * @return
 */
Mesh MeshFactory::cube(int size)
{

    Mesh cube = cylindre(size,size,4);
    cube.rotation(3, 45);
    return cube;
}


/** Power cube par quentin (  créer à partir d'un cylindre )
 * @brief cube
 * @return
 */
Mesh MeshFactory::cube()
{
    Mesh cube = MeshFactory::cube(1);
    return cube;
}

Mesh MeshFactory::cube(double sizeX, double sizeY, double sizeZ)
{
    Mesh c;

    //Center the cube
    sizeX /= 2;
    sizeY /= 2;
    sizeZ /= 2;


    c.m_tabPoint.push_back(Geometry::Point3D(-sizeX,-sizeY,-sizeZ));
    c.m_tabPoint.push_back(Geometry::Point3D(-sizeX,-sizeY,sizeZ));
    c.m_tabPoint.push_back(Geometry::Point3D(-sizeX,sizeY,-sizeZ));
    c.m_tabPoint.push_back(Geometry::Point3D(-sizeX,sizeY,sizeZ));
    c.m_tabPoint.push_back(Geometry::Point3D(sizeX,-sizeY,-sizeZ));
    c.m_tabPoint.push_back(Geometry::Point3D(sizeX,-sizeY,sizeZ));
    c.m_tabPoint.push_back(Geometry::Point3D(sizeX,sizeY,-sizeZ));
    c.m_tabPoint.push_back(Geometry::Point3D(sizeX,sizeY,sizeZ));

    c.m_tabNorme.push_back(Geometry::Vector(0,0,1));
    c.m_tabNorme.push_back(Geometry::Vector(0,0,-1));
    c.m_tabNorme.push_back(Geometry::Vector(0,1,0));
    c.m_tabNorme.push_back(Geometry::Vector(0,-1,0));
    c.m_tabNorme.push_back(Geometry::Vector(1,0,0));
    c.m_tabNorme.push_back(Geometry::Vector(-1,0,0));

    c.m_tabTopologie.push_back(0);
    c.m_tabTopologie.push_back(1);
    c.m_tabTopologie.push_back(6);
    c.m_tabTopologie.push_back(1);
    c.m_tabTopologie.push_back(4);
    c.m_tabTopologie.push_back(1);

    c.m_tabTopologie.push_back(0);
    c.m_tabTopologie.push_back(1);
    c.m_tabTopologie.push_back(2);
    c.m_tabTopologie.push_back(1);
    c.m_tabTopologie.push_back(6);
    c.m_tabTopologie.push_back(1);

    c.m_tabTopologie.push_back(0);
    c.m_tabTopologie.push_back(5);
    c.m_tabTopologie.push_back(3);
    c.m_tabTopologie.push_back(5);
    c.m_tabTopologie.push_back(2);
    c.m_tabTopologie.push_back(5);

    c.m_tabTopologie.push_back(0);
    c.m_tabTopologie.push_back(5);
    c.m_tabTopologie.push_back(1);
    c.m_tabTopologie.push_back(5);
    c.m_tabTopologie.push_back(3);
    c.m_tabTopologie.push_back(5);

    c.m_tabTopologie.push_back(2);
    c.m_tabTopologie.push_back(2);
    c.m_tabTopologie.push_back(7);
    c.m_tabTopologie.push_back(2);
    c.m_tabTopologie.push_back(6);
    c.m_tabTopologie.push_back(2);

    c.m_tabTopologie.push_back(2);
    c.m_tabTopologie.push_back(2);
    c.m_tabTopologie.push_back(3);
    c.m_tabTopologie.push_back(2);
    c.m_tabTopologie.push_back(7);
    c.m_tabTopologie.push_back(2);

    c.m_tabTopologie.push_back(4);
    c.m_tabTopologie.push_back(4);
    c.m_tabTopologie.push_back(6);
    c.m_tabTopologie.push_back(4);
    c.m_tabTopologie.push_back(7);
    c.m_tabTopologie.push_back(4);

    c.m_tabTopologie.push_back(4);
    c.m_tabTopologie.push_back(4);
    c.m_tabTopologie.push_back(7);
    c.m_tabTopologie.push_back(4);
    c.m_tabTopologie.push_back(5);
    c.m_tabTopologie.push_back(4);

    c.m_tabTopologie.push_back(0);
    c.m_tabTopologie.push_back(3);
    c.m_tabTopologie.push_back(4);
    c.m_tabTopologie.push_back(3);
    c.m_tabTopologie.push_back(5);
    c.m_tabTopologie.push_back(3);

    c.m_tabTopologie.push_back(0);
    c.m_tabTopologie.push_back(3);
    c.m_tabTopologie.push_back(5);
    c.m_tabTopologie.push_back(3);
    c.m_tabTopologie.push_back(1);
    c.m_tabTopologie.push_back(3);

    c.m_tabTopologie.push_back(1);
    c.m_tabTopologie.push_back(0);
    c.m_tabTopologie.push_back(5);
    c.m_tabTopologie.push_back(0);
    c.m_tabTopologie.push_back(7);
    c.m_tabTopologie.push_back(0);

    c.m_tabTopologie.push_back(1);
    c.m_tabTopologie.push_back(0);
    c.m_tabTopologie.push_back(7);
    c.m_tabTopologie.push_back(0);
    c.m_tabTopologie.push_back(3);
    c.m_tabTopologie.push_back(0);

    return c;
}

Mesh MeshFactory::cylindreComplexe(double longueur, double rayon, int precision)
{
    Mesh c = cylindre( longueur, rayon, precision);
    for (int i = 4 ; i < c.m_tabPoint.size(); i+=2)
    {
        double changement = 1 + ( rayon * 0.005 ) * sin(i/4);
        c.m_tabPoint[i]= Geometry::Point3D(c.m_tabPoint[i].getX()* changement, c.m_tabPoint[i].getY()* changement, c.m_tabPoint[i].getZ() );
        c.m_tabPoint[i+1]= Geometry::Point3D(c.m_tabPoint[i+1].getX() *changement, c.m_tabPoint[i+1].getY() * changement, c.m_tabPoint[i+1].getZ() );
        c.m_tabNorme[i]= Geometry::Vector(c.m_tabNorme[i][0]* changement, c.m_tabNorme[i][1]* changement, c.m_tabNorme[i][2] );
        c.m_tabNorme[i+1]= Geometry::Vector(c.m_tabNorme[i+1][0] *changement, c.m_tabNorme[i+1][1] * changement, c.m_tabNorme[i+1][2] );
    }
    return c;
}

/**
  Sphére
 * @brief sphere
 * @return
 */

Mesh MeshFactory::sphereTore(int i)
{
    return tore(0, i,16);
}
