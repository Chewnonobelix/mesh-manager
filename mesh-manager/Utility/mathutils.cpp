#include "mathutils.h"

using namespace MathUtility;

bool Math::m_init = false;

Math::Math()
{

}

int Math::alea(int min, int max)
{
    if(!m_init)
    {
        srand(time(NULL));
        m_init = true;
    }
    return (rand()%(max - min)) + min;
}

double  Math::alea(double min, double max)
{
    if(!m_init)
    {
        srand(time(NULL));
        m_init = true;
    }
    return (rand()/(double)RAND_MAX)*(max-min)+min;
}
