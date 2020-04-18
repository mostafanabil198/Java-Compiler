#include "parser/FollowGenerator.h"

FollowGenerator::FollowGenerator()
{

}


void FollowGenerator:: generate_follow()
{

    ParserTable::getInstance()->add_follow(ParserTable::getInstance()->get_first_non_terminal(),"$");
    get_follow(ParserTable::getInstance()->get_first_non_terminal());
    for(auto production : ParserTable::getInstance()->get_productions_table())
    {
        if(!ParserTable::getInstance()->has_follow(production.first))
        {
            get_follow(production.first);
        }

    }
}


void FollowGenerator:: get_follow(string non_terminal)
{

    vector<pair<string, pair<int, int>>> current = ParserTable::getInstance()->get_non_terminal_indexing(non_terminal);
    for( auto pos : current)
    {
        //cout << "non_terminal = " << non_terminal << endl;
        //cout <<"first index = "<< pos.second.first << " & second index = " << pos.second.second <<endl;
        finish = false;
        vector<vector<string>> cur_productions = ParserTable::getInstance()->get_production(pos.first);

        if(pos.second.second == cur_productions.at(pos.second.first).size()-1)
        {
            if(pos.first != non_terminal){
                if(!ParserTable::getInstance()->has_follow(pos.first))
                    get_follow(pos.first);

            for(auto elem_starts : ParserTable::getInstance()->get_follow(pos.first))
            {
               // cout << "non terminal = " << non_terminal << "--->" <<elem_starts << endl;
                ParserTable::getInstance()->add_follow(non_terminal,elem_starts);
            }
            }

        }
        else
        {

            if(pos.first != cur_productions.at(pos.second.first).at(pos.second.second+1))
            {

                //cout << "alhbd = " << cur_productions.at(pos.second.first).at(pos.second.second+1) << endl;
                evaluate_next_production(cur_productions,pos.second.first,pos.second.second+1,non_terminal);
                //cout << "finish = " << finish << endl;
                if(finish)
                {
                  //  cout << "pos.first = " << pos.first <<endl;
                  //  cout << "terminal = " << cur_productions.at(pos.second.first).at(pos.second.second+1) <<endl;

                    if(!ParserTable::getInstance()->has_follow(pos.first))
                    get_follow(pos.first);

                    for(auto elem_starts : ParserTable::getInstance()->get_follow(pos.first))
                    {
                   //     cout << "non terminal = " << non_terminal << "--->" << elem_starts<< endl;
                        ParserTable::getInstance()->add_follow(non_terminal,elem_starts);
                    }

                }
            }

        }


    }
}


void FollowGenerator:: evaluate_next_production(vector<vector<string>> current,int i, int j,string non_terminal)
{
    bool contain_eps = false;
    string production = current.at(i).at(j);
    if(!ParserTable::getInstance()->is_non_terminal(production))
    {
      //  cout << "non terminal = " << non_terminal << "--->" << production<< endl;
        ParserTable::getInstance()->add_follow(non_terminal,production);
    }
    else
    {
        vector<pair<string, vector<string>>> starts_of_nonterminal = ParserTable::getInstance()->get_start(production);
        for(auto start : starts_of_nonterminal)
        {
            if(!(start.first==EPSILON))
            {
            //    cout << "non terminal = " << non_terminal << "--->" << start.first<< endl;
                ParserTable::getInstance()->add_follow(non_terminal,start.first);

            }
            else
            {
                contain_eps = true;
            }
        }
        if(contain_eps)
        {
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
