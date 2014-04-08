#ifndef BATIMENT_H
#define BATIMENT_H

#include "mesh.h"

class Batiment : public Mesh
{
private:
    QVector<Point3D> tabPointsExtremes;

public:
    Batiment();
};

#endif // BATIMENT_H
