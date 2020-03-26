#ifndef DFA_H
#define DFA_H
using namespace std;

#include <vector>
#include <map>
#include <set>
#include <list>
#include <iostream>
#include <algorithm>

#include "RegularDef.h"
#include "Node.h"
#include "NFA.h"
#include "GeneralMethods.h"


class DFA {
private:
    /* Here will be the instance stored. */
    static DFA* instance;
    /* Private constructor to prevent instancing. */
    DFA();

    map< Node*,  map<RegularDef*,set<Node*>>> nfa_table;
    vector< set<Node*>>  stateMappingTable;
    vector< pair <Node*,  map<RegularDef*,Node*>>>  transition_table;
    set<Node*> get_transition_states(Node* state, RegularDef* def);
    set<Node*> get_epsilon_closure(Node* state);
    Node* get_highest_priority(set<Node*> set);
    void create_new_row(Node* node);
    void BFS(Node* start);
    void testDFA();
    set<Node*> loop_definition(RegularDef* def, Node* node);
    int table_with_same_state(set<Node*> state);

public:
    /* Static access method. */
    static DFA* get_instance();
    vector< pair <Node*,  map<RegularDef*, Node*>>>   get_dfa();
};


#endif
