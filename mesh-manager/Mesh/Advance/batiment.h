#ifndef BATIMENT_H
#define BATIMENT_H

#include "../Base/mesh.h"

class Batiment : public MeshBase::Mesh
{
private:
    QVector<Geometry::Point3D> tabPointsExtremes;

public:
    Batiment();
};

#endif // BATIMENT_H
