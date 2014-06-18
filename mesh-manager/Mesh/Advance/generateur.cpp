#include "generateur.h"
#include "../Base/meshfactory.h"
#include "../../Utility/calcbezier.h"
#include "../../Utility/point3d.h"

#include <cmath>
#include <iostream>

using namespace MeshAdvance;

Generateur::Generateur()
{
}


MeshBase::Mesh Generateur::creerRoute(Geometry::Point3D p0, Geometry::Point3D p1, Geometry::Point3D p2, Geometry::Point3D p3, double nbpts, double largeur)
{
    MeshBase::Mesh ret;
    Geometry::Point3D p00,p11,p22,p33;
    calcBezier::calculeOrthogonal(p0,p1,p2,p3,p00,p11,p22,p33, largeur);

    QVector <Geometry::Point3D> partieBasse;
    QVector <Geometry::Point3D> partieHaute;

    calcBezier c (p0,p1,p2,p3,nbpts);
    calcBezier c2 (p00,p11,p22,p33,nbpts);

    partieBasse = c.tabPoints();
    partieHaute = c2.tabPoints();

    ret.m_tabPoint.reserve(partieBasse.size()*2);
    for (int i = 0 ; i < partieBasse.size(); i++)
    {
        Geometry::Point3D a(partieBasse[i].getX(),partieBasse[i].getY(), 0);
        Geometry::Point3D b(partieHaute[i].getX(),partieHaute[i].getY(), 0);

        ret.m_tabPoint << a << b;
        ret.m_tabNorme << a.toVector() << b.toVector();

        if ( i >0 )
        {
            int taille = ret.m_tabPoint.size()-1;
            int tn = ret.m_tabNorme.size()-1;
            ret.m_tabTopologie << taille -2 << tn-2 << taille -1 << tn-1 << taille-3 << tn-3;
            ret.m_tabTopologie << taille -2 << tn-2 << taille << tn << taille-1 << tn-1;
        }
    }



    return ret;
}


MeshBase::Mesh Generateur::terraforme(MeshBase::Mesh &route, MeshBase::Mesh &terrain, double tailleRouteIN)
{
    MeshBase::Mesh m;
    double tailleRoute = tailleRouteIN ;
    m.m_tabPoint.reserve(terrain.m_tabPoint.size());
    m.m_tabTopologie = terrain.m_tabTopologie;
    m.m_tabNorme = terrain.m_tabNorme;

    double xmmin, xmax,ymin,ymax;
    MeshBase::Mesh::mensurationMesh(route, xmmin, xmax,ymin,ymax);

    for (Geometry::Point3D p : terrain.m_tabPoint )
    {
        double z=p.getZ();
        // Si on est dans le volume englobant la route
        if ( p.getX() < xmax + tailleRoute *2 && p.getX() > xmmin - tailleRoute *2 && p.getY() < ymax+ tailleRoute *2 && p.getY() > ymin - tailleRoute *2)
        {
            for ( int i = 0 ; i < route.m_tabPoint.size()-1; i++)
            {
                Geometry::Point3D pR = route.m_tabPoint[i];
                double dist = p.distanceXYTo(pR);
                double ratio = dist / (5*tailleRoute);

                // Si i est pair, on est sur la partie Haute de la route
                if( i%2==0)
                {
                    // Le point est sur la route.
                    if ( dist <= tailleRoute && p.distanceXYTo(route.m_tabPoint[i+1])<= tailleRoute)
                        z= pR.getZ();
                    // Le point est proche de la route.
                    else if ( dist < 5*tailleRoute && dist < p.distanceXYTo(route.m_tabPoint[i+1]) )
                    {
                        // Si ce point est plus proche du point précedement traité
                        int idMin=i;
                        for ( int j = 0 ; j < route.m_tabPoint.size(); j++ )
                        {
                            Geometry::Point3D pp = route.m_tabPoint[j];
                            if ( dist > pp.distanceXYTo(p) )
                                idMin = j;
                        }
                        if ( idMin == i)
                        {
                            z = p.getZ()*ratio + pR.getZ()*(1-ratio);
                        }
                    }
                }
                // Partie Basse
                else
                {
                    // Le point est sur la route.
                    if ( dist <= tailleRoute && p.distanceXYTo(route.m_tabPoint[i-1])<= tailleRoute)
                        z= pR.getZ();
                    // Le point est proche de la route.
                    else if (dist < 5*tailleRoute && dist < p.distanceXYTo(route.m_tabPoint[i-1]) )
                    {
                        int idMin=i;
                        for ( int j = 0 ; j < route.m_tabPoint.size(); j++ )
                        {
                            Geometry::Point3D pp = route.m_tabPoint[j];
                            if ( dist > pp.distanceXYTo(p) )
                                idMin = j;
                        }
                        if ( idMin == i)
                        {
                            std::cout << "PASSE"<<std::endl;
                            z = p.getZ()*ratio + pR.getZ()*(1-ratio);
                        }
                    }
                }
            }
            Geometry::Point3D pp(p.getX(), p.getY(), z);
            m.m_tabPoint.push_back(pp);
        }
        // Trop loin de la route, on laisse tel quel.
        else
        {
            m.m_tabPoint.push_back(p);
        }
    }
    return m;

}

