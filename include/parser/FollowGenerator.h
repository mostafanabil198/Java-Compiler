#ifndef FOLLOWGENERATOR_H
#define FOLLOWGENERATOR_H
#include "ParserTable.h"
#include <bits/stdc++.h>
#include <iostream>

using namespace std;

class FollowGenerator
{
    public:
        FollowGenerator();
        void generate_follow();

    protected:

    private:
        void get_follow(string non_terminal);
        bool finish = false;
        void evaluate_next_production(vector<vector<string>> current,int i, int j,string non_terminal);
};

#endif // FOLLOWGENERATOR_H
