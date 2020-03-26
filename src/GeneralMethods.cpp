#include "GeneralMethods.h"
#include "ExpNfa.h"

static GeneralMethods* instance;

GeneralMethods::GeneralMethods()
{
    Graph* initial_graph = new Graph();
    Node* n = new Node(0);
    initial_graph->set_start(n);
    initial_graph->set_accept_state(n);
    initial_graph->get_start_state()->set_accepted_input("eps");
    this->insertInMap(EPS, new RegularDef(initial_graph));

    string symbols[] = {"|", "*", "\\+", "(", ")", ":", "=", "{", "}", "[", "]"};
        for(int i = 0; i < 11; i++) {
            def_symbols.push_back(symbols[i]);
        }
    eps = this->getDefinitions(EPS);
}

GeneralMethods* GeneralMethods::getInstance()
{
    if(instance == NULL) {
        instance = new GeneralMethods();
    }
    return instance;
}
map<string, RegularDef*> GeneralMethods::getTable()
{
        return this->definitions;
}
RegularDef* GeneralMethods::getDefinitions(string id)
{
       if(this->definitions.count(id)) return definitions[id];
        return NULL;
}
void GeneralMethods::insertInMap(string id, RegularDef* definition)
{
    this->definitions.insert(pair<string, RegularDef*>(id, definition));
}

vector<string> GeneralMethods::get_def_symbols() {
    return this->def_symbols;
}

Graph* GeneralMethods::mergeGraphs(Graph *graph_a, Graph *graph_b, string def_symbol, int* id) {

    if(def_symbol == "|")
        return mergeOr(graph_a, graph_b, id);
    if(def_symbol == "*")
        return mergeAst(graph_a, id);
    if(def_symbol == "\\+")
        return mergePlus(graph_a, id);
    if(def_symbol == ".")
        return mergeCont(graph_a, graph_b, id);


    return NULL;


}

Graph *GeneralMethods::mergeOr(Graph *graph_a, Graph *graph_b, int* i) {
    if(graph_b == NULL)
        return graph_a;
    if(graph_a == NULL)
        return graph_b;
    Node* end_first = graph_a->get_accept_state();
    Node* end_second = graph_b->get_accept_state();
    Node* start_first = graph_a->get_start_state();
    Node* start_second = graph_b->get_start_state();
    string id;
    id = end_first->get_accepted_input() + "|"+ end_second->get_accepted_input();


    end_first->set_accepted_input(normal_state);
    end_second->set_accepted_input(normal_state);

    Node* new_start = new Node((*i)++);
    new_start->set_accepted_input(normal_state);
    Node* new_end = new Node((*i)++);
    new_end->set_accepted_input(id);

    Graph* result_graph = graph_a;
    result_graph->mergeGraph(graph_b->get_tansitions(), graph_b->get_all_nodes());

    result_graph->addEdge(new_start, start_first,eps);
    result_graph->addEdge(new_start, start_second,eps);

    result_graph->addEdge(end_first, new_end,eps);
    result_graph->addEdge(end_second, new_end,eps);

    result_graph->set_start(new_start);
    result_graph->set_accept_state(new_end);

    return result_graph;
}

Graph *GeneralMethods::mergePlus(Graph *graph_a, int* i) {
    if(graph_a == NULL)
        return graph_a;
    Node* start_state = graph_a->get_start_state();
    Node* end_state = graph_a->get_accept_state();
    string id;
    id = end_state->get_accepted_input() + "+";
    end_state->set_accepted_input(normal_state);
    Node* new_start = new Node((*i)++);
    new_start->set_accepted_input(normal_state);
    Node* new_end = new Node((*i)++);
    new_end->set_accepted_input(id);

    Graph* result_graph = graph_a;
    result_graph->addEdge(new_start, start_state,eps);
    result_graph->addEdge(end_state, start_state,eps);
    result_graph->addEdge(end_state, new_end,eps);
    result_graph->set_start(new_start);
    result_graph->set_accept_state(new_end);
    return result_graph;
}

Graph *GeneralMethods::mergeAst(Graph *graph_a, int* i) {
    if(graph_a == NULL)
        return graph_a;

    Graph* result_graph = mergePlus(graph_a, i);
    string id;
    id = result_graph->get_accept_state()->get_accepted_input();
    id = id.substr(0, id.size()-1) + "*";
    result_graph->addEdge(result_graph->get_start_state(), result_graph->get_accept_state(), eps);
    result_graph->get_accept_state()->set_accepted_input(id);
    return result_graph;
}
Graph *GeneralMethods::mergeCont(Graph *graph_a, Graph *graph_b, int* i) {
    if(graph_b == NULL)
        return graph_a;
    if(graph_a == NULL)
        return graph_b;


    //the end state of graph_a will be the start state of graph_b by add an edge between them its weight is eps and set it as N_ACC
    Node* start_first = graph_a->get_start_state();
    Node* start_second = graph_b->get_start_state();
    Node* end_first = graph_a->get_accept_state();
    Node* end_second = graph_b->get_accept_state();

    string id;
    id = end_first->get_accepted_input() + " "+ end_second->get_accepted_input();

    end_first->set_accepted_input(normal_state);
    end_second->set_accepted_input(id);

    Graph* result_graph = graph_a;
    result_graph->mergeGraph(graph_b->get_tansitions(), graph_b->get_all_nodes());
    result_graph->addEdge(end_first, start_second,eps);
    result_graph->set_start(start_first);
    result_graph->set_accept_state(end_second);
    return result_graph;
}

bool GeneralMethods::is_def_symbol(string s) {
    for (int i = 0; i < def_symbols.size(); ++i) {
        if(s == def_symbols[i])
            return true;
    }
    return false;
}

void GeneralMethods::test_Definitions() {
    map<string, RegularDef*>::iterator it;
    ExpNfa* c = new ExpNfa();

    for ( it = definitions.begin(); it != definitions.end(); it++ )
    {
        std::cout << it->first  // string (key)
                  << ":" << endl;
                   c->test_graph(it->second->get_regular_def()) ; // string's value
                  cout << std::endl ;
    }
}
