#ifndef NFA_H
#define NFA_H
using namespace std;

#include "ReadRules.h"
#include "Graph.h"

class NFA
{
    public:
        static NFA* get_instance();
        Graph* get_automata();
        void set_automata(Graph* graph);
        void read_input(string rules_file);

    protected:

    private:
        Graph* automata;
        NFA();
};

#endif // NFA_H
