#include "association.h"
#include "mesh.h"

Triplet::Triplet(double xi, double yi, double zi): x(xi), y(yi), z(zi) {}
Triplet::Triplet(Geometry::Point3D p): x(p.getX()), y(p.getY()), z(p.getZ()) {}

Association::Association()
{
}

bool Association::containMesh(QString id) const
{
    return m_assocMesh.contains(id);
}

void Association::addMesh(QString id, const MeshBase::Mesh &m)
{
    m_assocMesh[id] = m;
}

void Association::addTransfo(QString id, Triplet t)
{
    m_transfo[id].push_back(t);
}

QList<QPair<MeshBase::Mesh, QList<Triplet>>> Association::get() const
{
    QList<QPair<MeshBase::Mesh, QList<Triplet>>> ret;
    QList<QString> l = m_assocMesh.keys();

    foreach (QString s, l)
    {
        ret.push_back(qMakePair(m_assocMesh[s], m_transfo[s]));
    }

    return ret;
}
