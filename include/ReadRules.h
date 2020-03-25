#ifndef READRULES_H
#define READRULES_H
#include <bits/stdc++.h>
using namespace std;

class ReadRules
{
    private:
    string filename;
public:
    ReadRules(string file_name);
    bool read_rules();
};

#endif // READRULES_H
