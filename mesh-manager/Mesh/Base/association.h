#ifndef ASSOCIATION_H
#define ASSOCIATION_H

#include <QMap>
#include <QList>
#include <QPair>
#include "../../Utility/point3d.h"

namespace MeshBase
{
    class Mesh;
}

struct Triplet
{
    double x, y, z;

    Triplet(double = 0, double = 0, double = 0);
    Triplet(Geometry::Point3D);
};

class Association
{
private:
    QMap<QString, MeshBase::Mesh> m_assocMesh;
    QMap<QString, QList<Triplet>> m_transfo;

public:
    Association();
    bool containMesh(QString) const;
    void addMesh(QString, const MeshBase::Mesh&);
    void addTransfo(QString, Triplet);
    QList<QPair<MeshBase::Mesh, QList<Triplet>>> get() const;
};

#endif // ASSOCIATION_H
