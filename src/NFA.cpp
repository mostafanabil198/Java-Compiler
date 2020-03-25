#include "NFA.h"

static NFA* instance;

NFA::NFA()
{
}

NFA* NFA::get_instance() {
    if(instance == NULL)
        instance = new NFA();
    return instance;
}

Graph* NFA::get_automata() {
    return this->automata;
}

void NFA::set_automata(Graph *graph) {
    this->automata = graph;
}


void NFA::read_input() {
    ReadRules *t = new ReadRules(""); //-
    t->read_rules();
}
