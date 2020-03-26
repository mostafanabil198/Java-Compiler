#include "ReadInput.h"
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>

ReadInput::ReadInput(string filename)
{
    this->file=filename;
    this->minimized_dfa = DFA_minimization::get_instance();
    this->transition_table = minimized_dfa->get_min_dfa();
    cout << endl << "------------------ReadInput----------------- " << endl;
    read_input_from_file();
}

vector <string> ReadInput::get_line_tokens(string line) {
    vector<string> tokens;
    stringstream ssin(line);
    string token;
    while(ssin >> token) {
        cout << endl << "------ Token:  " << token << endl;
        tokens.push_back(token);
    }
    return tokens;
}

void ReadInput::Output() {
    ofstream outfile;
    outfile.open("tokens.txt");
    for (int i = 0; i < this->tokens.size(); i++) {
        if(tokens[i].at(0) == '\\' && tokens[i].size() > 1){
            tokens[i] = tokens[i].at(1);
            }
        outfile << tokens[i] << endl;
    }
    outfile.close();
}

//get the next state under the current input
Node* ReadInput::get_next_state(Node* current_state, char inputChar) {
    string input = string(1, inputChar);
    map <RegularDef*, Node*> current_state_transitions;
    vector<pair<Node*, map<RegularDef*, Node*>>>::iterator it;
    for (it = (*this->transition_table).begin() ; it != (*this->transition_table).end(); ++it) {
        if((*it).first == current_state) {//get current state from the transition table
            current_state_transitions = (*it).second; //return all possible transitions for current state
        }
    }
    for (map<RegularDef*, Node*>::iterator it = current_state_transitions.begin(); it != current_state_transitions.end(); ++it) {
        if ((*it).first->accepts(input)) { //if there exist an edge whose definition accept the input
            return (*it).second; //return the destination node(next state)
        }
    }
    return NULL;
}

vector<string> ReadInput::get_tokens() {
    return this->tokens;
}

void ReadInput::read_input_from_file() {
    ifstream infile(this->file);
    string line;
    vector <string> line_tokens;
    if (infile.is_open()) {
        while (getline(infile, line)) {
            if (line.length() == 0 || line == " ")
                continue;
            line_tokens = get_line_tokens(line);

            for (int i = 0; i < line_tokens.size(); i++) {//loop on line tokens
                Node *current_state = minimized_dfa->get_start_state();
                Node *last_accepted_state = NULL;
                int last_accepted_index = -1;
                int start_index = 0;
                for (int j = 0; j < line_tokens[i].length(); j++) {//loop on every character of the token

                    current_state = get_next_state(current_state, line_tokens[i].at(j)); //get next state for the input character
                    if(line_tokens[i] == " ") {
                        continue;
                    }
                    if (current_state != NULL && current_state->get_accepted_input() != normal_state){ //if the current state accepts an expression
                        last_accepted_state = current_state; //set last accepted state to current one
                        last_accepted_index = j;
                    }
                    //the current state after the input is null (no destination found machine terminate)
                    //or we reached end of input (last state) but it doesnt accept an expression (normal state)
                    if ( (current_state == NULL) || (j == line_tokens[i].length() - 1 && current_state->get_accepted_input() == normal_state)) {
                    //case there were accepted states before get the last one (most recent)
                        if (last_accepted_index > -1 && last_accepted_state != nullptr){

                            tokens.push_back(last_accepted_state->get_accepted_input());
                            cout<< "----accept and didnt reach end---" << last_accepted_state->get_accepted_input()<<endl;
                            last_accepted_state = NULL;//reset accepted state
                            start_index = last_accepted_index;//update new start to be at the last accepted index
                            j = last_accepted_index; //after this loop j will be incremented start after last acceptedS
                            last_accepted_index = -1; //reset accepted index
                        }
                        else {
                        //if there werent any accepted states ,therefore wrong input
                        //apply panic mode recovery remove a letter then statrt again
                            tokens.push_back("Not Matched");
                            cout<<"Not Matched"<<endl;

                            if (start_index != 0) {
                                j = start_index + 1;
                                last_accepted_index = j;
                            }
                        }
                        //reset the current state to start from the beginng for new input
                        current_state = minimized_dfa->get_start_state();
                    }
                    //case reaching end of input and the current state accepts an expression
                    else if (j == line_tokens[i].length() - 1 && current_state->get_accepted_input() != normal_state){
                        tokens.push_back(current_state->get_accepted_input());
                        cout<< "----accept and reach end---" << last_accepted_state->get_accepted_input()<<endl;
                    }
                }
            }
           // tokens.push_back("$");
        }
    }
    Output();
}
