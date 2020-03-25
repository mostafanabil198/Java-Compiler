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
    ReadRules(string file_name);
    bool read_rules();
};

#endif // READRULES_H
