#ifndef PARSER_H
#define PARSER_H

#include <bits/stdc++.h>
#include <iostream>

#include "StartGenerator.h"
#include "FollowGenerator.h"
#include "ParserOutput.h"
#include "ParserTable.h"

using namespace std;
class Parser
{
    public:
        Parser(string CFG_file);

    protected:

    private:
        StartGenerator start_generator;
        FollowGenerator follow_generator;
        ParserOutput parser_output;
        void read_rules(string CFG_file);
        string remove_spaces(string str);
        vector<string> split(string line, char del);
        vector<string> get_rule_elems(string lhs_non_terminal, int rule_index, string line);
        void add_non_terminal_index(string elem, string lhs_non_terminal, int rule_index, int i);
};

#endif // PARSER_H
