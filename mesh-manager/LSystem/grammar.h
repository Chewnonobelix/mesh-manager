#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "lsystem_global.h"
#include "axiom.h"
#include "terminal.h"
#include "nonterminal.h"
#include <QMap>

namespace LSystem
{
    template<class T>
    class LSYSTEMSHARED_EXPORT Grammar
    {
    private:
        Axiom<T>* m_axiom;
        QMap<QString, Terminal<T>*> m_terminalSymbol;
        QMap<QString, NonTerminal<T>*> m_productionRules;

    public:
        Grammar(){}
        ~Grammar()
        {
            delete m_axiom;
        }

        T generation(int pcase, double transformation)
        {
            return m_axiom->start(pcase, transformation);
        }

        void setAxiom(const Axiom<T>& a)
        {
            m_axiom = a.clone();
        }
    };
}
#endif // GRAMMAR_H
