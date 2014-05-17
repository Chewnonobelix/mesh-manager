#include "terraincontinu.h"


double TerrainContinu::getZ ( double x, double y) const
{
    double z =  mBruit.GetHeight( x, y );
    return z;
}


/**
 * @brief TerrainContinu, constructeur parramétré, avec les hauteurs, les fréquences, et le nombre d'itérations à oprérer
 * @param n
 * @param tabHauteursIn
 * @param tabFrequencesIn
 */
TerrainContinu::TerrainContinu(PerlinNoise NoiseIn) : //n( nIn),
    //mTabHauteurMaximales(tabHauteursIn),
    //mTabFrequence(tabFrequencesIn),
    mBruit(NoiseIn)
{

}
