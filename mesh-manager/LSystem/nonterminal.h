#ifndef NONTERMINAL_H
#define NONTERMINAL_H

#include "terminal.h"
#include <QList>
#include <QString>
namespace LSystem
{
    template<class T> class Grammar;

    template<class T>
    class NonTerminal
    {
    private:
        QString m_id;

    protected:
        Grammar<T>* m_parent;

    public:
        NonTerminal(QString id): m_id(id)
        {}
        NonTerminal(const NonTerminal<T>& nt): m_id(nt.m_id), m_parent(nt.m_parent)
        {}
        virtual ~NonTerminal() {}

        QString id() const;
        virtual T productionRules(QVector<double>) = 0;
        virtual NonTerminal<T>* clone(Grammar<T>*) const = 0;
    };
}
#endif // NONTERMINAL_H
