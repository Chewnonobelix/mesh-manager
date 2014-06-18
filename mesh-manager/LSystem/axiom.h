#ifndef AXIOM_H
#define AXIOM_H

#include "terminal.h"

namespace LSystem
{
    template<class T> class Grammar;
/**
 * @class Axiom
 * @brief Classe représentation un axiome d'une grammaire/L-system, i.e son point départ
 * @tparam T Type renvoier par la grammaire, doit supporté une opération de concaténation
 */
    template<class T>
    class Axiom
    {
    protected:
        Grammar<T>* m_parent;
    public:
        Axiom(){}
        virtual ~Axiom() {}
        Axiom(const Axiom<T>& a): m_parent(a.m_parent)
        {}

        virtual Axiom<T>* clone(Grammar<T>*) const = 0;
        virtual T start(QVector<double>) = 0;
    };
}
#endif // AXIOM_H
