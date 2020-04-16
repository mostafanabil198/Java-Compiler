#ifndef READINPUT_H
#define READINPUT_H
using namespace std;

#include <bits/stdc++.h>
#include <fstream>
#include <sstream>

#include "RegularDef.h"
#include "Node.h"
#include "DFA_minimization.h"

class ReadInput
{
public:
    ReadInput(string program_file, string rules_file, string output_file);
    void read_input_from_file(string output_file);
    Node* get_next_state(Node* next_state, char input);
    void Output(string output_file);
    vector<string> get_tokens();
    private:
    string file;
    vector<pair<Node*, map<RegularDef*, Node*>>>* transition_table;
    DFA_minimization * minimized_dfa;
    vector<string> tokens;
    vector <string> get_line_tokens(string line);

};

#endif // READINPUT_H