MeshBase::Mesh Generateur::creerRouteTotale(QVector<quad_coord> tab,int nbPoints, double tailleRoute)
{

    MeshBase::Mesh m = Generateur::creerRoute(tab[0].point_A,tab[0].point_AP, tab[0].point_BP, tab[0].point_B, nbPoints ,tailleRoute);
    for (int i = 1 ; i < tab.size() ; i ++)
    {
        MeshBase::Mesh mm = Generateur::creerRoute(tab[i].point_A,tab[i].point_AP, tab[i].point_BP, tab[i].point_B, nbPoints ,tailleRoute);
        m += mm;
    }
    return m;
}


MeshBase::Mesh Generateur::generateurAlumette ()
{
    /*MeshBase::Mesh m = MeshBase::MeshFactory::sphere(5);
    m.redimensionner(0.8,0.8,1.2);
    m.redimensionner(0.1, 0.1,0.1);*/
    MeshBase::Mesh m2 = MeshBase::MeshFactory::cylindre(9,1,4);
    m2.rotation(3, 45);
    m2.redimensionner(0.1, 0.1,0.1);
    return m2;//MeshBase::Mesh::concatenation(m, m2, 0.95);
}

MeshBase::Mesh Generateur::generateurAlumette (int i)
{
    MeshBase::Mesh m = MeshBase::MeshFactory::sphere(i);
    m.redimensionner(0.8,0.8,1.2);
    m.redimensionner(0.1, 0.1,0.1);
    MeshBase::Mesh m2 = MeshBase::MeshFactory::cylindre(9,1,4);
    m2.rotation(3, 45);
    m2.redimensionner(0.1, 0.1,0.1);
    return MeshBase::Mesh::concatenation(m, m2, 0.95);
}


MeshBase::Mesh Generateur::cylinderRainures(double longueur, double rayon, int precision, int nbSommets, int rapport)
{
    MeshBase::Mesh cylindre = MeshBase::MeshFactory::cylindre( longueur, rayon, precision*2);
    for (int i = 4 ; i < cylindre.m_tabPoint.size(); i+=2)
    {
        double x = cylindre.m_tabPoint[i].getX();
        double y = cylindre.m_tabPoint[i].getY();
        double norme = sqrt(x*x+y*y);
        double angle = 2 * atan(y / ( x + norme));
        double changement = 1 + ( norme / rapport  ) * sin(angle * nbSommets);
        cylindre.m_tabPoint[i]= Geometry::Point3D(x* changement, y* changement, cylindre.m_tabPoint[i].getZ() );
        cylindre.m_tabPoint[i+1]= Geometry::Point3D(x *changement, y * changement, cylindre.m_tabPoint[i+1].getZ() );
        cylindre.m_tabNorme[i]= Geometry::Vector(x* changement, y* changement, cylindre.m_tabNorme[i][2] );
        cylindre.m_tabNorme[i+1]= Geometry::Vector(x *changement,y * changement, cylindre.m_tabNorme[i+1][2] );
    }
    return cylindre;
}

