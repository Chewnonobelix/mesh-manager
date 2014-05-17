#ifndef PAIRBRUITDISTANCE_H
#define PAIRBRUITDISTANCE_H

#include "terraincontinu.h"
#include "../Utility/point3d.h"

class PairBruitDistance
{
private:
    double mDistance;
    Geometry::Point3D mPointCentral;
    TerrainContinu mFonction;

    double getRapport ( double distanceAuCentre );

public:
    PairBruitDistance();
    /**
      constructeur à utiliser, construit la structure de donnée
     * @brief PairBruitDistance
     * @param rayonActionIn
     * @param centreIn
     * @param fonctionIn
     */
    PairBruitDistance ( double rayonActionIn, Geometry::Point3D centreIn, TerrainContinu fonctionIn);

    /**
     * @brief getZ : retourne la hauteur au point demandé
     * @param x
     * @param y
     * @return
     */
    double getZ ( double x, double y );
};

#endif // PAIRBRUITDISTANCE_H
