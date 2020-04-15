#include "parser/Parser.h"

Parser::Parser(string CFG_file)
{
    read_rules(CFG_file);
}


void Parser::read_rules(string CFG_file){
    // open file and start reading *
    // read line by line --> check if it starts with # --> then its new production
    // if new --> remove # and split on = --> first is the non-terminal
    // second is the all rules --> split them on | --> then split on space
    // insert in productions table
    // insert in terminal table
    // insert in indexing table

    ifstream infile(CFG_file);
    string line;
    string lhs_non_terminal;
    if(infile.is_open()) {
        while (getline(infile, line)) {
            if(line.length() == 0 || line == " ") continue;
            if(line[0] == '#') { // new production

            }
        }
    } else {
    }
}

void Parser::remove_spaces(string *str)
{
    str->erase(remove(str->begin(), str->end(), ' '), str->end());
}
