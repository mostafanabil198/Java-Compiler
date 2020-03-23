#ifndef NODE_H
#define NODE_H
#include "Edge.h"
#include <bits/stdc++.h>
using namespace std;
#define normal_state "none"

class Node
{
    public:
        Node(int id);
        string get_accepted_input();
        void set_accepted_input(string accepted_input);
        vector<Edge*> get_entering_edges();
        vector<Edge*> get_leaving_edges();
        int get_id();
        int get_priority();
        void set_priority(int priority);
        bool insert_edge(Edge* edge,bool entering);


    private:
    int id;
    vector<Edge*> entering_Edges;
    vector<Edge*> leaving_Edges;
    string accepted_input;
    int priority;
};

#endif // NODE_H
