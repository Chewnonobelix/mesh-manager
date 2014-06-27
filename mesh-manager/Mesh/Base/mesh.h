#ifndef MESH_H
#define MESH_H

#include <QVector>
#include <QString>
#include "../../Utility/point3d.h"
#include "../../Utility/vector.h"
#include "../../Utility/mathutils.h"
#include "association.h"

namespace MeshBase
{
    class MeshFactory;
    class TransformationBarr;
}
namespace MeshAdvance
{
    class Generateur;
    class TerrainDiscret;
}

namespace MeshBase
{
    class Mesh
    {
        friend class MeshFactory;
        friend class MeshAdvance::Generateur;
        friend class TransformationBarr;
        friend class MeshAdvance::TerrainDiscret;

    private:
        QVector<Geometry::Point3D> m_tabPoint;
        QVector<Geometry::Vector> m_tabNorme;
        QVector<int> m_tabTopologie;
        Association m_assoc;

        /**
         * @brief subDivideSpherePoint Fonction permettant de subdviser une shphère
         */
        void subDivideSpherePoint(int = 1);

        /**
         * @brief degToRad renvoit un radiant
         * @param deg
         * @return
         */
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
         * @brief smoothMesh : fait fondre les normales.
         */
        void smoothMesh(double deltaX);

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

        /**
         * @brief rotation sur X, Y, et Z
         * 0 signifie pas de transformation pour cette composante
         * @param thetaX
         * @param thetaY
         * @param thetaZ
         */
        void rotation(double thetaX, double thetaY, double thetaZ);
        /**
         * @brief translation : applique la transformation de vecteur (x,y,z) �  l'objet
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
        static Geometry::Vector getNormeTriangle ( Geometry::Point3D A, Geometry::Point3D B, Geometry::Point3D C);

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

        // Ecrit sans les normales
        void writeObjNoNormals(QString nom);

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

        /**
         * @brief surcharge des op�rateurs
         */
        friend Mesh MeshBase::operator + (const Mesh&, const Mesh&);
        friend Mesh MeshBase::operator + (const Mesh&, const QVector<Mesh>&);
        Mesh& operator += (const Mesh&);
        Mesh& operator += (const QVector<Mesh>&);

        Mesh& operator = (const Mesh&);

        friend bool operator == (const Mesh&, const Mesh&);


        /**
         * @brief generateurTerrain fonction inutile
         * @return
         */
        static Mesh generateurTerrain ();

        static void mensurationMesh(Mesh& m, double& xmmin,double& xmax,double& ymin,double& ymax);
        void addAssoc(QString, const Mesh&, Triplet);
    };
}

#endif // MESH_H
