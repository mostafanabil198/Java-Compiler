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

bool NFA::set_automata(Graph *graph) {
    this->automata = graph;
}


void NFA::read_input() {
    Read_Input *t = new Read_Input("F:/2nd semester third year/2nd Semester/1 Compilers/4 Labs/Compiler/Test/input.txt"); //-
    t->read_file();
}
