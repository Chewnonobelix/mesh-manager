#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "mesh.h"
#include <QDebug>

namespace MeshBase
{
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

        static MeshBase::Mesh& taperingZ(MeshBase::Mesh&, double, double, double, double);

        static MeshBase::Mesh& twistingZ(MeshBase::Mesh&, double, double);

        static MeshBase::Mesh& bendingY(MeshBase::Mesh&, double, double, double, double);
    };
}

#endif // TRANSFORMATION_H
