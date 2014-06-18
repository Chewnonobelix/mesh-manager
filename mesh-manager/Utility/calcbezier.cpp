#include "calcbezier.h"

#include <iostream>
#include "vector.h"

#define cube(X) ((X*X*X))
#define carre(X) ((X*X))


QVector<Geometry::Point3D> calcBezier::tabPoints() const
{
    return m_tabPoints;
}

void calcBezier::setTabPoints(const QVector<Geometry::Point3D> &tabPoints)
{
    m_tabPoints = tabPoints;
}

void calcBezier::calculeOrthogonal(Geometry::Point3D &p0, Geometry::Point3D &p1, Geometry::Point3D &p2, Geometry::Point3D &p3, Geometry::Point3D &p00, Geometry::Point3D &p11, Geometry::Point3D &p22, Geometry::Point3D &p33, double largeur)
{
    Geometry::Vector A(p1.getX()-p0.getX(), p1.getY()-p0.getY(), p1.getZ() - p0.getZ());
    Geometry::Vector B(p3.getX()-p2.getX(), p3.getY()-p2.getY(), p3.getZ() - p2.getZ());
    Geometry::Vector AO = Orthogonal(A);
    AO = Normalized(AO);
    AO = AO * largeur;
    Geometry::Vector BO = Orthogonal(B);
    BO = Normalized(BO);
    BO = BO * largeur;

    p00.setX(p0.getX()+AO[0]);
    p00.setY(p0.getY()+AO[1]);
    p00.setZ(p0.getZ()+AO[2]);


    p11.setX(p1.getX()+AO[0]);
    p11.setY(p1.getY()+AO[1]);
    p11.setZ(p1.getZ()+AO[2]);


    p22.setX(p2.getX()+BO[0]);
    p22.setY(p2.getY()+BO[1]);
    p22.setZ(p2.getZ()+BO[2]);


    p33.setX(p3.getX()+BO[0]);
    p33.setY(p3.getY()+BO[1]);
    p33.setZ(p3.getZ()+BO[2]);

}



QVector<quad_coord> calcBezier::getTabPointsRoute(QVector<Geometry::Point3D> pointsDePassage)
{
    QVector<quad_coord> res;

    // Pour tous les points de passage -1 car nous avons n-1 segments
    Geometry::Point3D BPP;
    for (int i = 0 ; i < pointsDePassage.size() -1; i ++ )
    {
        // Nouvelle portion
        quad_coord q;

        Geometry::Point3D A = pointsDePassage[i];
        // Garanti par l'incrément
        Geometry::Point3D B = pointsDePassage[i+1];
        q.point_A = A;
        q.point_B = B;

        // On ajoute les points A et B.
        /*q.point_A = pointsDePassage[i];
        q.point_B = pointsDePassage[i+3];
        q.point_BP = pointsDePassage[i+2];
        q.point_AP = pointsDePassage[i+1];*/

        // Cas pour le premier segment
        /**/
        Geometry::Vector v;
        if (i == 0)
        {
            q.point_BP = B;

            if ( i + 2 < pointsDePassage.size() )
                BPP = getPointDerivee(A,pointsDePassage[i+2]);
            else
                BPP = getPointDerivee(A,B);
            v = BPP.toVector();
            v = Normalized(v);
            //v = v.Rotation(-20);
            BPP.fromVector(v);

            q.point_BP.setX(q.point_BP.getX() - BPP.getX()/4);
            q.point_BP.setY(q.point_BP.getY() - BPP.getY()/4);
            q.point_BP.setZ(q.point_BP.getZ() - BPP.getZ()/4);


            //v = v.Rotation(66);
            q.point_AP = A;

            q.point_AP.setX(q.point_AP.getX() + BPP.getX()/4);
            q.point_AP.setY(q.point_AP.getY() + BPP.getY()/4);
            q.point_AP.setZ(q.point_AP.getZ() + BPP.getZ()/4);


           // v = v.Rotation(-66);
        }
        // Cas pour le dernier segment
        else if ( i == pointsDePassage.size()-2)
        {
            q.point_BP = B;

            q.point_BP.setX(q.point_BP.getX() - BPP.getX()/4);
            q.point_BP.setY(q.point_BP.getY() - BPP.getY()/4);
            q.point_BP.setZ(q.point_BP.getZ() - BPP.getZ()/4);


            q.point_AP = A;

            q.point_AP.setX(q.point_AP.getX() + BPP.getX()/4);
            q.point_AP.setY(q.point_AP.getY() + BPP.getY()/4);
            q.point_AP.setZ(q.point_AP.getZ() + BPP.getZ()/4);
        }
        // Cas général
        else
        {
            q.point_AP = A;

            q.point_AP.setX(q.point_AP.getX() + BPP.getX()/4);
            q.point_AP.setY(q.point_AP.getY() + BPP.getY()/4);
            q.point_AP.setZ(q.point_AP.getZ() + BPP.getZ()/4);

            q.point_BP = B;


            if ( i + 2 < pointsDePassage.size() )
                BPP = getPointDerivee(A,pointsDePassage[i+2]);
            else
                BPP = getPointDerivee(A,B);

            Geometry::Vector v = BPP.toVector();
            v = Normalized(v);
            //v = v.Rotation(-20);
            BPP.fromVector(v);

            q.point_BP.setX(q.point_BP.getX() - BPP.getX()/4);
            q.point_BP.setY(q.point_BP.getY() - BPP.getY()/4);
            q.point_BP.setZ(q.point_BP.getZ() - BPP.getZ()/4);
        }/**/

        // On ajoute la portion.
        res.push_back(q);
    }
    return res;
}


Geometry::Point3D calcBezier::getPointDerivee(Geometry::Point3D A, Geometry::Point3D B)
{
    Geometry::Point3D ret(B.getX()-A.getX(), B.getY()-A.getY(), B.getZ() - A.getZ());
    return ret;
}

Geometry::Point3D calcBezier::getInverse(Geometry::Point3D A)
{
    return (A * -1);
}

calcBezier::calcBezier(Geometry::Point3D p0i, Geometry::Point3D p1i, Geometry::Point3D p2i, Geometry::Point3D p3i, double nbPoints):
    p0(p0i), p1(p1i), p2(p2i), p3(p3i)
{
    m_tabPoints.reserve(nbPoints);

    // (1-t)^3 * P0 + 3(1-t)²*t * P1 + 3(1-t)t² * P2 + t^3 * P3
    for ( int i = 0 ; i <= nbPoints ; i++)
    {
        double t = i * 1.d/nbPoints;
        double tt  = 1 - t;
        Geometry::Point3D p;
        p.setX(cube(tt)*p0.getX() + 3*carre(tt)*p1.getX()*t + 3*carre(t)*tt*p2.getX() + cube(t)*p3.getX());
        p.setY(cube(tt)*p0.getY() + 3*carre(tt)*p1.getY()*t + 3*carre(t)*tt*p2.getY() + cube(t)*p3.getY());
        m_tabPoints.push_back(p);
    }
}

void calcBezier::afficheTabPoints()
{
    std::cout << "Affichage Points Courbe" << std::endl;
    for (int i = 0 ; i < m_tabPoints.size(); i++)
    {
        std::cout<< "Point" << i << " x=" << m_tabPoints[i].getX() << " y=" << m_tabPoints[i].getY() << std::endl;
    }
    std::cout << "Fin taille=" << m_tabPoints.size() << std::endl;
}
