#include <iostream>

#include "ReadInput.h"
#include "Parser.h"
using namespace std;


int main()
{
    // params --> program, rules file, output file
    //ReadInput *r = new ReadInput("Test/program.txt","Test/rules.txt" ,"tokens.txt");
    Parser *parser = new Parser("Test/lec_cfg_error_rules.txt");
    return 0;
}


