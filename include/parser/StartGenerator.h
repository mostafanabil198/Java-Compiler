#ifndef STARTGENERATOR_H
#define STARTGENERATOR_H
#include "ParserTable.h"
#include <bits/stdc++.h>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
class StartGenerator
{
    public:
        StartGenerator();
        void generate_start();
    protected:

    private:

        void get_starts(string non_terminal);
};

#endif // STARTGENERATOR_H
