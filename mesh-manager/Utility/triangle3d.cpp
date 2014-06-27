#include "triangle3d.h"
#include <cmath>

Triangle3D::Triangle3D()
{
}


Triangle3D::Triangle3D(Geometry::Point3D Ain,Geometry::Point3D Bin,Geometry::Point3D Cin): A(Ain),B(Bin),C(Cin)
{
}

double Triangle3D::getZBarricentre(Geometry::Point3D& D)
{
    double xn = (B.getY()-A.getY())*(C.getZ()-A.getZ()) - (C.getY()-A.getY())*(B.getZ()-A.getZ());
    double yn = (C.getX()-A.getX())*(B.getZ()-A.getZ()) - (B.getX()-A.getX())*(C.getZ()-A.getZ());
    double zn = (B.getX()-A.getX())*(C.getY()-A.getY()) - (C.getX()-A.getX())*(B.getY()-A.getY());

    double z =( A.getX() *xn) +(A.getY() *yn) + (A.getZ()*zn) - (D.getX()*xn) - (D.getY()*yn) ;
    z = z/zn;

    return z;
}


double area(const double& x1, const double& y1, const double& x2, const double& y2, const double& x3, const double& y3)
{
   return abs((x1*(y2-y3) + x2*(y3-y1)+ x3*(y1-y2))/2.0);
}

bool isInside(const double& x1,const double& y1, const double& x2, const double& y2, const double& x3, const double& y3, const double& x, const double& y)
{
   /* Calculate area of triangle ABC */
   double A = area (x1, y1, x2, y2, x3, y3);

   /* Calculate area of triangle PBC */
   double A1 = area (x, y, x2, y2, x3, y3);

   /* Calculate area of triangle PAC */
   double A2 = area (x1, y1, x, y, x3, y3);

   /* Calculate area of triangle PAB */
   double A3 = area (x1, y1, x2, y2, x, y);

   /* Check if sum of A1, A2 and A3 is same as A */
   if (((A -( A1 + A2 + A3) ) < 0.001 ) || ((A -( A1 + A2 + A3) ) > -0.001 ))
        return true;
   else
       return false;
}

bool Triangle3D::pointInterieurTriangle(Geometry::Point3D& p)
{
    double ap_x = p.getX()-A.getX();
    double ap_y = p.getY()-A.getY();

    bool p_ab = (B.getX()-A.getX())*ap_y-(B.getY()-A.getY())*ap_x > 0;

    if(((C.getX()-A.getX())*ap_y-(C.getX()-A.getY())*ap_x > 0) == p_ab) return false;

    if(((C.getX()-B.getX())*(p.getY()-B.getY())-(C.getX()-B.getY())*(p.getX()-B.getX()) > 0) != p_ab) return false;

    return true;
    //return isInside(A.getX(),A.getY(), B.getX(), B.getY(), C.getX(), C.getY(), p.getX(), p.getY());
}
double dot (Geometry::Vector a, Geometry::Vector b)
{
    double ret = 0;
    ret += a[0]*b[0];
    ret += a[1]*b[1];
    ret += a[2]*b[2];
    return ret;
}

bool Triangle3D::estInterrieur(Geometry::Point3D P)
{
    // Compute vectors
    Geometry::Vector v0 = C.toVector() - A.toVector();
    Geometry::Vector v1 = B.toVector() - A.toVector();
    Geometry::Vector v2 = P.toVector() - A.toVector();

    // Compute dot products
    double dot00 = dot(v0, v0);
    double dot01 = dot(v0, v1);
    double dot02 = dot(v0, v2);
    double dot11 = dot(v1, v1);
    double dot12 = dot(v1, v2);

    // Compute barycentric coordinates
    double invDenom = 1.d / (dot00 * dot11 - dot01 * dot01);
    double u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    double v = (dot00 * dot12 - dot01 * dot02) * invDenom;

    // Check if point is in triangle
    return (u > 0.d) && (v > 0.d) && (u + v < 1.d);
}



int IsPointInBoundingBox(double x1, double y1, double x2, double y2, double px, double py)
{
    double left, top, right, bottom; // Bounding Box For Line Segment

    // For Bounding Box
    if(x1 < x2)
    {
        left = x1;
        right = x2;
    }
    else
    {
        left = x2;
        right = x1;
    }

    if(y1 < y2)
    {
        top = y1;
        bottom = y2;
    }
    else
    {
        top = y2;
        bottom = y1;
    }

    if( (px+0.01) >= left && (px-0.01) <= right &&
            (py+0.01) >= top && (py-0.01) <= bottom )
    {
        return 1;
    }
    else
        return 0;

}


int LineSegmentIntersection(double l1x1, double l1y1, double l1x2, double l1y2,
                            double l2x1, double l2y1, double l2x2, double l2y2,
                            double *m1, double *c1, double *m2, double *c2,
                            double* intersection_X, double* intersection_Y)
{

    double dx, dy;

    dx = l1x2 - l1x1;
    dy = l1y2 - l1y1;

    *m1 = dy / dx;

    // y = mx + c
    // intercept c = y - mx
    *c1 = l1y1 - *m1 * l1x1; // which is same as y2 - slope * x2

    dx = l2x2 - l2x1;
    dy = l2y2 - l2y1;

    *m2 = dy / dx;
    // y = mx + c
    // intercept c = y - mx
    *c2 = l2y1 - *m2 * l2x1; // which is same as y2 - slope * x2

    if( (*m1 - *m2) == 0)
        return 0;
    else
    {
        *intersection_X = (*c2 - *c1) / (*m1 - *m2);
        *intersection_Y = *m1 * *intersection_X + *c1;
    }

    if(IsPointInBoundingBox(l1x1, l1y1, l1x2, l1y2, *intersection_X, *intersection_Y) == 1 && IsPointInBoundingBox(l2x1, l2y1, l2x2, l2y2, *intersection_X, *intersection_Y) == 1)
    {
        return 1;
    }
    else
        return 0;
}


bool Triangle3D::inside ( Geometry::Point3D p)
{
    double m1, c1, m2, c2,px=0, py=0;
    double intersection_X, intersection_Y;
    int nCountIntersections = 0;
    nCountIntersections += LineSegmentIntersection(A.getX(), A.getY(), B.getX(), B.getY(), p.getX(), p.getY(), px, py,
                                &m1, &c1, &m2, &c2, &intersection_X, &intersection_Y);

    nCountIntersections += LineSegmentIntersection(A.getX(), A.getY(), C.getX(), C.getY(), p.getX(), p.getY(), px, py,
                                &m1, &c1, &m2, &c2, &intersection_X, &intersection_Y);

    nCountIntersections += LineSegmentIntersection(C.getX(), C.getY(), B.getX(), B.getY(), p.getX(), p.getY(), px, py,
                                &m1, &c1, &m2, &c2, &intersection_X, &intersection_Y);

    if ( nCountIntersections%2 ==  1)
        return true;
    else
        return false;
}
