#include "ReadRules.h"

ReadRules::ReadRules(string file_name)
{
   this->filename=file_name;
}

bool ReadRules::read_rules() {
    ifstream infile(this->filename);
    string line;
    ExpNfa automata_c;
    if(infile.is_open()) {
        while (getline(infile, line)) {
            if(line.length() == 0 || line == " ")
                continue;
            automata_c.construct_automata(line);
        }
        automata_c.construct_nfa();
    return true;
    } else {
        return false;
    }

}
