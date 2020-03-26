#include "RegularDef.h"

RegularDef::RegularDef(Graph *regular_def)
{
    this->regular_def = regular_def;
}

void RegularDef::set_regular_def(Graph *regular_def) {
    this->regular_def = regular_def;
}

Graph* RegularDef::get_regular_def() {
    return regular_def;
}

bool RegularDef::accepts(string input) {
    if(regular_def->get_all_nodes().size() == 1){
       string accepted_input = regular_def->get_accept_state()->get_accepted_input();
       if(accepted_input.at(0) == '\\') {
           accepted_input = string(1,accepted_input.at(1));
       }
       if(accepted_input == EPS){
            return true;
       } else if(accepted_input == input) {
           return true;
       }
        return false;
    } else {
        return false;
    }
}

Node* RegularDef::dfs(Node* start, int states_number, string input) {

    bool *visited = new bool[states_number];
    for(int i = 0; i < states_number; i++){
        visited[i] = false;
    }

    stack<Node*> stack;

    visited[start->get_id()] = true;
    stack.push(start);

    while(!stack.empty())
    {
        start = stack.top();
        stack.pop();

        vector<Edge*> edges = start->get_leaving_edges();
        for (vector<Edge*>::iterator it = edges.begin() ; it != edges.end(); ++it) {
            if ((*it)->get_weight()->accepts(input))
                return (*it)->get_dest();
            if (!visited[(*it)->get_dest()->get_id()]) {
                visited[(*it)->get_dest()->get_id()] = true;
                stack.push((*it)->get_dest());
            }
        }
    }

    return NULL;
}


