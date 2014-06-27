#ifndef CALCBEZIER_H
#define CALCBEZIER_H


#include "point3d.h"
#include <QVector>

typedef struct
{
    Geometry::Point3D point_A;
    Geometry::Point3D point_B;
    Geometry::Point3D point_AP;
    Geometry::Point3D point_BP;
} quad_coord;

class calcBezier
{
private:
    QVector<Geometry::Point3D> m_tabPoints;
    Geometry::Point3D p0;
    Geometry::Point3D p1;
    Geometry::Point3D p2;
    Geometry::Point3D p3;

    static Geometry::Point3D getPointDerivee(Geometry::Point3D A, Geometry::Point3D B);
    static Geometry::Point3D getInverse(Geometry::Point3D A);
public:
    calcBezier(Geometry::Point3D p0, Geometry::Point3D p1, Geometry::Point3D p2, Geometry::Point3D p3, double nbPoints);


    void afficheTabPoints();
    QVector<Geometry::Point3D> tabPoints() const;
    void setTabPoints(const QVector<Geometry::Point3D> &tabPoints);

    static void calculeOrthogonal (Geometry::Point3D& p0, Geometry::Point3D& p1, Geometry::Point3D& p2, Geometry::Point3D& p3,
                                   Geometry::Point3D& p00, Geometry::Point3D& p11, Geometry::Point3D& p22, Geometry::Point3D& p33, double largeur);

    static void calculeOrthogonalSimple
        (Geometry::Point3D &p0, Geometry::Point3D &p1, Geometry::Point3D &p00, double largeur);

    static QVector<quad_coord> getTabPointsRoute ( QVector<Geometry::Point3D> pointsDePassage);
};

#endif // CALCBEZIER_H
