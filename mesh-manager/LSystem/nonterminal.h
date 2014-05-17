#ifndef NONTERMINAL_H
#define NONTERMINAL_H

#include "lsystem_global.h"
#include "terminal.h"
#include <QList>

namespace LSystem
{
    template<class T>
    class LSYSTEMSHARED_EXPORT NonTerminal
    {
    private:
        QString m_id;

    public:
        NonTerminal(QString id): m_id(id){}
        QString id() const;
        virtual T productionRules(int pcase, double transformation) = 0;
    };
}
#endif // NONTERMINAL_H
