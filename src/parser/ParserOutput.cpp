#include "ParserOutput.h"

ParserOutput::ParserOutput()
{

}


void ParserOutput:: derive(vector<string> tokens)
{

//push $ in the stack them the start non terminal to begin
    cout << "************OUTPUT********************"<< endl;
    parsing_stack.push("$");
    parsing_stack.push(ParserTable::getInstance()->get_first_non_terminal());
    int index = 0;

    //loop till the stack is empty
    while(!parsing_stack.empty())
    {
        string top = parsing_stack.top();

        //if the top of the stack is terminal
        if(!ParserTable::getInstance()->is_non_terminal(top))
        {
         //if it matches the first of the input
            if(top == tokens.at(index))
            {
                cout <<top << " matched with " << tokens.at(index)<<endl;

                parsing_stack.pop();
                index++;
            }
            else
            {
           //if it doesnot match the first of the input, remove from the stack
                cout << "ERROR : Top of stack: " << top << " didnot match with " << tokens.at(index) << endl;

                parsing_stack.pop();
            }
        }
        else
        {
        //if the top of the stack is non-terminal
            //if it is epsilon ,remove from stack
            if(ParserTable::getInstance()->is_entry_epsilon(top,tokens.at(index)))
            {
                cout << top << "-->" << "EPSILON" << endl;
                parsing_stack.pop();

            }
            //if it is sync, remove from stack
            else if(ParserTable::getInstance()->is_entry_sync(top,tokens.at(index)))
            {
                cout << "ERROR : sync " << endl;
                parsing_stack.pop();

            }
            //if it is empty remove from input
            else if(ParserTable::getInstance()->is_entry_empty(top,tokens.at(index)))
            {
                cout << "ERROR : illegal "<< top << " discard " << tokens.at(index) << endl;
                index ++ ;

            }
            else
            {
            //if it has production get it and push it in the stack inversly
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

 //if the stack has $ and input has $ then it is accepted , if it still has input so it is not accepted
    if(index == tokens.size())
    {
        cout << "Accepted and Done" << endl;
    }
    else
    {
        cout << "ERROR: NotAccepted" << endl;
    }

}

