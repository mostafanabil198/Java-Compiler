#ifndef READINPUT_H
#define READINPUT_H
#include <bits/stdc++.h>
#include "RegularDef.h"
#include "Node.h"
#include "DFA_minimization.h"

class ReadInput
{
public:
    ReadInput(string filename);
    void read_input_from_file();
    Node* get_next_state(Node* next_state, char input);
    void Output();
    vector<string> get_tokens();
    private:
    string file;
    vector<pair<Node*, map<RegularDef*, Node*>>>* transition_table;
    DFA_minimization * minimized_dfa;
    vector<string> tokens;
    vector <string> get_line_tokens(string line);

};

#endif // READINPUT_H
