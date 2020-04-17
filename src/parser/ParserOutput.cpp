#include "ParserOutput.h"

ParserOutput::ParserOutput()
{

}


void ParserOutput:: derive(vector<string> tokens)
{

    parsing_stack.push("$");
    parsing_stack.push(ParserTable::getInstance()->get_first_non_terminal());
    int index = 0;
    while(!parsing_stack.empty())
    {
        string top = parsing_stack.top();
        if(!ParserTable::getInstance()->is_non_terminal(top))
        {
            if(top == tokens.at(index))
            {
                parsing_stack.pop();
                cout <<top << " matched with " << tokens.at(index)<<endl;
                index++;
            } else {
                parsing_stack.pop();
                cout << "Top of stack: " << top << "didnot match with " << tokens.at(index) << endl;
            }
        } else {

        }
    }

}

