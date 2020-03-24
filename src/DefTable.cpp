#include "DefTable.h"
#include "RegularDef.h"
#include <bits/stdc++.h>
#include <iostream>

static DefTable* instance;

DefTable::DefTable()
{
    Graph* initial_graph = new Graph();
    Node* n = new Node(0);
    initial_graph->set_start(n);
    initial_graph->set_accept_state(n);
    initial_graph->get_start_state()->set_accepted_input("eps");
    this->insertInMap(EPS, new RegularDef(initial_graph));

    ifstream infile("F:/2nd semester third year/2nd Semester/1 Compilers/4 Labs/Compiler/Automata/Helpers.txt");
    string line;
    if(infile.is_open()) {
        while (getline(infile, line)) {
            helpers.push_back(line);
        }
    }
    eps = this->getDefinitions(EPS);
}

DefTable* DefTable::getInstance()
{
    if(instance == NULL) {
        instance = new DefTable();
    }
    return instance;
}
map<string, RegularDef*> DefTable::getTable()
{
        return this->definitions;
}
RegularDef* DefTable::getDefinitions(string id)
{
       if(this->definitions.count(id)) return definitions[id];
        return NULL;
}
void DefTable::insertInMap(string id, RegularDef* definition)
{
    this->definitions.insert(pair<string, RegularDef*>(id, definition));
}

vector<string> DefTable::get_helpers() {
    return this->helpers;
}

Graph* DefTable::mergeGraphs(Graph *graph_A, Graph *graph_B, string helper, int* id) {

    if(helper == "|")
        return mergeOr(graph_A, graph_B, id);
    if(helper == "*")
        return mergeAst(graph_A, id);
    if(helper == "\\+")
        return mergePlus(graph_A, id);
    if(helper == ".")
        return mergeCont(graph_A, graph_B, id);


    return NULL;


}

Graph *DefTable::mergeOr(Graph *graph_A, Graph *graph_B, int* i) {
    if(graph_B == NULL)
        return graph_A;
    if(graph_A == NULL)
        return graph_B;
    Node* end_first = graph_A->get_accept_state();
    Node* end_second = graph_B->get_accept_state();
    Node* start_first = graph_A->get_start_state();
    Node* start_second = graph_B->get_start_state();
    string id;
    id = end_first->get_accepted_input() + "|"+ end_second->get_accepted_input();


    end_first->set_accepted_input(normal_state);
    end_second->set_accepted_input(normal_state);

    Node* new_start = new Node((*i)++);
    new_start->set_accepted_input(normal_state);
    Node* new_end = new Node((*i)++);
    new_end->set_accepted_input(id);

    Graph* result_graph = graph_A;
    result_graph->mergeGraph(graph_B->get_tansitions(), graph_B->get_all_nodes());

    result_graph->addEdge(new_start, start_first,eps);
    result_graph->addEdge(new_start, start_second,eps);

    result_graph->addEdge(end_first, new_end,eps);
    result_graph->addEdge(end_second, new_end,eps);

    result_graph->set_start(new_start);
    result_graph->set_accept_state(new_end);

    return result_graph;
}

Graph *DefTable::mergePlus(Graph *graph_A, int* i) {
    if(graph_A == NULL)
        return graph_A;
    Node* start_state = graph_A->get_start_state();
    Node* end_state = graph_A->get_accept_state();
    string id;
    id = end_state->get_accepted_input() + "+";
    end_state->set_accepted_input(normal_state);
    Node* new_start = new Node((*i)++);
    new_start->set_accepted_input(normal_state);
    Node* new_end = new Node((*i)++);
    new_end->set_accepted_input(id);

    Graph* result_graph = graph_A;
    result_graph->addEdge(new_start, start_state,eps);
    result_graph->addEdge(end_state, start_state,eps);
    result_graph->addEdge(end_state, new_end,eps);
    result_graph->set_start(new_start);
    result_graph->set_accept_state(new_end);
    return result_graph;
}

Graph *DefTable::mergeAst(Graph *graph_A, int* i) {
    if(graph_A == NULL)
        return graph_A;

    Graph* result_graph = mergePlus(graph_A, i);
    string id;
    id = result_graph->get_accept_state()->get_accepted_input();
    id = id.substr(0, id.size()-1) + "*";
    result_graph->addEdge(result_graph->get_start_state(), result_graph->get_accept_state(), eps);
    result_graph->get_accept_state()->set_accepted_input(id);
    return result_graph;
}
Graph *DefTable::mergeCont(Graph *graph_A, Graph *graph_B, int* i) {
    if(graph_B == NULL)
        return graph_A;
    if(graph_A == NULL)
        return graph_B;


    //the end state of graph_A will be the start state of graph_B by add an edge between them its weight is eps and set it as N_ACC
    Node* start_first = graph_A->get_start_state();
    Node* start_second = graph_B->get_start_state();
    Node* end_first = graph_A->get_accept_state();
    Node* end_second = graph_B->get_accept_state();

    string id;
    id = end_first->get_accepted_input() + " "+ end_second->get_accepted_input();

    end_first->set_accepted_input(normal_state);
    end_second->set_accepted_input(id);

    Graph* result_graph = graph_A;
    result_graph->mergeGraph(graph_B->get_tansitions(), graph_B->get_all_nodes());
    result_graph->addEdge(end_first, start_second,eps);
    result_graph->set_start(start_first);
    result_graph->set_accept_state(end_second);
    return result_graph;
}

bool DefTable::isAhelper(string s) {
    for (int i = 0; i < helpers.size(); ++i) {
        if(s == helpers[i])
            return true;
    }
    return false;
}
