#ifndef PARSER_H
#define PARSER_H

#include <bits/stdc++.h>
#include <iostream>

#include "StartGenerator.h"
#include "FollowGenerator.h"
#include "ParserOutput.h"

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
        void remove_spaces(string *str)
};

#endif // PARSER_H
