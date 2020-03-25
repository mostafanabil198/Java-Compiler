#ifndef TOKENIZING_H
#define TOKENIZING_H
using namespace std;

#include <bits/stdc++.h>
#include <string>
#include <vector>
#include <list>
#include <cstring>
#include <sstream>
#include <algorithm>

#include "GeneralMethods.h"

class Tokenizing
{
    public:
        Tokenizing();
        vector<string> get_tokens(string line, char del);

    protected:

    private:
        vector<string> tokens;
        vector<string> def_symbols;
        void parse_string(string str);
};

#endif // TOKENIZING_H
