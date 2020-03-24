#ifndef DEFTABLE_H
#define DEFTABLE_H
#include <bits/stdc++.h>
#include "RegularDef.h"

class DefTable
{
    public:
    static DefTable* getInstance();
    map<string, RegularDef*> getTable();
    RegularDef* getDefinitions(string id);
    void insertInMap(string id, RegularDef* definition);

    private:
    map<string, RegularfDef*> definitions;
     DefTable();
};

#endif // DEFTABLE_H
