#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "mesh.h"
#include <QDebug>

class TransformationBarr
{
private:
    static double coeffA0(double, double, double, double);
    static double coeffA1(double, double, double, double);
    static double coeffA2(double, double, double, double);
    static double coeffA3(double, double, double, double);
    static double calculPol(double, double, double, double, double);

public:
    TransformationBarr();

    static Mesh& taperingZ(Mesh&, double, double, double, double);

    static Mesh& twistingZ(Mesh&, double, double);

    static Mesh& bendingY(Mesh&, double, double, double, double);
};

#endif // TRANSFORMATION_H
