#include "grammartree.h"

GrammarTree::GrammarTree()
{
    TrunkNT tnt;
    TrunkT tt;
    BranchNT bnt;
    BranchT bt;
    TreeAxiom ta;

    addProductionRule("TrunkNT", &tnt);
    addProductionRule("BranchNT", &bnt);
    addTerminalSymbol("TrunkT", &tt);
    addTerminalSymbol("BranchT", &bt);
    setAxiom(&ta);
}
