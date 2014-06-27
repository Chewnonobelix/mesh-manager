#ifndef TRIANGLE3D_H
#define TRIANGLE3D_H

#include "point3d.h"

class Triangle3D
{
private:
    Geometry::Point3D A;
    Geometry::Point3D B;
    Geometry::Point3D C;
public:
    Triangle3D();
    Triangle3D(Geometry::Point3D Ain,Geometry::Point3D Bin,Geometry::Point3D Cin);

    double getZBarricentre(Geometry::Point3D& D);
    bool pointInterieurTriangle(Geometry::Point3D& p);
    bool estInterrieur(Geometry::Point3D p);

    // Méthode fonctionele.
    bool inside ( Geometry::Point3D p);
};

#endif // TRIANGLE3D_H
