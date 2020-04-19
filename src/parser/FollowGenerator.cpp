#include "parser/FollowGenerator.h"

FollowGenerator::FollowGenerator()
{

}


void FollowGenerator:: generate_follow()
{
    // First, add $ in the follow list of the start non terminal
    ParserTable::getInstance()->add_follow(ParserTable::getInstance()->get_first_non_terminal(),"$");
    get_follow(ParserTable::getInstance()->get_first_non_terminal());
    // loop for all the nonterminal to get the follow of them
    for(auto production : ParserTable::getInstance()->get_productions_table())
    {
       // check if the follow of this non terminal still not calculated
        if(!ParserTable::getInstance()->has_follow(production.first))
        {
            get_follow(production.first);
        }

    }
}


void FollowGenerator:: get_follow(string non_terminal)
{

    vector<pair<string, pair<int, int>>> current = ParserTable::getInstance()->get_non_terminal_indexing(non_terminal);

    //loop for each position this non terminal existed in and calculate the follow on that position
    for( auto pos : current)
    {
        finish = false;
        //create object of the all productions of that nonterminal to find the dssired position
        vector<vector<string>> cur_productions = ParserTable::getInstance()->get_production(pos.first);

        //if that nonterminal is the last symbol in that production get the follow of the left non termenal
        //Example : X --> aBb  ,  where x :left nonterminal
        if(pos.second.second == cur_productions.at(pos.second.first).size()-1)
        {
            if(pos.first != non_terminal){
                if(!ParserTable::getInstance()->has_follow(pos.first))
                    get_follow(pos.first);

            for(auto elem_starts : ParserTable::getInstance()->get_follow(pos.first))
            {
                ParserTable::getInstance()->add_follow(non_terminal,elem_starts);
            }
            }

        }
        else
        {

//            if(pos.first != cur_productions.at(pos.second.first).at(pos.second.second+1))
          //  {

         // if that nonterminal is not the last symbol .so, check the next symbol is it terminal or non terminal
                evaluate_next_production(cur_productions,pos.second.first,pos.second.second+1,non_terminal);
                // if the first of the next nonterminal has epsilon , get the follow of the left non terminal
                if(finish)
                {
                    if(!ParserTable::getInstance()->has_follow(pos.first))
                    get_follow(pos.first);

                    for(auto elem_starts : ParserTable::getInstance()->get_follow(pos.first))
                    {
                        ParserTable::getInstance()->add_follow(non_terminal,elem_starts);
                    }

                }
           // }

        }


    }
}

//check the next symbol is terminal or non terminal
//if terminal put it in the follow list
//if non terminal get the start of it and check it has epsilon or not
void FollowGenerator:: evaluate_next_production(vector<vector<string>> current,int i, int j,string non_terminal)
{
    bool contain_eps = false;
    string production = current.at(i).at(j);

    // if it is terminal , add it in the follow list
    if(!ParserTable::getInstance()->is_non_terminal(production))
    {
        ParserTable::getInstance()->add_follow(non_terminal,production);
    }
    else
    {
    //if it is nonterminal get the start of it and add them in the follow list
        vector<pair<string, vector<string>>> starts_of_nonterminal = ParserTable::getInstance()->get_start(production);
        for(auto start : starts_of_nonterminal)
        {
            if(!(start.first==EPSILON))
            {
                ParserTable::getInstance()->add_follow(non_terminal,start.first);

            }
            else
            {
                contain_eps = true;
            }
        }
        //if it has epsilon
        if(contain_eps)
        {
            //if it is not the last symbol in the production , get in a recursion and check the next symbol
            if(j < current.at(i).size()-1)
            {
                evaluate_next_production(current,i,j+1,non_terminal);
            }
            else
            {
                finish = true;
            }
        }
    }
}
