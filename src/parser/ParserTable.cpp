#include "ParserTable.h"

static ParserTable* instance;
ParserTable::ParserTable()
{

}

ParserTable* ParserTable::getInstance()
{
    if(instance == NULL) {
        instance = new ParserTable();
    }
    return instance;
}


vector<vector<string>> ParserTable::get_production(string key){
    return productions[key];
}

void ParserTable::add_production(string key, vector<string> production){
    productions[key].push_back()
}
// Start table
vector<pair<string, vector<string>>> ParserTable::get_start(string key){
    vector<pair<string, vector<string>>> x;
    return x;
}
void ParserTable::add_start(string key, pair<string, vector<string>>){
}
// Follow table
vector<string> ParserTable::get_follow(string key){
    vector<string> x;
    return x;
}
void ParserTable::add_follow(string key, string follow){

}

bool ParserTable::has_epsilon(string key){
    return false;
}
vector<string> ParserTable::get_terminals(){
    vector<string> x;
    return x;
}
void ParserTable::generate_parser_table(){

}

void ParserTable::add_terminal(string terminal){
}

vector<pair<string, pair<int, int>>> ParserTable::get_non_terminal_indexing(string non_terminal){
    vector<pair<string, pair<int, int>>> x;
    return x;
}
void ParserTable::add_non_terminal_index(string non_terminal, pair<string, pair<int, int>> index){

}

void ParserTable::add_has_eps(string key) {

}

void ParserTable::set_first_non_terminal(string non_terminal){
}

string ParserTable::get_first_non_terminal(){
    string x;
    return x;
}
