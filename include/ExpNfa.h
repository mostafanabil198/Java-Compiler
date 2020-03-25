#ifndef EXPNFA_H
#define EXPNFA_H
using namespace std;
#include <bits/stdc++.h>

#include "Tokenizing.h"
#include "Graph.h"
#include "NFA.h"
#include "RegularDef.h"
#include "GeneralMethods.h"

#define EPS "eps"

class ExpNfa
{
public:
    ExpNfa();
    bool construct_automata(string line);
    bool construct_definition(string id, vector<string> definition);
    bool construct_nfa();
    void test_graph(Graph *pGraph);
    void construct_keywords(vector<string> tokens);
    void construct_punct(vector<string> tokens);
    void insert_def(vector<Edge *> edges);
    Graph *recurse_build(vector<string> tokens, int* i);
    Graph *recurse_brackets(vector<string> *pVector, int *pInt);
    Graph *create_char_graph(string basic_string, int *pInt);
    Graph *split_token(string basic_string, int *pInt, string h);
    Graph *create_graph(vector<string> *pVector, string basic_string, int *pInt, string h);
    Graph *create_graph_from_defintition(RegularDef* def, int* i, string temp);
    Graph *get_cont(Graph *d_g, vector<string> *tokens, int *i);
    Graph *expanded_graph(string tokens, int *i);
    string check_operation(vector<string> *pVector);
    vector<string> expand_def(string def);


protected:

private:
    vector<Graph*> exp_graphs;
    GeneralMethods* general_methods;
    int priority = 1;
    int node_id = 1;
    map<string, vector<string>> definitions;
};

#endif // EXPNFA_H
