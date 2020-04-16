#include "Edge.h"

Edge::Edge(Node *src, Node *dest, RegularDef *weight)
{
    this->src = src;
    this->dest = dest;
    this->weight = weight;
}

Node* Edge::get_src() {
    return this->src;
}

Node* Edge::get_dest() {
    return this->dest;
}

RegularDef* Edge::get_weight() {
    return this->weight;
}
