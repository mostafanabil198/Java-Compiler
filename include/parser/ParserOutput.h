#ifndef PARSEROUTPUT_H
#define PARSEROUTPUT_H

#include <bits/stdc++.h>
#include <iostream>

using namespace std;
class ParserOutput
{
    public:
        ParserOutput();

    protected:

    private:
        stack<string> parsing_stack;
        vector<string> tokens;
        void derive();
};

#endif // PARSEROUTPUT_H
