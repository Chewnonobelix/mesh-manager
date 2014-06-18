#ifndef POINT3D_H
#define POINT3D_H

#include "vector.h"
namespace Geometry
{

    class Point3D
    {
    private:
        /**
        * Coordonnées d'un point
        */
        double coord_x;
        double coord_y;
        double coord_z;
    public:
        Point3D();
        /**
        *        Constructeur par défaut, valeur par défaut: origine du repère
        */
        Point3D(double, double, double);

        /**
        * Constructeur par recopie
        */
        Point3D(const Point3D&);

        /**
        * Destructeur virtuel
        */
        virtual ~Point3D();


        /**
        * Getter et Setter
        */

        double getX() const;
        void setX(double x);
        double getY() const;
        void setY(double y);
        double getZ() const;
        void setZ(double z);

        static Point3D fromVector( const Vector& v );

        Vector toVector() const;

        /**
        * Opérateur d'affectation
        */
        Point3D& operator = (const Point3D&);
        /**
        * Opérateur d'égalité
        */
        bool operator == (const Point3D&);

        /**
        * Opérateur d'addition de 2 points, crée un nouveau point.
        */
        Point3D operator + (const Point3D&);


        /**
        * Opératiopn d'addition statique
        */
        Point3D& operator += (const Point3D&);

        /**
        * Multiplication d'un point par un scalaire, crée un nouveau point
        */
        Point3D operator*(double);

        /**
        * Multiplication statique par un scalaire
        */
        Point3D& operator *= (double);

        /**
         * @brief distanceTo : retourne la distance entre 2 points ( sur XY )
         * @param autre
         * @return
         */
        double distanceXYTo ( Point3D autre);
    };
}

#endif // POINT3D_H
