#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "axiom.h"
#include "terminal.h"
#include "nonterminal.h"
#include <QMap>
#include <QDebug>

namespace LSystem
{
    template<class T>
    class Grammar
    {
    private:
        Axiom<T>* m_axiom;
        QMap<QString, Terminal<T>*> m_terminalSymbol;
        QMap<QString, NonTerminal<T>*> m_productionRules;

    public:
        Grammar(){}
        virtual  ~Grammar()
        {
            delete m_axiom;

            foreach(Terminal<T>* t, m_terminalSymbol)
            {
                delete t;
            }

            foreach(NonTerminal<T>* nt, m_productionRules)
            {
                delete nt;
            }
        }

        T generation(const QVector<double>& params)
        {
            return m_axiom->start(params);
        }

        void setAxiom(Axiom<T>* a)
        {
            m_axiom = a->clone(this);
        }

        void addProductionRule(QString id, NonTerminal<T>* rules)
        {
            if(!m_productionRules.contains(id))
            {
                m_productionRules[id] = rules->clone(this);
            }
        }

        NonTerminal<T>* productionRule(QString id) const
        {
            if(m_productionRules.contains(id))
            {
                return m_productionRules[id];
            }
            else
            {
                return nullptr;
            }
        }

        void addTerminalSymbol(QString id, Terminal<T>* symbol)
        {
            if(!m_terminalSymbol.contains(id))
            {
                m_terminalSymbol[id] = symbol->clone(this);
            }
        }

        Terminal<T>* terminalSymbol(QString id) const
        {
            if(m_terminalSymbol.contains(id))
            {
                return m_terminalSymbol[id];
            }
            else
            {
                return nullptr;
            }
        }
    };
}
#endif // GRAMMAR_H
