#ifndef MESH_H
#define MESH_H

#include <QVector>
#include <QString>
#include "point3d.h"
#include "vector.h"



class MeshFactory;
class Generateur;
class TransformationBarr;

class Mesh
{
    friend class MeshFactory;
    friend class Generateur;
    friend class TransformationBarr;

private:
    QVector<int> m_tabTopologie;
    QVector<Vector> m_tabNorme;
    QVector<Point3D> m_tabPoint;

    /**
     * @brief subDivideSpherePoint Fonction permettant de subdviser une shphère
     * Non testé
     */
    void subDivideSpherePoint(int = 1);
    inline double degToRad(double deg) const
    {
        return (deg*M_PI)/180;
    }

public:
    Mesh();
    Mesh(const Mesh&);

    /**
     * @brief normaliseMesh positionne le point 0 de la mesh sur (0,0,0)
     */
    void normaliseMesh ();

    /**
     * @brief copie la mesh courante
     * @return une nouvelle Mesh
     */
    Mesh copie () const;

	double getMaxZ () const;

    /**
     * @brief Mesh::corrigeNormales
     * Recalcule toutes les normales � partir de l'expression de points quelcoques
     */
    void corrigeNormales ();


    /**
     * @brief rotation : fait tourner l'objet autour de son axe
     * 0 = x
     * 1 = y
     * 2 = z
     */
    void rotation(int composante, double angle);

    void rotation(double thetaX, double thetaY, double thetaZ);
    /**
     * @brief translation : applique la transformation de vecteur (x,y,z) à l'objet
     */
    void translation(double x , double y , double z);

    /**
     * @brief redimensionner redimensionne l'objet avec une composante 3D
     * 1= identitée, 0, annulation de la composante
     */
    void redimensionner(double x, double y , double z);

	    /**
     * @brief getNormeTriangle
     * @param A
     * @param B
     * @param C
     * @return Nouveau vector correspondant � la nouvelle norme.
     */
    static Vector getNormeTriangle ( Point3D A, Point3D B, Point3D C);


    /**
     * Retourne une chaine formatée
     * @brief toString
     * @return
     */
    QString toString();
    /**
      Ecrit l'objet
     * @brief writeObj
     * @param nom
     * @param data
     */
    void writeObj(QString nom);

	    /**
      Ecrit l'objet
     * @brief read object from file
     * @param path of the file
     */
    static Mesh readObj(QString path);

    /**
     * @brief concatenation de deux Mesh a première en tête et la secconde en base
     * @param partieHaute
     * @param partieBasse
     * @param rapportPourcent :
     * @return
     */
    static Mesh concatenation(Mesh partieHaute,Mesh partieBasse, double rapportPourcent);

    friend Mesh operator + (const Mesh&, const Mesh&);
    friend Mesh operator + (const Mesh&, const QVector<Mesh>&);
    Mesh& operator += (const Mesh&);
    Mesh& operator += (const QVector<Mesh>&);

    Mesh& operator = (const Mesh&);

    friend bool operator == (const Mesh&, const Mesh&);
};

#endif // MESH_H
