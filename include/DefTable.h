#ifndef DEFTABLE_H
#define DEFTABLE_H
#include <bits/stdc++.h>
#include "RegularDef.h"
#include "Graph.h"
using namespace std;
class RegularDef;
class Graph;
class DefTable
{
    public:
    static DefTable* getInstance();
    map<string, RegularDef*> getTable();
    RegularDef* getDefinitions(string id);
    void insertInMap(string id, RegularDef* definition);

    Graph* mergeGraphs(Graph* graph_1, Graph* graph_2h, string helper, int* id);
    vector<string> get_helpers();

    Graph *mergeOr(Graph *pGraph, Graph *graph_2, int* id);

    Graph *mergePlus(Graph *pGraph, int* id);

    Graph *mergeAst(Graph *pGraph, int* id);

    Graph *mergeCont(Graph *pGraph, Graph *graph_2, int* id);

    bool isAhelper(string s);
    private:
    map<string, RegularDef*> definitions;
    vector<string> helpers;
    RegularDef *eps;
     DefTable();
};

#endif // DEFTABLE_H
