#ifndef AXIOM_H
#define AXIOM_H

#include "lsystem_global.h"
#include "terminal.h"


namespace LSystem
{
/**
 * @class Axiom
 * @brief Classe représentation un axiome d'une grammaire/L-system, i.e son point départ
 * @tparam T Type renvoier par la grammaire, doit supporté une opération de concaténation
 */
    template<class T>
    class LSYSTEMSHARED_EXPORT Axiom
    {
    public:
        Axiom(){}
        virtual Axiom* clone() const = 0;
        virtual T start(int pcase, double transformation) = 0;
    };
}
#endif // AXIOM_H
