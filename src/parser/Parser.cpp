#include "parser/Parser.h"

Parser::Parser(string CFG_file)
{
    read_rules(CFG_file);

    ParserTable::getInstance()->print_productions();
    ParserTable::getInstance()->print_non_terminal_indexing();

    ParserTable::getInstance()->print_has_eps();
    ParserTable::getInstance()->print_terminals();
    start_generator.generate_start();
    ParserTable::getInstance()->print_starts();
}


void Parser::read_rules(string CFG_file)
{
    // open file and start reading *
    // read line by line --> check if it starts with # --> then its new production *
    // if new --> remove # and split on = --> first is the non-terminal *
    // second is the all rules --> split them on | --> then split on space *
    // insert in productions table *
    // insert in terminal table *
    // insert in indexing table *

    ifstream infile(CFG_file);
    string line;
    string lhs_non_terminal;
    int rule_index;
    int rule_number = 0;
    if(infile.is_open())
    {
        while (getline(infile, line))
        {
            if(line.length() == 0 || line == " ")
                continue;
            vector<string> production_rules;
            if(line[0] == '#')   // new production
            {
            rule_number++;
                line = line.substr(1, line.size() - 1);
                vector<string> production_elems = split2(line, " = ");
                lhs_non_terminal = remove_spaces(production_elems[0]);
                if(rule_number == 1) ParserTable::getInstance()->set_first_non_terminal(lhs_non_terminal);
                rule_index = 0;
                production_rules = split2(production_elems[1], "| ");
            }
            else
            {
                production_rules = split2(line, "| ");
            }
            for(int i = 0; i < production_rules.size(); i++)
            {
                vector<string> rule_elems = get_rule_elems(lhs_non_terminal, rule_index++, production_rules[i]);
                ParserTable::getInstance()->add_production(lhs_non_terminal, rule_elems);
            }
        }
    }
    else
    {
        cout << "Error!! .. File not found";
    }
}

string Parser::remove_spaces(string str)
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

vector<string> Parser::get_rule_elems(string lhs_non_terminal, int rule_index, string line)
{
    vector<string> elems;
    stringstream ssin(line);
    string elem;
    int i = 0;
    while(ssin >> elem)
    {
        if(elem[0] == '\'' && elem[elem.size()-1] == '\''){
            elem = elem.substr(1, elem.size() - 2);
            ParserTable::getInstance()->add_terminal(elem);
        } else if (elem == EPSILON) {
            //ParserTable::getInstance()->add_terminal(elem);
            ParserTable::getInstance()->add_has_eps(lhs_non_terminal);
        } else {
            add_non_terminal_index(elem, lhs_non_terminal, rule_index, i);
        }
        elems.push_back(elem);
        i++;
    }
    return elems;
}

void Parser::add_non_terminal_index(string elem, string lhs_non_terminal, int rule_index, int i){
    pair<string, pair<int, int>> index;
    index = make_pair(lhs_non_terminal, make_pair(rule_index, i));
    ParserTable::getInstance()->add_non_terminal_index(elem, index);
}

vector<string> Parser::split2(string line, string del){
    vector<string> words;
    size_t pos = 0;
    string word;
    while ((pos = line.find(del)) != string::npos) {
        word = line.substr(0, pos);
        if(word != "" && word != " ") words.push_back(word);
        line.erase(0, pos + del.length());
    }
    if(line != "" && line != " ") words.push_back(line);
    return words;
}

vector<string> Parser::split(string line, char del)
{
    std::istringstream line_stream(line);
    std::string word;
    vector<string> words;
    // get word by word separated by a del
    while(std::getline(line_stream, word, del))
    {
        if(word != "" && word != " ") words.push_back(word);
    }
    return words;
}

