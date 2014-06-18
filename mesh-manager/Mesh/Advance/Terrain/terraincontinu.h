#ifndef TERRAINCONTINU_H
#define TERRAINCONTINU_H

#include <QVector>
#include "../../../Utility/perlinnoise.h"

class TerrainContinu
{
private:
    // Noté ai dnas le cours
    //QVector<double> mTabHauteurMaximales;

    // Noté lambda i dnas le cours
    //QVector<double> mTabFrequence;

    // Nombre d'itéations ( = taille des qvectors)
    //int n;

    // Perlin noise local.
    PerlinNoise mBruit;

public:

    TerrainContinu() {}


    /**
     * @brief zgetZ
     * @return z, la hauteur correspondant au point (x, y)
     */
    double getZ(double x, double y) const;


    /**
     * @brief TerrainContinu, constructeur parramétré, avec les hauteurs, les fréquences, et le nombre d'itérations à oprérer
     * @param n
     * @param tabHauteursIn
     * @param tabFrequencesIn
     */
    TerrainContinu(/*int n, QVector<double> tabHauteursIn, QVector<double> tabFrequencesIn, */PerlinNoise NoiseIn);

    /**
     * @brief Getter et setteur Noise
     * @return
     */
    PerlinNoise getPerlinNoise() { return mBruit; }
    void getPerlinNoise(PerlinNoise noiseIn) { mBruit = noiseIn; }
};

#endif // TERRAINCONTINU_H
