#ifndef GENERALMETHODS_H
#define GENERALMETHODS_H
using namespace std;

#include <bits/stdc++.h>
#include <iostream>

#include "RegularDef.h"
#include "Graph.h"

class RegularDef;
class Graph;
class GeneralMethods
{
    public:
    static GeneralMethods* getInstance();
    map<string, RegularDef*> getTable();
    RegularDef* getDefinitions(string id);
    void insertInMap(string id, RegularDef* definition);

    Graph* mergeGraphs(Graph* graph_a, Graph* graph_b, string def_symbol, int* id);
    vector<string> get_def_symbols();

    Graph *mergeOr(Graph *graph_a, Graph *graph_b, int* id);

    Graph *mergePlus(Graph *graph_a, int* id);

    Graph *mergeAst(Graph *graph_a, int* id);

    Graph *mergeCont(Graph *graph_a, Graph *graph_b, int* id);
    void test_Definitions();

    bool is_def_symbol(string s);
    private:
    map<string, RegularDef*> definitions;
    vector<string> def_symbols;
    RegularDef *eps;
    GeneralMethods();
};

#endif // DEFTABLE_H
