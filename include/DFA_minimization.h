#ifndef COMPILER_DFAMinimizer_H
#define COMPILER_DFAMinimizer_H

#include <vector>
#include <map>
#include <set>
#include<iterator>
#include <string.h>
#include <iostream>
#include "RegularDef.h"
#include "Node.h"
#include "DFA.h"
#include "Graph.h"
#include "GeneralMethods.h"
class DFA_minimization {
private:
    /* Here will be the instance stored. */
    static DFA_minimization* instance;
    /* Private constructor to prevent instancing. */
    DFA_minimization();

    vector<pair<Node*, map<RegularDef*, Node*>>> minimizedTransitionStateTable;
    DFA* dfa;
    set<Node*> Accepted;
    set<Node*> NotAccepted;
    vector<set<Node*>> previousPartition;
    vector<set<Node*>> nextPartition;
    Node* startState;

private:
    void set_first_partition(set<Node*> *Acc, set<Node*>* Not_Acc, vector<set<Node*>> *partitions);
    void partitioning(DFA* dfa, vector<set<Node*>>*pre, vector<set<Node*>> *next);
    void partitioningHelper(DFA* dfa, vector<set<Node*>>*pre,vector<set<Node*>>*next);
    void distinguish_states(DFA* dfa,vector<set<Node*>> *P , vector<set<Node*>> *n, set<Node*> curr);
    bool check_equivalent_states(DFA* dfa , vector<set<Node*>> *P, Node* A , Node *B);
    bool check_equal_partition(vector<set<Node*>> *P,vector<set<Node*>> *N);
    void build_min_dfa(DFA* dfa,vector<pair<Node*, map<RegularDef*, Node*>>>*ret, vector<set<Node*>> *partition);
    void get_start_state(Node *old, Node *current, set<Node *> &set1);
public:
    Node *get_start_state() const;

    void set_start_state(Node *startState);
    /* Static access method. */
    static DFA_minimization* get_instance();
    vector<pair<Node*,map<RegularDef*,Node*>>> *get_min_dfa();
    void printMinimizedDFA();




};


#endif
