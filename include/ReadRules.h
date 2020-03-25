#ifndef READRULES_H
#define READRULES_H
using namespace std;
#include <bits/stdc++.h>

#include "ExpNfa.h"

class ReadRules
{
    private:
    string filename;
public:
    ReadRules(string filename);
    bool read_rules();
};

#endif // READRULES_H
