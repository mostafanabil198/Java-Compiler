#ifndef REGULARDEF_H
#define REGULARDEF_H
#include "Graph.h"
#include "DefTable.h"
#include <iostream>
#include <stack>
using namespace std;
class RegularDef
{
    public:
        RegularDef(Graph *regular_def);
        Graph *get_regular_def();
        bool set_regular_def(Graph *regular_def);
        Node *dfs(Node *start, int states_number, string input);
        bool accepts(string input);

    protected:

    private:
        Graph *regular_def;

};

#endif // REGULAR_DEF_H
