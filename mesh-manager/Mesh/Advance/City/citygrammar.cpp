#include "citygrammar.h"

CityGrammar::CityGrammar()
{
    CityAxiom a;
    AvenueNT b;
    RueNT c;
    RueT d;
    AvenueT e;
    MaisonT f;
    ImmeubleT g;
    AutreT h;

    setAxiom(&a);
    addProductionRule("Avenue", &b);
    addProductionRule("Rue", &c);

    addTerminalSymbol("Rue",&d);
    addTerminalSymbol("Avenue",&e);
    addTerminalSymbol("Maison", &f);
    addTerminalSymbol("Immeuble", &g);
    addTerminalSymbol("Autre", &h);
}