void Generateur::torsionMesh ( MeshBase::Mesh& m)
{
    QVector<Geometry::Point3D> nouveauTableau;
    nouveauTableau.reserve(m.m_tabPoint.size());

    for ( int i = 0 ; i < m.m_tabPoint.size(); i++ )
    {
        Geometry::Point3D p = m.m_tabPoint[i];
        p.setY(p.getY() +((p.getX()*p.getX())/10.0));
        nouveauTableau.push_back(p);
    }
    m.m_tabPoint = nouveauTableau;
}


MeshBase::Mesh Generateur::creationRouteDroite(double tailleX, double tailleY, int pointsX, int pointsY)
{
    MeshBase::Mesh m;
    int precision = pointsY;
    double distX = (double)tailleX/ (double)pointsX;
    double distY = (double)tailleY/ (double)pointsY;
    m.m_tabPoint.reserve((pointsX+1 )* (pointsY+1));
    m.m_tabNorme.reserve((pointsX+1 )* (pointsY+1));
    m.m_tabTopologie.reserve( pointsX * pointsY * pointsX);

    for (int i = 0 ; i <= pointsX ; i ++)
    {
        for (int j = 0 ; j <= pointsY ; ++j )
        {
            m.m_tabPoint.push_back(Geometry::Point3D(distX*i,j*distY,0));

            m.m_tabNorme.push_back(Geometry::Vector(distX*i,j*distY,0));
            if ( i && j )
            {
                int tailleP = m.m_tabPoint.size()-1;
                int tailleN = m.m_tabNorme.size()-1;

                // Triangle Base Haut
                m.m_tabTopologie.push_back(tailleP-1);
                m.m_tabTopologie.push_back(tailleN-1);


                m.m_tabTopologie.push_back(tailleP - precision -1);
                m.m_tabTopologie.push_back(tailleN - precision -1);

                m.m_tabTopologie.push_back(tailleP - precision -2 );
                m.m_tabTopologie.push_back(tailleN - precision -2 );


                // Triangle Base Bas : Bon
                m.m_tabTopologie.push_back(tailleP);
                m.m_tabTopologie.push_back(tailleN);

                m.m_tabTopologie.push_back(tailleP - precision -1);
                m.m_tabTopologie.push_back(tailleN - precision -1);


                m.m_tabTopologie.push_back(tailleP-1);
                m.m_tabTopologie.push_back(tailleN-1);
            }
        }
    }
    std::cout << "taille tab topo " << m.m_tabTopologie.size() << std::endl;
    std::cout << "taille tab pts " << m.m_tabPoint.size() << std::endl;
    std::cout << "taille tab nor " << m.m_tabNorme.size() << std::endl;
    return m;
}

MeshBase::Mesh Generateur::generateurColonne ()
{
    MeshBase::Mesh m = MeshBase::MeshFactory::cone();
    MeshBase::Mesh mC = MeshBase::MeshFactory::cone();
    mC.rotation(0, 180);
    //MeshBase::Mesh m2 = MeshBase::Mesh::cylinder(9.9,1,32);
    MeshBase::Mesh m2 = cylinderRainures(9.9,1,360, 20, 20);

    MeshBase::Mesh r = MeshBase::Mesh::concatenation(m, m2, -0.01);
    MeshBase::Mesh r2 = MeshBase::Mesh::concatenation(mC, r, 1.01);
    r2.redimensionner(0.1,0.1, 0.1);
    return r2;
}

