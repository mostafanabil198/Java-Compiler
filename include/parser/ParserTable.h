#ifndef PARSERTABLE_H
#define PARSERTABLE_H

#include <bits/stdc++.h>
#include <iostream>

#define EPSILON "\\L"
#define SYNC "~sync~"

using namespace std;
class ParserTable
{
    public:
        static ParserTable* getInstance();
        // Productions table
        vector<vector<string>> get_production(string key);
        void add_production(string key, vector<string> production);
        unordered_map<string, vector<vector<string>>> get_productions_table();
        // Start table
        bool has_start(string key);
        vector<pair<string, vector<string>>> get_start(string key);
        void add_start(string key, pair<string, vector<string>> start);
        // Follow table
        unordered_set<string> get_follow(string key);
        void add_follow(string key, string follow);
        bool has_follow(string key);
        // Has Epsilon set
        bool has_epsilon(string key);
        void add_has_eps(string key);
        // Non Terminal set
        unordered_set<string> get_terminals();
        bool is_non_terminal(string word);
        void add_terminal(string terminal);
        // Parser Table
        bool add_parsing_table_entry(string non_terminal, string terminal, vector<string> production_entry);
        vector<string> get_parsing_table_entry(string non_terminal, string terminal);
        bool generate_parser_table();
        bool is_entry_empty();
        bool is_entry_epsilon();
        bool is_entry_sync();
        // Non Terminal Indexing
        vector<pair<string, pair<int, int>>> get_non_terminal_indexing(string non_terminal);
        void add_non_terminal_index(string non_terminal, pair<string, pair<int, int>> index);
        // First Non Terminal
        void set_first_non_terminal(string non_terminal);
        string get_first_non_terminal();
        // Printing Tables
        void print_productions();
        void print_parsing_table();
        void print_starts();
        void print_follows();
        void print_non_terminal_indexing();
        void print_has_eps();
        void print_terminals();

    protected:

    private:
        ParserTable();
        // key -> non-terminal ROW ... pair.kay -> terminal ... pair.value -> production cell
        unordered_map<string, unordered_map<string, vector<string>>> parsing_table;
        // key -> non-terminal ... vector contains vector for each production "which was separated by |"
        unordered_map<string, vector<vector<string>>> productions;
        // key -> non-terminal ROW ... 1st vector -> all starts of this non-terminal
        // pair-string -> the terminal 'the start symbol' ... inner-vector -> production that has this start
        unordered_map<string, vector<pair<string, vector<string>>>> starts;
        // key -> non-terminal ... vector of all following symbols
        unordered_map<string, unordered_set<string>> follows;
        // key -> non-terminal which we need to index ... vector -> all appearance of this non-terminal
        // pair-string -> the terminal which appeared in ... inner-pair: 1st-int -> the production it appeared in
        // 2nd-int -> the index in that production
        unordered_map<string, vector<pair<string, pair<int, int>>>> non_terminal_indexing;

        unordered_set<string> has_eps;
        unordered_set<string> terminals;
        //to start the stack with
        string first_non_terminal;

        void print_vector_string(vector<string> vec);
};


#endif // PARSERTABLE_H
