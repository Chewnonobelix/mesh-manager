#ifndef TERMINAL_H
#define TERMINAL_H

#include <QString>

namespace LSystem
{
    template<class T> class Grammar;

    template<class T>
    class Terminal
    {
    private:
        QString m_id;

    protected:
        Grammar<T>* m_parent;

    public:
        Terminal(QString id):  m_id(id){}

        Terminal(const Terminal<T>& t):  m_id(t.m_id), m_parent(t.m_parent)
        {}

        virtual ~Terminal() {}

        QString id() const
        {
            return m_id;
        }

        virtual T symbol(QVector<double>) = 0;
        virtual Terminal<T>* clone(Grammar<T>*) const = 0;
    };
}
#endif // TERMINAL_H
