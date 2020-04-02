#include <iostream>

#include "ReadInput.h"
using namespace std;

int main()
{
    // params --> program, rules file, output file
    ReadInput *r = new ReadInput("Test/program.txt","Test/rules.txt" ,"tokens.txt");
    return 0;
}
