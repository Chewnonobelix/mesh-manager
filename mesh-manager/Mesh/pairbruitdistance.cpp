#include "pairbruitdistance.h"

PairBruitDistance::PairBruitDistance()
{
}

double PairBruitDistance::getRapport ( double distanceAuCentre )
{
    if ( distanceAuCentre >= mDistance)
        return 0.0;
    else
        return  ( mDistance - distanceAuCentre ) / mDistance;
}

PairBruitDistance::PairBruitDistance ( double rayonActionIn, Point3D centreIn, TerrainContinu fonctionIn):
    mDistance(rayonActionIn), mPointCentral(centreIn), mFonction(fonctionIn)
{
}

double PairBruitDistance::getZ ( double x, double y )
{
    double distance = mPointCentral.distanceXYTo(Point3D(x,y,0));
    double rapport = getRapport(distance);

    return rapport * mFonction.getZ(x,y);
}
