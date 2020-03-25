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
class DFAMinimizer {
private:
    /* Here will be the instance stored. */
    static DFAMinimizer* instance;
    /* Private constructor to prevent instancing. */
    DFAMinimizer();

    vector<pair<Node*, map<RegularDef*, Node*>>> minimizedTransitionStateTable;
    DFA* dfa;
    set<Node*> Accepted;
    set<Node*> NotAccepted;
    vector<set<Node*>> previousPartition;
    vector<set<Node*>> nextPartition;
    Node* startState;

private:
    void setFirstPartition(set<Node*> *Acc, set<Node*>* Not_Acc, vector<set<Node*>> *partitions);
    void partitioning(DFA* dfa, vector<set<Node*>>*pre, vector<set<Node*>> *next);
    void partitioningHelper(DFA* dfa, vector<set<Node*>>*pre,vector<set<Node*>>*next);
    void distinguishStates(DFA* dfa,vector<set<Node*>> *P , vector<set<Node*>> *n, set<Node*> curr);
    bool areEquivalentStates(DFA* dfa , vector<set<Node*>> *P, Node* A , Node *B);
    bool isEqualPartition(vector<set<Node*>> *P,vector<set<Node*>> *N);
    void buildMinimizedDFA(DFA* dfa,vector<pair<Node*, map<RegularDef*, Node*>>>*ret, vector<set<Node*>> *partition);
    void findStartState(Node *old, Node *current, set<Node *> &set1);
public:
    Node *getStartState() const;

    void setStartState(Node *startState);
    /* Static access method. */
    static DFAMinimizer* getInstance();
    vector<pair<Node*,map<RegularDef*,Node*>>> *getMinimizedDFA();
    void printMinimizedDFA();

};


#endif
