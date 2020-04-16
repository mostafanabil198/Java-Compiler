#ifndef REGULARDEF_H
#define REGULARDEF_H
using namespace std;
#include <iostream>
#include <stack>

#include "Graph.h"
#include "GeneralMethods.h"

class RegularDef
{
    public:
        RegularDef(Graph *regular_def);
        Graph *get_regular_def();
        void set_regular_def(Graph *regular_def);
        Node *dfs(Node *start, int states_number, string input);
        bool accepts(string input);

    protected:

    private:
        Graph *regular_def;
};

#endif // REGULARDEF_H
