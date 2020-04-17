#include "ParserTable.h"

static ParserTable* instance;
ParserTable::ParserTable()
{

}

ParserTable* ParserTable::getInstance()
{
    if(instance == NULL)
    {
        instance = new ParserTable();
    }
    return instance;
}


vector<vector<string>> ParserTable::get_production(string key)
{
    return productions[key];
}

void ParserTable::add_production(string key, vector<string> production)
{
    productions[key].push_back(production);
}

unordered_map<string, vector<vector<string>>> ParserTable::get_productions_table()
{
    return this->productions;
}
// Start table
bool ParserTable::has_start(string key)
{
    return (starts.find(key) != starts.end());
}
bool ParserTable::has_follow(string key){
    return (follows.find(key) != follows.end());
}
vector<pair<string, vector<string>>> ParserTable::get_start(string key){
    return starts[key];
}
void ParserTable::add_start(string key, pair<string, vector<string>> start)
{
    starts[key].push_back(start);
}
// Follow table
unordered_set<string> ParserTable::get_follow(string key)
{
    return follows[key];
}
void ParserTable::add_follow(string key, string follow)
{
    follows[key].insert(follow);
}

bool ParserTable::has_epsilon(string key)
{
    return has_eps.find(key) != has_eps.end();
}
unordered_set<string> ParserTable::get_terminals()
{
    return terminals;
}
//unordered_map<string, unordered_map<string, vector<string>>> parsing_table;
//unordered_map<string, vector<pair<string, vector<string>>>> starts;
//unordered_map<string, vector<vector<string>>> productions;
//unordered_map<string, vector<string>> follows;
bool ParserTable::add_parsing_table_entry(string non_terminal, string terminal, vector<string> production_entry)
{
    if(parsing_table.find(non_terminal) != parsing_table.end())
    {
        pair<string, unordered_map<string, vector<string>>> t = *parsing_table.find(non_terminal);
        if (t.second.find(terminal) != t.second.end() )
        {
            return false;
        }
    }
    parsing_table[non_terminal][terminal] = production_entry;
    return true;
}
vector<string> ParserTable::get_parsing_table_entry(string non_terminal, string terminal)
{
    return parsing_table[non_terminal][terminal];
}

bool ParserTable::generate_parser_table()
{
    bool unambigous = true;
    for(auto production : productions)
    {
        string non_terminal = production.first;
        for(auto start : get_start(non_terminal))
        {
            if(start.first != "\L")
            {
                if(!add_parsing_table_entry(non_terminal, start.first, start.second))
                {
                    cout << "!!!!!!! Error! This code is ambiguous at non-terminal: " << non_terminal << " ,input: ";
                    cout << start.first << " :" << "     ->";
                    print_vector_string(start.second);
                    cout << endl << "     ->";
                    print_vector_string(get_parsing_table_entry(non_terminal, start.first));
                    cout << endl;
                    unambigous = false;
                }
            }
        }
        vector<string> follow_entry;
        if(has_epsilon(non_terminal))
        {
            follow_entry.push_back(EPSILON);
        }
        else
        {
            follow_entry.push_back(SYNC);
        }
        for(auto follow : get_follow(non_terminal))
        {
            if(!add_parsing_table_entry(non_terminal, follow, follow_entry))
            {
                cout << "!!!!!!! Error! This code is ambiguous at non-terminal: " << non_terminal << " ,input: ";
                cout << follow << " :" << "     ->";
                print_vector_string(follow_entry);
                cout << endl << "     ->";
                print_vector_string(get_parsing_table_entry(non_terminal, follow));
                cout << endl;
                unambigous = false;
            }
        }
    }
    return unambigous;
}
bool ParserTable::is_non_terminal(string word)
{
    return (productions.find(word) != productions.end());
}

void ParserTable::add_terminal(string terminal)
{
    terminals.insert(terminal);
}

vector<pair<string, pair<int, int>>> ParserTable::get_non_terminal_indexing(string non_terminal)
{
    return non_terminal_indexing[non_terminal];
}
void ParserTable::add_non_terminal_index(string non_terminal, pair<string, pair<int, int>> index)
{
    non_terminal_indexing[non_terminal].push_back(index);
}

void ParserTable::add_has_eps(string key)
{
    has_eps.insert(key);
}

void ParserTable::set_first_non_terminal(string non_terminal)
{
    first_non_terminal = non_terminal;
}

string ParserTable::get_first_non_terminal()
{
    return first_non_terminal;
}

void ParserTable::print_productions()
{
    cout << "========== Productions Table ==========" << endl;
    for(auto production : productions)
    {
        cout << production.first << ":" << endl;
        for( auto rule : production.second)
        {
            cout << "     ";
            for(auto elem : rule)
            {
                cout << elem << " ";
            }
            cout << endl;
        }
    }
}
void ParserTable::print_parsing_table()
{
    cout << "========== Parsing Table ==========" << endl;
    for(auto non_terminal : parsing_table)
    {
        cout << non_terminal.first << ":" << endl;
        for(auto terminal : non_terminal.second)
        {
            cout << "     " << terminal.first << "->";
            for( auto elem : terminal.second)
            {
                cout << elem << " ";
            }
        }
        cout << endl;
    }
}

void ParserTable::print_starts()
{
    cout << "========== Start Table ==========" << endl;
    for(auto non_terminal : starts)
    {
        cout << non_terminal.first << ":" << endl;
        for(auto input : non_terminal.second)
        {
            cout << "     " << input.first << "->";
            for( auto elem : input.second)
            {
                cout << elem << " ";
            }
            cout << endl;
        }
    }
}
void ParserTable::print_follows()
{
    cout << "========== Follow Table ==========" << endl;
    for(auto non_terminal : follows)
    {
        cout << non_terminal.first << ":";
        for( auto elem : non_terminal.second)
        {
            cout << elem << " ";
        }
        cout << endl;
    }
}
void ParserTable::print_non_terminal_indexing()
{
    cout << "========== Non-Terminal indexing Table ==========" << endl;
    for(auto non_terminal : non_terminal_indexing)
    {
        cout << non_terminal.first << ":" << endl;
        for(auto input : non_terminal.second)
        {
            cout << "     " << input.first << "->";
            cout << input.second.first << " ";
            cout << input.second.second;
            cout << endl;
        }
    }
}
void ParserTable::print_has_eps()
{
    cout << "========== Non Terminal Has Eps Table ==========" << endl;
    for(auto non_terminal : has_eps)
    {
        cout << non_terminal << " , ";
    }
    cout << endl;
}
void ParserTable::print_terminals()
{
    cout << "========== Terminals Table ==========" << endl;
    for(auto terminal : terminals)
    {
        cout << terminal << " , ";
    }
    cout << endl;
}

void ParserTable::print_vector_string(vector<string> vec)
{
    for(auto word : vec)
    {
        cout << word << " ";
    }
}
