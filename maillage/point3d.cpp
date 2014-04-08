#include "point3d.h"

Point3D::Point3D():coord_x(0), coord_y(0), coord_z(0)
{}
Point3D::Point3D(double x, double y, double z):coord_x(x), coord_y(y), coord_z(z)
{}

Point3D::Point3D(const Point3D& p): coord_x(p.getX()), coord_y(p.getY()), coord_z(p.getZ())
{}

Point3D::~Point3D()
{}

double Point3D::getX() const
{
    return coord_x;
}

void Point3D::setX(double x)
{
    coord_x = x;
}

double Point3D::getY() const
{
    return coord_y;
}

void Point3D::setY(double y)
{
    coord_y = y;
}

double Point3D::getZ() const
{
    return coord_z;
}

void Point3D::setZ(double z)
{
    coord_z = z;
}

Point3D& Point3D::operator = (const Point3D& p)
{
    setX(p.getX( ));
    setY(p.getY( ));
    setZ(p.getZ( ));

    return *this;
}

bool operator == (const Point3D& p1, const Point3D& p2)
{
    return (p1.getX( ) == p2.getX( )) &&
            (p1.getY( ) == p2.getY( )) &&
            (p1.getZ( ) == p2.getZ( ));
}

Point3D operator + (const Point3D& p1, const Point3D& p2)
{
    return Point3D(p1.getX( ) + p2.getX( ), p1.getY( ) + p2.getY( ),
                   p1.getZ( ) + p2.getZ( ));
}

Point3D& Point3D::operator += (const Point3D& p)
{
    setX(getX( ) + p.getX( ));
    setY(getY( ) + p.getY( ));
    setZ(getZ( ) + p.getZ( ));

    return *this;
}

Point3D operator*(const Point3D& p, double s)
{
    return Point3D (p.getX( ) * s, p.getY( ) * s, p.getZ( ) * s);

}

Point3D& Point3D::operator *= (double s)
{
    setX(getX( ) * s);
    setY(getY( ) * s);
    setZ(getZ( ) * s);

    return *this;
}



Point3D Point3D::fromVector( const Vector& v )
{
    return Point3D(v[0], v[1], v[2]);
}

Vector Point3D::toVector(  ) const
{
    return Vector(getX(), getY(), getZ());
}
