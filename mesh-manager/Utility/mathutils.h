#ifndef MATHUTILS_H
#define MATHUTILS_H

#include <time.h>
#include <cstdlib>


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


namespace MathUtility
{
    class Math
    {
    private:
        static bool m_init;

    public:
        Math();
        static int alea(int , int );

        static double alea(double , double );
    };

}
#endif // MATHUTILS_H
