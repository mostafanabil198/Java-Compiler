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
    static DFA* instance;
    DFA(string rules_file);

    map< Node*, map<RegularDef*, set<Node*>>> nfa_table;
    vector< set<Node*>> stateMappingTable;
    vector< pair <Node*, map<RegularDef*,Node*>>> transition_table;
    set<Node*> get_transition_states(Node* state, RegularDef* def);
    set<Node*> get_epsilon_closure(Node* state);
    Node* get_highest_priority(set<Node*> set);
    void create_new_row(Node* node);
    void BFS(Node* start);
    void testDFA();
    set<Node*> loop_definition(RegularDef* def, Node* node);
    int table_with_same_state(set<Node*> state);

public:
    static DFA* get_instance(string rules_file);
    vector< pair <Node*, map<RegularDef*, Node*>>> get_dfa();
};


#endif
