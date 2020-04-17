#ifndef PARSEROUTPUT_H
#define PARSEROUTPUT_H
#include "ParserTable.h"
#include <bits/stdc++.h>
#include <iostream>
#include <stack>

using namespace std;
class ParserOutput
{
    public:
        ParserOutput();
        void derive(vector<string> tokens);

    protected:

    private:
        stack<string> parsing_stack;
};

#endif // PARSEROUTPUT_H