MeshBase::Mesh Generateur::generateurDalle (double taille)
{
    MeshBase::Mesh cube = MeshBase::MeshFactory::cube(taille, taille, taille/10);
    //cube.redimensionner(taille,taille,taille/10);
    cube.normaliseMesh();
    return cube;
}

MeshBase::Mesh Generateur::generateurBaseColonnes (double taille)
{
    int nb_Col = 5;
    double rapportTaille = (taille/2)/10;

    MeshBase::Mesh colone = generateurColonne();
    colone.redimensionner(taille/2,taille/2,taille/2);
    colone.translation(rapportTaille,0,( -taille / 2 ));
    MeshBase::Mesh meshTerrain = generateurDalle(taille);
    //meshTerrain.translation(taille/2, taille/2, 0);


    MeshBase::Mesh coloneAngle = colone.copie();
    coloneAngle.translation(0,rapportTaille,0);
    meshTerrain += coloneAngle;

    coloneAngle = colone.copie();
    coloneAngle.translation(0,taille -rapportTaille,0);
    meshTerrain += coloneAngle;


    coloneAngle = colone.copie();
    coloneAngle.translation(taille - 2 *rapportTaille,rapportTaille,0);
    meshTerrain += coloneAngle;

    coloneAngle = colone.copie();
    coloneAngle.translation(taille - 2* rapportTaille,taille -rapportTaille,0);
    meshTerrain += coloneAngle;

    for ( int  i = 1 ; i < nb_Col ; i++ )
    {
        MeshBase::Mesh coloneA = colone.copie();
        coloneA.translation( i * ( taille/nb_Col)-rapportTaille,  rapportTaille ,0);
        meshTerrain += coloneA ;

        MeshBase::Mesh coloneB = colone.copie();
        coloneB.translation( i * ( taille/nb_Col) -rapportTaille, taille -rapportTaille,0);
        meshTerrain += coloneB ;

        MeshBase::Mesh coloneC = colone.copie();
        coloneC.translation(0 , i * ( taille/nb_Col),0);
        meshTerrain += coloneC ;

        MeshBase::Mesh coloneD = colone.copie();
        coloneD.translation(taille - 2* rapportTaille , i * ( taille/nb_Col) ,0);
        meshTerrain += coloneD ;
    }
    return meshTerrain;
}

MeshBase::Mesh Generateur::generateurCoque (double taille)
{
    MeshBase::Mesh coque;
    for (int i = 0 ; i < taille ; i ++)
    {
        MeshBase::Mesh nouvellePartie;
        for ( int j = 0 ; j < taille/5 ; j ++)
        {
            if ( j == 0)
            {
                MeshBase::Mesh nouvelleAlummette = Generateur::generateurAlumette(1);
                nouvellePartie += nouvelleAlummette;
            }
            else
            {
                MeshBase::Mesh nouvelleAlummetteGauche = Generateur::generateurAlumette(1);
                MeshBase::Mesh nouvelleAlummetteDroite = Generateur::generateurAlumette(1);
                nouvelleAlummetteGauche.translation(0.005*j*j,0.01*j*j,0);
                nouvelleAlummetteDroite.translation(-0.005*j*j,0.01*j*j ,0);
                nouvellePartie += nouvelleAlummetteGauche;
                nouvellePartie += nouvelleAlummetteDroite;
            }
        }
        coque = MeshBase::Mesh::concatenation(nouvellePartie,coque,1);
    }


    return coque;
}

MeshBase::Mesh Generateur::planGouteEau ( double precision )
{
    MeshBase::Mesh a = MeshBase::MeshFactory::planComplexe(precision);
    a.redimensionner(10,10,1);
    a.translation(-5,-5,0);

    for (int i = 0 ; i < a.m_tabPoint.size() ; i ++)
    {
        double z = sin ( sqrt(a.m_tabPoint[i].getX()*a.m_tabPoint[i].getX() + a.m_tabPoint[i].getY()*a.m_tabPoint[i].getY()))
                / sqrt ( 1 + a.m_tabPoint[i].getX()*a.m_tabPoint[i].getX()+a.m_tabPoint[i].getY()*a.m_tabPoint[i].getY());
        a.m_tabPoint[i] = Geometry::Point3D(a.m_tabPoint[i].getX(), a.m_tabPoint[i].getY(),z);
        a.m_tabNorme[i] = Geometry::Vector(a.m_tabNorme[i][0], a.m_tabNorme[i][1],z);
    }
    return a;
}

