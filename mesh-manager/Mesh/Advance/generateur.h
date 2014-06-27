#ifndef GENERATEUR_H
#define GENERATEUR_H

#include <QPoint>
#include "../Base/mesh.h"
#include "Terrain/terraincontinu.h"
#include "../../Utility/calcbezier.h"

namespace MeshAdvance
{
class Generateur
{
public:
    Generateur();
    /**
     * @brief generateurAlumette Génère une alummette
     * @return
     */
    static MeshBase::Mesh generateurAlumette ();

    static MeshBase::Mesh generateurAlumette (int i);
    /**
     * @brief generateurColonne Génère une colonne de hauteur 1.
     * @return
     */
    static MeshBase::Mesh generateurColonne ();
    /**
     * @brief generateurDalle Génère une dalle à partir d'un cube
     * @param taille
     * @return
     */
    static MeshBase::Mesh generateurDalle (double taille);
    /**
     * @brief generateurBaseColonnes Génère une base rectangulaire avec des colones de chaque coté
     * @param taille
     * @return
     */
    static MeshBase::Mesh generateurBaseColonnes (double taille);
    /**
     * @brief generateurToitTore génère un toit avec
     * @param taille
     * @param hauteur
     * @return
     */
    static MeshBase::Mesh generateurToitTore ( double taille, double hauteur);


    /**
     * @brief generateurCoque Dessine une coqe de taille t, de largeur taille/5
     * Avec des alumettes ^^
     * @return
     */
    static MeshBase::Mesh generateurCoque (double taille);

    /**
     * @brief planGouteEau retourne un plan 1 * 1 déformé par une goutte d'eau
     * @param precision
     * @return
     */
    static MeshBase::Mesh planGouteEau ( double precision );

    /**
      Non fonctionnel
     * @brief cylindreComplexe dessine un cylindre complexe;
     * @param longueur
     * @param rayon
     * @param precision
     * @return
     */
    static MeshBase::Mesh cylindreComplexe (double longueur, double rayon, double precision);

    /**
     * @brief maisonSimple dessine une maison simple de taille t
     * @param taille
     * @return
     */
    static MeshBase::Mesh maisonSimple ( double taille);

    /**
     * @brief retourne un toit simple de taille 1*1*1
     * @return
     */
    static MeshBase::Mesh toitSimpleFez ();

    /**
     * @brief Génère le temple Grec :)
     * @param taille du temple
     * @return
     */
    static MeshBase::Mesh generateurTemple ( double taille );

    /**
     * @brief Génère un pentraedre de taille 1*1*1
     * @return
     */
    static MeshBase::Mesh pentaedrePyramidal ();

    /**
     * @brief génère un plan ondulé pour immiter les tuiles
     * @return
     */
    static MeshBase::Mesh generateurPlanOnduleeTuile();

    /**
     * @brief génération du signe du gémeaux (schéma simple)
     * @param taille
     * @return
     */
    static MeshBase::Mesh generateurGemeau();

    static MeshBase::Mesh generateurColoneStyle();

    static MeshBase::Mesh cylinderRainures(double longueur, double rayon, int precision, int nbSommets, int rapport);

    static MeshBase::Mesh creationRouteDroite(double tailleX, double tailleY, int pointsX, int pointsY);
    static void torsionMesh ( MeshBase::Mesh& m);

    static MeshBase::Mesh creerRoute(Geometry::Point3D p0, Geometry::Point3D p1, Geometry::Point3D p2, Geometry::Point3D p3, double nbpts, double largeur);

    static MeshBase::Mesh creerRouteTotale (QVector<quad_coord> tab, int nbPoints, double tailleRoute);

    static MeshBase::Mesh terraforme (MeshBase::Mesh& route, MeshBase::Mesh& terrain, double tailleRoute/*, MeshAdvance::TerrainComplexe& geol*/, int);
    static MeshBase::Mesh terraforme (MeshBase::Mesh& route, MeshBase::Mesh& terrain, double tailleRoute);

    };
}
#endif // GENERATEUR_H
