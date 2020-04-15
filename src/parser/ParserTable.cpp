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
    productions[key].push_back(production);
}
// Start table
vector<pair<string, vector<string>>> ParserTable::get_start(string key){
    return starts[key];
}
void ParserTable::add_start(string key, pair<string, vector<string>> start){
    starts[key].push_back(start);
}
// Follow table
vector<string> ParserTable::get_follow(string key){
    return follows[key];
}
void ParserTable::add_follow(string key, string follow){
    follows[key].push_back(follow);
}

bool ParserTable::has_epsilon(string key){
    return has_eps.find(key) != has_eps.end();
}
unordered_set<string> ParserTable::get_terminals(){
    return terminals;
}
void ParserTable::generate_parser_table(){
    //
}

void ParserTable::add_terminal(string terminal){
    terminals.insert(terminal);
}

vector<pair<string, pair<int, int>>> ParserTable::get_non_terminal_indexing(string non_terminal){
    return non_terminal_indexing[non_terminal];
}
void ParserTable::add_non_terminal_index(string non_terminal, pair<string, pair<int, int>> index){
    non_terminal_indexing[non_terminal].push_back(index);
}

void ParserTable::add_has_eps(string key) {
    has_eps.insert(key);
}

void ParserTable::set_first_non_terminal(string non_terminal){
    first_non_terminal = non_terminal;
}

string ParserTable::get_first_non_terminal(){
    return first_non_terminal;
}

void ParserTable::print_productions(){
    cout << "========== Productions Table ==========" << endl;
    for(auto production : productions){
        cout << production.first << ":" << endl;
        for( auto rule : production.second){
            cout << "     ";
            for(auto elem : rule){
                cout << elem << " ";
            }
            cout << endl;
        }
    }
}
void ParserTable::print_parsing_table(){
    cout << "========== Parsing Table ==========" << endl;
    for(auto non_terminal : parsing_table){
        cout << non_terminal.first << ":" << endl;
        cout << "     " << non_terminal.second.first << "->";
        for( auto elem : non_terminal.second.second){
            cout << elem << " ";
        }
        cout << endl;
    }
}

void ParserTable::print_starts(){
    cout << "========== Start Table ==========" << endl;
    for(auto non_terminal : starts){
        cout << non_terminal.first << ":" << endl;
        for(auto input : non_terminal.second) {
            cout << "     " << input.first << "->";
            for( auto elem : input.second){
                cout << elem << " ";
            }
            cout << endl;
        }
    }
}
void ParserTable::print_follows(){
    cout << "========== Follow Table ==========" << endl;
    for(auto non_terminal : follows){
        cout << non_terminal.first << ":";
            for( auto elem : non_terminal.second){
                cout << elem << " ";
            }
        cout << endl;
    }
}
void ParserTable::print_non_terminal_indexing(){
    cout << "========== Non-Terminal indexing Table ==========" << endl;
    for(auto non_terminal : non_terminal_indexing){
        cout << non_terminal.first << ":" << endl;
        for(auto input : non_terminal.second) {
            cout << "     " << input.first << "->";
            cout << input.second.first << " ";
            cout << input.second.second;
            cout << endl;
        }
    }
}
void ParserTable::print_has_eps(){
    cout << "========== Non Terminal Has Eps Table ==========" << endl;
    for(auto non_terminal : has_eps) {
        cout << non_terminal << " , ";
    }
    cout << endl;
}
void ParserTable::print_terminals(){
    cout << "========== Terminals Table ==========" << endl;
    for(auto terminal : terminals) {
        cout << terminal << " , ";
    }
    cout << endl;
}
