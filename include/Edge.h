#ifndef EDGE_H
#define EDGE_H
using namespace std;

#include <string>

#include "Node.h"
#include "RegularDef.h"

#define EPS "eps"
class RegularDef;
class Edge
{
    public:
        Edge(Node *src, Node *dst, RegularDef *weight);
        Node *get_src();
        Node *get_dest();
        RegularDef *get_weight();

    protected:

    private:
        Node *src;
        Node *dest;
        RegularDef *weight;
};

#endif // EDGE_H
