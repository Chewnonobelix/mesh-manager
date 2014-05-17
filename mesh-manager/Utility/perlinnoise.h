#ifndef PERLINNOISE_H
#define PERLINNOISE_H

namespace MathUtility
{
    class PerlinNoise
    {
    public:

        // Constructor
        PerlinNoise();
        /**
          Pour plus d'informations, se référé à la these sur les bruits de perlin.
          Pour généré un terrain fortement maillé, je recommande une fréquence,et des octaves failbes et une persistence moyenne
         * @brief PerlinNoise
         * @param _persistence
         * @param _frequency
         * @param _amplitude
         * @param _octaves
         * @param _randomseed
         */
        PerlinNoise(double _persistence, double _frequency, double _amplitude, int _octaves, int _randomseed);
        PerlinNoise(double _persistence,double presistenceFrequences, double _frequency, double _amplitude, int _octaves, int _randomseed);

        // Get Height
        double GetHeight(double x, double y) const;

        // Get
        double Persistence() const { return persistence; }
        double Frequency()   const { return frequency;   }
        double Amplitude()   const { return amplitude;   }
        int    Octaves()     const { return octaves;     }
        int    RandomSeed()  const { return randomseed;  }

        // Set
        void Set(double _persistence, double _frequency, double _amplitude, int _octaves, int _randomseed);

        void SetPersistence(double _persistence) { persistence = _persistence; }
        void SetFrequency(  double _frequency)   { frequency = _frequency;     }
        void SetAmplitude(  double _amplitude)   { amplitude = _amplitude;     }
        void SetOctaves(    int    _octaves)     { octaves = _octaves;         }
        void SetRandomSeed( int    _randomseed)  { randomseed = _randomseed;   }

    private:

        double Total(double i, double j) const;
        double GetValue(double x, double y) const;
        double Interpolate(double x, double y, double a) const;
        double Noise(int x, int y) const;

        double persistence, persitenceFrequence, frequency, amplitude;
        int octaves, randomseed;
    };
}
#endif // PERLINNOISE_H
