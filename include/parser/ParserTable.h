#ifndef PARSERTABLE_H
#define PARSERTABLE_H

#include <bits/stdc++.h>
#include <iostream>

#define EPSILON "\\L"

using namespace std;
class ParserTable
{
    public:
        static ParserTable* getInstance();
        // Productions table
        vector<vector<string>> get_production(string key);
        void add_production(string key, vector<string> production);
        // Start table
        vector<pair<string, vector<string>>> get_start(string key);
        void add_start(string key, pair<string, vector<string>> start);
        // Follow table
        vector<string> get_follow(string key);
        void add_follow(string key, string follow);
        // Has Epsilon set
        bool has_epsilon(string key);
        void add_has_eps(string key);

        vector<string> get_terminals();
        void add_terminal(string terminal);
        void generate_parser_table();

        vector<pair<string, pair<int, int>>> get_non_terminal_indexing(string non_terminal);
        void add_non_terminal_index(string non_terminal, pair<string, pair<int, int>> index);

        void set_first_non_terminal(string non_terminal);
        string get_first_non_terminal();

    protected:

    private:
        ParserTable();
        // key -> non-terminal ROW ... pair.kay -> terminal ... pair.value -> production cell
        unordered_map<string, pair<string, vector<string>>> parsing_table;
        // key -> non-terminal ... vector contains vector for each production "which was separated by |"
        unordered_map<string, vector<vector<string>>> productions;
        // key -> non-terminal ROW ... 1st vector -> all starts of this non-terminal
        // pair-string -> the terminal 'the start symbol' ... inner-vector -> production that has this start
        unordered_map<string, vector<pair<string, vector<string>>>> starts;
        // key -> non-terminal ... vector of all following symbols
        unordered_map<string, vector<string>> follows;
        // key -> non-terminal which we need to index ... vector -> all appearance of this non-terminal
        // pair-string -> the terminal which appeared in ... inner-pair: 1st-int -> the production it appeared in
        // 2nd-int -> the index in that production
        unordered_map<string, vector<pair<string, pair<int, int>>>> non_terminal_indexing;

        unordered_set<string> has_eps;
        vector<string> terminals;
        string first_non_terminal;

};


#endif // PARSERTABLE_H
