#include "ReadRules.h"
#include <fstream>
#include <sstream>

ReadRules::ReadRules(string file_name)
{
   this->filename=file_name;
}

bool ReadRules::read_rules() {
    ifstream infile(this->filename);
    string line;
    Construct_Automata automata_c;
    if(infile.is_open()) {
        while (getline(infile, line)) {
            if(line.length() == 0 || line == " ")
                continue;
            automata_c.constructAutomata(line);
        }
        automata_c.constructNFA();
    return true;
    } else {
        return false;
    }


}
