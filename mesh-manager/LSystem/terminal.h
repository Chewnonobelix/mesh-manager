#ifndef TERMINAL_H
#define TERMINAL_H

#include "lsystem_global.h"

namespace LSystem
{
    template<class T>
    class LSYSTEMSHARED_EXPORT Terminal
    {
    public:
        Terminal(){}
        virtual T symbol(int pcase, double transformation) = 0;
    };
}
#endif // TERMINAL_H