MeshBase::Mesh Generateur::cylindreComplexe (double longueur, double rayon, double precision)
{
    MeshBase::Mesh a;
    //     /*double */rayon = diametre/2;
    double ratio = (2 * 3.14116) / precision;

    // Points sur l'axe
    a.m_tabPoint.push_back(Geometry::Point3D(0,0,0));
    a.m_tabPoint.push_back(Geometry::Point3D(0,0,longueur));

    // Points de base pour faire fonctionner l'algorithme
    a.m_tabPoint.push_back(Geometry::Point3D(rayon,0,0));
    a.m_tabPoint.push_back(Geometry::Point3D(rayon,0,longueur));

    // Normales de bases
    a.m_tabNorme.push_back(Geometry::Vector(0,0,0));
    a.m_tabNorme.push_back(Geometry::Vector(0,0,longueur));
    a.m_tabNorme.push_back(Geometry::Vector(rayon,0,0));
    a.m_tabNorme.push_back(Geometry::Vector(rayon,0,longueur));

    for (int i = 1 ; i <= precision ; i++){
        // IdP1 = 2 * ( i + 1)
        // IdP2 = 2 * ( i + 1) + 1
        double angle = i * ( ratio);
        double x = rayon * cos ( angle);
        double y = rayon * sin ( angle);

        // Bas
        a.m_tabPoint.push_back(Geometry::Point3D(x,y,0));
        a.m_tabNorme.push_back(Geometry::Vector(x,y,0));

        //Haut
        a.m_tabPoint.push_back(Geometry::Point3D(x,y,longueur));
        a.m_tabNorme.push_back(Geometry::Vector(x,y,longueur));

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

MeshBase::Mesh Generateur::maisonSimple ( double tailleMax)
{
    double hauteur = 1.0 + tailleMax* (((double)(rand()%10)) / 10.0);
    double largeur = 1.0 + tailleMax *(((double)(rand()%10)) / 10.0);
    double longueur= 1.0 + tailleMax *(((double)(rand()%10)) / 10.0);
    MeshBase::Mesh maison = MeshBase::MeshFactory::rectangleComplexe(12,1,1 );
    maison.rotation(1,90);
    maison.redimensionner(longueur, largeur, hauteur);
    //maison.translation(1,1, - hauteur/2 );
    MeshBase::Mesh toit = Generateur::toitSimpleFez();
    toit.redimensionner(longueur,largeur,1);
    toit.translation(longueur/2,largeur/2, - hauteur - 1);

    maison = MeshBase::Mesh::concatenation(toit,maison, 1);

    /*while (maison.) {

    }*/

    return maison;
}


MeshBase::Mesh Generateur::generateurTemple ( double taille )
{

    MeshBase::Mesh temple = Generateur::generateurBaseColonnes(taille);
    //temple.translation(taille/2, taille/2,0);
    std::cout <<"colonesBases passée"<<std::endl;


    MeshBase::Mesh meshToiture = generateurDalle(taille);
    meshToiture.redimensionner(1,1,0.1);
    double valTranslate = - temple.getMaxZ() ;
    meshToiture.translation(0,0, valTranslate );
    temple += meshToiture;
    std::cout <<"oiture passée"<<std::endl;
    MeshBase::Mesh pentadre = Generateur::pentaedrePyramidal();
    pentadre.translation(-0.5,-0.5,0);
    pentadre.rotation(0,180);
    pentadre.redimensionner(taille/10, taille, taille/10 );
    pentadre.translation(taille/20,taille/2, valTranslate );
    temple += pentadre;

    std::cout <<"pentaedre passée"<<std::endl;

    double angle =9.4;

    MeshBase::Mesh tuiles = Generateur::generateurPlanOnduleeTuile();
    tuiles.rotation(0,180);
    tuiles.redimensionner(taille, taille/2,1);
    MeshBase::Mesh tuile2 = tuiles;
    tuile2.rotation(0,angle);
    tuile2.translation(0, 2* ( taille/2 ) + 0.035  ,-temple.getMaxZ() +  0.5);
    tuile2.redimensionner(0.8, 1,1);
    tuile2.translation(taille/10, 0,0);
    temple += tuile2;

    std::cout <<"tuiles passée"<<std::endl;

    MeshBase::Mesh cylindreArrond = MeshBase::MeshFactory::cylindre(taille*0.99,taille/45, 32);
    cylindreArrond.rotation(1,90);
    cylindreArrond.translation(0.005,taille/2 , - temple.getMaxZ()+ taille/85);
    temple += cylindreArrond;
    std::cout <<"cylindre passée"<<std::endl;



    MeshBase::Mesh cylindreArrondBord = MeshBase::MeshFactory::cylindre(taille,taille/45, 32);
    cylindreArrondBord.rotation(1,90);
    cylindreArrondBord.translation(0,0 , - taille/2);
    temple += cylindreArrondBord;
    cylindreArrondBord.translation(0,taille, 0);
    temple += cylindreArrondBord;

    tuiles.rotation(0,-angle);
    tuiles.translation(0, taille/2  + 0.035,-temple.getMaxZ() + 0.087 );
    tuiles.redimensionner(0.8, 1,1);
    tuiles.translation(taille/10, 0,0);
    temple += tuiles;


    pentadre.translation(taille -taille/10,0, 0 );
    temple += pentadre;

    return temple;
}


MeshBase::Mesh Generateur::pentaedrePyramidal ()
{
    MeshBase::Mesh forme;

    forme.m_tabPoint.push_back(Geometry::Point3D(0,0,0));
    forme.m_tabPoint.push_back(Geometry::Point3D(0,1,0));
    forme.m_tabPoint.push_back(Geometry::Point3D(1,0,0));
    forme.m_tabPoint.push_back(Geometry::Point3D(1,1,0));
    forme.m_tabPoint.push_back(Geometry::Point3D(0,0.5,1));
    forme.m_tabPoint.push_back(Geometry::Point3D(1,0.5,1));
    int posNorm = 0;

    // face A
    forme.m_tabNorme.push_back(
                MeshBase::Mesh::getNormeTriangle(forme.m_tabPoint[4], forme.m_tabPoint[1], forme.m_tabPoint[0] ));
    posNorm = forme.m_tabNorme.size();
    forme.m_tabTopologie << 4 << posNorm << 1 << posNorm << 0 << posNorm ;

    // Face b
    forme.m_tabNorme.push_back(
                MeshBase::Mesh::getNormeTriangle(forme.m_tabPoint[2], forme.m_tabPoint[3], forme.m_tabPoint[5] ));
    posNorm = forme.m_tabNorme.size();
    forme.m_tabTopologie << 2 << posNorm << 3 << posNorm << 5 << posNorm ;

    // Face c
    forme.m_tabNorme.push_back(
                MeshBase::Mesh::getNormeTriangle(forme.m_tabPoint[0], forme.m_tabPoint[1], forme.m_tabPoint[3] ));
    posNorm = forme.m_tabNorme.size();
    forme.m_tabTopologie << 0 << posNorm << 1 << posNorm << 3 << posNorm ;

    //Face d
    forme.m_tabNorme.push_back(
                MeshBase::Mesh::getNormeTriangle(forme.m_tabPoint[0], forme.m_tabPoint[3], forme.m_tabPoint[2] ));
    posNorm = forme.m_tabNorme.size();
    forme.m_tabTopologie << 0 << posNorm << 3 << posNorm << 2 << posNorm ;


    //Face e
    forme.m_tabNorme.push_back(
                MeshBase::Mesh::getNormeTriangle(forme.m_tabPoint[0], forme.m_tabPoint[2], forme.m_tabPoint[4] ));
    posNorm = forme.m_tabNorme.size();
    forme.m_tabTopologie << 0 << posNorm << 2 << posNorm << 4 << posNorm ;

    //Face f
    forme.m_tabNorme.push_back(
                MeshBase::Mesh::getNormeTriangle(forme.m_tabPoint[2], forme.m_tabPoint[5], forme.m_tabPoint[4] ));
    posNorm = forme.m_tabNorme.size();
    forme.m_tabTopologie << 2 << posNorm << 5 << posNorm << 4 << posNorm ;

    //Face g
    forme.m_tabNorme.push_back(
                MeshBase::Mesh::getNormeTriangle(forme.m_tabPoint[4], forme.m_tabPoint[3], forme.m_tabPoint[1] ));
    posNorm = forme.m_tabNorme.size();
    forme.m_tabTopologie << 4 << posNorm << 3 << posNorm << 1 << posNorm ;

    //Face h
    forme.m_tabNorme.push_back(
                MeshBase::Mesh::getNormeTriangle(forme.m_tabPoint[5], forme.m_tabPoint[3], forme.m_tabPoint[4] ));
    posNorm = forme.m_tabNorme.size();
    forme.m_tabTopologie << 5 << posNorm << 3 << posNorm << 4 << posNorm ;

    return forme;
}

MeshBase::Mesh Generateur::generateurPlanOnduleeTuile()
{
    int precision = 128;
    MeshBase::Mesh plan = MeshBase::MeshFactory::planComplexe(precision);
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

MeshBase::Mesh Generateur::generateurColoneStyle()
{
    MeshBase::Mesh rectangle= MeshBase::MeshFactory::rectangleComplexe(10,10,1);
    MeshBase::Mesh rectangle1= MeshBase::MeshFactory::rectangleComplexe(10,10,1);
    rectangle.translation(-0.5,-0.5,-5);
    rectangle1.translation(-0.5,-0.5,-5);

    //    TransformationBarr::taperingY(rectangle,-5,5,0,1);
    //    TransformationBarr::taperingY(rectangle1,-5,5,0,1);

    //    MeshBase::Mesh cylindre1 = MeshBase::MeshFactory::cylindreComplexe(20,1,10,20,1);
    //    MeshBase::Mesh cylindre2 = MeshBase::MeshFactory::cylindreComplexe(20,1,10,20,1);

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


MeshBase::Mesh Generateur::generateurGemeau()
{
    MeshBase::Mesh rectangle= MeshBase::MeshFactory::rectangleComplexe(10,10,1);
    MeshBase::Mesh rectangle1= MeshBase::MeshFactory::rectangleComplexe(10,10,1);
    rectangle.translation(-0.5,-0.5,-5);
    rectangle1.translation(-0.5,-0.5,-5);

    //    TransformationBarr::taperingY(rectangle,-5,5,0,1);
    //    TransformationBarr::taperingY(rectangle1,-5,5,0,1);

    //    MeshBase::Mesh cylindre1 = MeshBase::Mesh::cylindreComplexe(20,1,10,20,1);
    //    MeshBase::Mesh cylindre2 = MeshBase::Mesh::cylindreComplexe(20,1,10,20,1);

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

MeshBase::Mesh Generateur::toitSimpleFez()
{
    MeshBase::Mesh m = MeshBase::MeshFactory::fez(1,4,2,4);
    m.rotation(2, 45);
    //double x = sqrt(2);
    //m.translation(x,-x,-2);
    double facteur = 1.0606601717798212866012665431573;
    m.redimensionner(facteur,facteur,1);
    m.redimensionner(1.0/3.0,1.0/3.0,0.5);
    return m;
}

