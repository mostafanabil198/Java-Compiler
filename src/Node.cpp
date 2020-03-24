#include "Node.h"
#include "Edge.h"
#include <bits/stdc++.h>
Node::Node(int id)
{
   this->id=id;
   this->accepted_input=normal_state;
   this->priority=-1;
}
string Node::get_accepted_input(){
    return this->accepted_input;
}

void Node::set_accepted_input(string accepted_input){
this->accepted_input=accepted_input;
}

vector<Edge*> Node::get_entering_edges() {
    return this->entering_Edges;
}

vector<Edge*> Node::get_leaving_edges() {
    return this->leaving_Edges;
}

int Node::get_id() {
    return id;
}

void Node::set_priority(int priority) {
    this->priority = priority;
}
int Node::get_priority() {
    return  this->priority;
}

bool Node::insert_edge(Edge *edge, bool entering) {
    if(entering) {
        if(find(entering_Edges.begin(), entering_Edges.end(), edge) != entering_Edges.end())
            return false;
        entering_Edges.push_back(edge);
    } else {
        if(find(leaving_Edges.begin(), leaving_Edges.end(), edge) != leaving_Edges.end())
            return false;
        leaving_Edges.push_back(edge);
    }
    return true;
}
