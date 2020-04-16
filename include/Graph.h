#ifndef GRAPH_H
#define GRAPH_H
using namespace std;

#include <bits/stdc++.h>

#include "Edge.h"
#include "Node.h"
#include "RegularDef.h" 

class RegularDef;
class Node;
class Edge;
class Graph
{
    public:
    Graph();
    bool addEdge(Node * src, Node* Dest, RegularDef* weight);
    void mergeGraph(vector <Edge*> edges, vector <Node*> nodes);
    Node* get_start_state();
    Node* get_accept_state();
    vector<Node*> get_all_nodes();
    void set_start(Node* new_start);
    void set_accept_state(Node* new_accepted);
    vector<Edge*> get_tansitions();
    Node* getTargetNode(Node* src, RegularDef* weight);
    private :
       Node* start;
       Node* accept_state;
       vector<Node*> nodes;
       vector<Edge*> transitions;

};

#endif // GRAPH_H
