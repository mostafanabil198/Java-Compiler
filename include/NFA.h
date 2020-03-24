#ifndef NFA_H
#define NFA_H
using namespace std;

//#include "ReadInput.h"
#include "Graph.h"

class NFA
{
    public:
        static NFA* get_instance();
        Graph* get_automata();
        void set_automata(Graph* graph);
        void read_input();

    protected:

    private:
        Graph* automata;
        NFA();
};

#endif // NFA_H
