#include "Graph.h"
#include <bits/stdc++.h>
#include "Node.h"
using namespace std;

Graph::Graph()
{
    start = NULL;
    accept_state = NULL;
    nodes.clear();
    transitions.clear();
}

bool Graph::addEdge(Node * src, Node* Dest, RegularDef* weight)
{
    if(this->getTargetNode(src, weight )== Dest)
        return false;
    if(find(nodes.begin(), nodes.end(), src) == nodes.end())
        this->nodes.push_back(src);
    if(find(nodes.begin(), nodes.end(),Dest ) == nodes.end())
        this->nodes.push_back(Dest);
    if(this->getTargetNode(src, weight) == Dest)
        return false;
    Edge* transition = new Edge(src, Dest, weight);
    src->insert_edge(transition, false);
    Dest->insert_edge(transition, true);
    this->transitions.push_back(transition);
    return true;

}
void Graph::mergeGraph(vector<Edge*> edges, vector<Node*> nodes)
{
    for (int i = 0; i < edges.size() ; ++i)
    {
        this->transitions.push_back(edges[i]);
    }
    for (int i = 0; i < nodes.size() ; ++i)
    {
        this->nodes.push_back(nodes[i]);
    }
}


Node* Graph::get_start_state()
{
    return this->start;
}
Node* Graph::get_accept_state()
{
    return this->accept_state;

}
vector<Node*> Graph::get_all_nodes()
{
    return nodes;
}
void Graph::set_start(Node* new_start)
{
    if(find(nodes.begin(), nodes.end(), new_start) == nodes.end())
        this->nodes.push_back(new_start);
    this->start=new_start;
}
void Graph::set_accept_state(Node* new_accepted)
{
    if(find(nodes.begin(), nodes.end(), new_accepted) == nodes.end())
        this->nodes.push_back(new_accepted);
    this->accept_state=new_accepted;
}
vector<Edge*> Graph::get_tansitions()
{
    return this->transitions;
}
Node* Graph::getTargetNode(Node* src, RegularDef* weight)
{
    if(find(nodes.begin(), nodes.end(), src) == nodes.end())
        return NULL;
    vector<Edge*> outward = src->get_leaving_edges();
    for(int i = 0; i < outward.size(); i++)
    {
        if(outward[i]->get_weight() == weight)
        {
            return outward[i]->get_dest();
        }
    }
    return NULL;
}
