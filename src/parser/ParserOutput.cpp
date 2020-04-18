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
                cout <<top << " matched with " << tokens.at(index)<<endl;

                parsing_stack.pop();
                index++;
            }
            else
            {

                cout << "ERROR : Top of stack: " << top << "didnot match with " << tokens.at(index) << endl;

                parsing_stack.pop();
            }
        }
        else
        {
            if(ParserTable::getInstance()->is_entry_epsilon(top,tokens.at(index)))
            {
                cout << top << "-->" << "EPSILON" << endl;
                parsing_stack.pop();

            }
            else if(ParserTable::getInstance()->is_entry_sync(top,tokens.at(index)))
            {
                cout << "ERROR : sync " << endl;
                parsing_stack.pop();

            }
            else if(ParserTable::getInstance()->is_entry_empty(top,tokens.at(index)))
            {
                cout << "ERROR : illegal "<< top << "discard " << tokens.at(index) << endl;
                index ++ ;

            }
            else
            {
                cout << top << "-->";
                vector<string> temp;
                for(int t=ParserTable::getInstance()->get_parsing_table_entry(top,tokens.at(index)).size()-1;t>=0; --t)
                {
                    cout << ParserTable::getInstance()->get_parsing_table_entry(top,tokens.at(index)).at(t) << " ";
                    temp.push_back(ParserTable::getInstance()->get_parsing_table_entry(top,tokens.at(index)).at(t));
                }
                cout << endl;
                parsing_stack.pop();
                for(int t=0; t < temp.size(); ++t)
                {
                    parsing_stack.push(temp.at(t));
                }

            }
        }
    }

    if(index == tokens.size())
    {
        cout << "Accepted and Done" << endl;
    }
    else
    {
        cout << "ERROR: NotAccepted" << endl;
    }

}

