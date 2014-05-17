#ifndef TERRAINDISCRET_H
#define TERRAINDISCRET_H

#include "mesh.h"
#include "terraincontinu.h"
#include "perlinnoise.h"
#include "pairbruitdistance.h"

#include <QPair>


class TerrainDiscret
{
private:
    /**
      TODO
      Vector de pair ( paire de point + TerrainContinu à utiliser dans chaque cas.
     * @brief a,b les deux points du domaine
     */
    QVector<QPair<QPair<Point3D ,Point3D >, TerrainContinu  > > TabEnembles;

    /**
      Taille du coté du terrain
     * @brief mTailleTerrain
     */
    int mTailleTerrain;

    /** @brief mDeltaXY : le nombre de mettres entre deux points */
    double mDeltaXY;


    /** @brief mDeltaZ : le nombre de mettres entre deux points */
    double mDeltaZ;

    /**
     * @brief mMesh de retour
     */
    Mesh mMesh;

    /**
     * @brief mTabElevation Stoque l'élévation des points x,t, avec la composante Z
     */
    QVector<double> mTabElevation;

    /**
     * @brief retourne vrais si l'objet est à l'intérieur de
     * @param x
     * @param y
     * @param pairIn
     * @return
     */
    bool contient ( double x, double y, QPair<Point3D ,Point3D > pairIn);
public:
    /**
     * @brief TerrainDiscret constructeur par défaut
     */
    TerrainDiscret();

    /**
     * @brief TerrainDiscret : constructeur avec multi ensembles
     * @param fonctionIn
     */
    TerrainDiscret( QVector<QPair<QPair<Point3D ,Point3D >, TerrainContinu  > > fonctionIn, int nbPoints, double deltaXY, double deltaZ);

    TerrainDiscret ( QVector<PairBruitDistance> pairsIn,int taille , double deltaXY, double deltaZ );

    TerrainDiscret ( QString cheminNomDeFichier, double deltaXY, double deltaZ );

    /**
      Constructeur pour initialiser un relief à partir d'un terrain continu.
      La taille étant le nombre de points voulu par coté.
     * @brief TerrainDiscret
     * @param terrainIn
     * @param taille
     */
    TerrainDiscret (TerrainContinu terrainIn,int taille, double deltaXY, double deltaZ );

    // A revoir
    //void miseEnrelief( PerlinNoise noiseIn, Point3D pointA, Point3D pointB, int n );

    Mesh getMesh( );
    // Interpolation dans un triangle.
    double getZ (int x, int y);

    /**
      Nous raisonnons sur un tableau 1D, A rotation près, le résultat est identique
     * @brief getZ
     * @param x
     * @return
     */
    double getZ(int x);

    /**
     * @brief coupeSommets : fait des crêtes "volcans" pour les sommets dépassants la hauteur indiqué
     * Prend en charge
     * @param hauteurs
     */
    void coupeSommets (double hauteurMax , double facteur);

    /**
     * @brief coupeCreux Evite les trous trops profonds
     * @param hauteurMin
     */
    void coupeCreux ( double hauteurMin, double facteur);
};


/* terrain legerement valonne coherent
    int n = 6;
    QVector<double> tabHauteursIn;
    tabHauteursIn << 10 << 5 << 2.5 << 1.25 << 10.0/16.0 << 10.0/32.0;
    QVector<double> tabFrequencesIn;
    tabFrequencesIn << 32 << 16 << 8 << 4 << 2 << 1;

    PerlinNoise noise =  PerlinNoise(4, 1, 2, 1, 0.2 );

    TerrainContinu tc(n, tabHauteursIn,tabFrequencesIn, noise);
    TerrainDiscret t = TerrainDiscret( tc, 64 );
    Mesh m = t.getMesh();
    m.rotation(0, -90);
    m.corrigeNormales();
    m.writeObj("terrain.obj");*/

#endif // TERRAINDISCRET_H
