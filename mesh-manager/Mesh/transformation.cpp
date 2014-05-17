#include "transformation.h"

TransformationBarr::TransformationBarr()
{
}

double TransformationBarr::coeffA0(double a, double sa, double b, double sb)
{
    return (a*a*a*sb - 3*a*a*b*sb+3*a*b*b*sa-b*b*b*sa)/((a-b)*(a-b)*(a-b));
}

double TransformationBarr::coeffA1(double a, double sa, double b, double sb)
{
    return -(6*(sa-sb)*a*b)/((a-b)*(a-b)*(a-b));
}

double TransformationBarr::coeffA2(double a, double sa, double b, double sb)
{
    return 3*(sa-sb)*(a+b)/((a-b)*(a-b)*(a-b));
}

double TransformationBarr::coeffA3(double a, double sa, double b, double sb)
{
    return -2*(sa-sb)/((a-b)*(a-b)*(a-b));
}

double TransformationBarr::calculPol(double x, double a0, double a1, double a2, double a3)
{
    return a0+a1*x+a2*x*x+a3*x*x*x;
}

Mesh& TransformationBarr::taperingZ(Mesh& m, double a, double sa, double b, double sb)
{
    for(int i = 0; i < m.m_tabPoint.size(); i ++)
    {
        Point3D& p = m.m_tabPoint[i];
        double sz;
        if(p.getZ() >= a && p.getZ() <= b)
        {
            sz = calculPol(p.getZ(), coeffA0(a,sa,b,sb), coeffA1(a,sa,b,sb), coeffA2(a,sa,b,sb), coeffA3(a,sa,b,sb));
        }
        else if(p.getZ() < a)
        {
            sz = sa;
        }
        else
        {
            sz = sb;
        }

        p.setX(sz*p.getX());
        p.setY(sz*p.getY());
    }

    m.corrigeNormales();

    return m;
}

Mesh& TransformationBarr::twistingZ(Mesh& m, double coeff, double frequence)
{
    for(int i = 0; i < m.m_tabPoint.size(); i ++)
    {
        Point3D &p = m.m_tabPoint[i];

        double x = p.getX(),y = p.getY();
        p.setX(cos(2*p.getZ()*M_PI/frequence) * x + sin(2*p.getZ()*M_PI/frequence) * y);
        p.setY(sin(2*p.getZ()*M_PI/frequence) * x + cos(2*p.getZ()*M_PI/frequence) * y);
    }

    for(int i = 0; i < m.m_tabNorme.size(); i ++)
    {
        Vector
                &p = m.m_tabNorme[i];

        double x = p[0],y = p[1];
        p[0] = cos(2*p[2]*M_PI/frequence) * x + sin(2*p[2]*M_PI/frequence) * y;
        p[1] = sin(2*p[2]*M_PI/frequence) * x + cos(2*p[2]*M_PI/frequence) * y;
    }

    m.corrigeNormales();

    return m;
}

Mesh& TransformationBarr::bendingY(Mesh& m, double y0, double ymin, double ymax, double ratio)
{
    m.rotation(-90, 0, 0);
    for(int i = 0; i < m.m_tabPoint.size(); i ++)
    {
        Point3D& p = m.m_tabPoint[i];
        double theta;
        double y = p.getY(), yc;
        double z = p.getZ();
        if(y >= ymin && y <= ymax)
        {
            yc = p.getY();
            theta = ratio*(yc - y0);
            p.setY(-sin(theta)*(z-1/ratio)+y0);
            p.setZ(cos(theta)*(z-1/ratio)+1/ratio);
        }
        else if( y < ymin)
        {
            yc = ymin;
            theta = ratio*(yc - y0);
            p.setY(-sin(theta)*(z-1/ratio)+y0+cos(theta)*(y-ymin));
            p.setZ(cos(theta)*(z-1/ratio)+1/ratio+sin(theta)*(y-ymin));
        }
        else if( y > ymax)
        {
            yc = ymax;
            theta = ratio*(yc - y0);
            p.setY(-sin(theta)*(z-1/ratio)+y0+cos(theta)*(y-ymax));
            p.setZ(cos(theta)*(z-1/ratio)+1/ratio+sin(theta)*(y-ymax));
        }
    }
    m.rotation(90, 0, 0);
    m.corrigeNormales();
    return m;
}
