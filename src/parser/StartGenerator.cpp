#include "parser/StartGenerator.h"

StartGenerator::StartGenerator()
{
    //loop on
}




void StartGenerator::generate_start()
{

//check terminal--> insert in start table this terminal(elem) + the production it came from (rule)
//check non terminal --> case done--> add its starts in the current start + the current rule for each start
    //case notdoe--> recurse call get_starts for this non terminal
//after finishing check that if this non terminal goes to epsilon -->case true continue the loop  , Else --> break the loop
    for(auto production : ParserTable::getInstance()->get_productions_table())
    {
        if(!ParserTable::getInstance()->has_start(production.first))
        {
            get_starts(production.first);
        }
    }
}
void StartGenerator::get_starts(string current_non_terminal)
{
    //loop on productions
    for( auto rule : ParserTable::getInstance()->get_production(current_non_terminal))
    {
        //loop on elemnts of each production
        for(auto elem : rule)
        {
            bool has_epsilon=false;
            if(!ParserTable::getInstance()->is_non_terminal(elem))
            {
                ParserTable::getInstance()->add_start(current_non_terminal,make_pair(elem,rule));
                break;
            }
            else
            {
                //case undone
                if(!ParserTable::getInstance()->has_start(elem))
                {
                    get_starts(elem);
                }

                for(auto elem_starts : ParserTable::getInstance()->get_start(elem))
                {
                    if(elem_starts.first==EPSILON) {
                        has_epsilon = true;
                        // To get the non-terminals taht has Epsilon in first
                        ParserTable::getInstance()->add_has_eps(current_non_terminal);
                    }
                    ParserTable::getInstance()->add_start(current_non_terminal,make_pair(elem_starts.first,rule));
                }

                //check if this non terminal goes to epsilon
                if(!has_epsilon)
                    break;
            }
        }

    }
}

