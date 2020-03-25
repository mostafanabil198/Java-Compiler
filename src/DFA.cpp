#include <list>
#include <iostream>
#include <algorithm>
#include "DFA.h"
#include "NFA.h"
#include "GeneralMethods.h"


DFA* DFA::instance;

DFA* DFA::get_instance() {
    if (instance == NULL) {
        instance = new DFA();
    }
    return instance;
}
//search in NFA table to get the transisions of a state under
// defination and return set of destination nodes.
set<Node*> DFA::get_transition_states (Node* state, RegularDef* def) {
    if(nfa_table.find(state) != nfa_table.end()) {
        if(nfa_table.at(state).find(def) != nfa_table.at(state).end()) {
            return nfa_table.at(state).at(def);
        }
    }
    return set<Node*>();
}


//take the given state and search for destination states under
// defination EPS and push all of them in a set of nodes to
//return it.
set<Node*> DFA::get_epsilon_closure(Node *start) {
    RegularDef* Eps = GeneralMethods::getInstance()->getDefinitions(EPS);
    set<Node*> setReturned;
    Node* state;

    list<Node*> queue;
    queue.push_back(start);
    while(!queue.empty()) {
        state = queue.front();
        queue.pop_front();
        //check if it doesn't exist in set
        if(setReturned.find(state) == setReturned.end()) {
            setReturned.insert(state);
            set<Node*> set = get_transition_states(state, Eps);
            //add edges in queue
            for (std::set<Node*>::iterator it=set.begin(); it!=set.end(); ++it) {
                queue.push_back(*it);
            }
        }
    }
    return setReturned;
}


// return the node with the highest priority of a
//given set of nodes if the node not dummy node
Node* DFA::get_highest_priority(set<Node*> set) {
    int priority = -1;
    Node* returnedState = new Node(-1);
    for (std::set<Node*>::iterator it = set.begin(); it != set.end(); ++it) {
        if((*it)->get_accepted_input() != normal_state) {
            if (priority == -1) {
                priority = (*it)->get_priority();
                returnedState = (*it);
            } else if((*it)->get_priority() < priority) {
                priority = (*it)->get_priority();
                returnedState = (*it);
            }
        }
    }
    return returnedState;
}

void DFA::testDFA() {
    for (vector<pair <Node*,  map<RegularDef*,Node*>>>::iterator it = transition_table.begin() ; it != transition_table.end(); ++it) {
        map<RegularDef*, Node*> map = (*it).second;
        cout<<(*it).first->get_id()<<(*it).first->get_accepted_input()<<" ";
        for (std::map<RegularDef*, Node*>::iterator itDef = map.begin(); itDef != map.end(); ++itDef) {
            cout<<(*itDef).first->get_regular_def()->get_start_state()->get_accepted_input()<<"  ";
            cout<<" "<<(*itDef).second->get_id()<< " ";
        }
        cout<< endl;
    }
}

//search in DFA table if a given node ia already exist and returnd
//its id
//if it doesnot exist return 0.
int DFA::table_with_same_state(set<Node *> state) {
    for(vector<set<Node*>>::iterator it = stateMappingTable.begin(); it != stateMappingTable.end(); ++it ) {
        if((*it) == state) {
            return it - stateMappingTable.begin();
        }
    }
    return 0;
}

DFA::DFA() {
    NFA* nfa = NFA::get_instance();
    nfa->read_input();

    //get the final NFA graph
    Graph* graph = nfa->get_automata();
    Node* start = graph->get_start_state();

    //get the NFA table from the graph.
    BFS(start);

    Node* dummyState = NULL;
    int id = 0;

    //create a new state to be added iin DFA table
    //with specific id.
    Node* state = new Node(id);
    state->set_accepted_input(start->get_accepted_input());
    // get EPS closuer for the starting node
    stateMappingTable.push_back(get_epsilon_closure(start));
    //push the first state in the DFA table
    transition_table.push_back(make_pair(state,map<RegularDef*,Node*>()));
    id++;

    RegularDef* Eps = GeneralMethods::getInstance()->getDefinitions(EPS);
    for (vector<pair<Node*, map<RegularDef*,Node*>>>::size_type itVector = 0; itVector != transition_table.size(); ++itVector) {
        //get for each definition all states from epsilon transition
        set<Node *> setOfState = stateMappingTable[transition_table[itVector].first->get_id()];
        //get definitions table iterator
        map<string, RegularDef*> definitions = GeneralMethods::getInstance()->getTable();


        //iterate for all the definations to complete the DFA table.
        for (map<string, RegularDef*>::iterator itDef = definitions.begin(); itDef != definitions.end(); ++itDef) {

            if(itDef->second == Eps) {
                continue;
            }

            //find the destination set for the current state under this definition
            set<Node *> returnedSetOfEachDefinition;
            for (set<Node *>::iterator itSet = setOfState.begin(); itSet != setOfState.end(); ++itSet) {
                set<Node *> returnedSet = get_transition_states(*itSet, itDef->second);
                returnedSetOfEachDefinition.insert(returnedSet.begin(), returnedSet.end());
            }


            //find the destination of the previous set under EPS defination.
            set<Node *> eps;
            for (set<Node *>::iterator itSet = returnedSetOfEachDefinition.begin(); itSet != returnedSetOfEachDefinition.end(); ++itSet) {
                set<Node *> returnedSet = get_epsilon_closure(*itSet);
                eps.insert(returnedSet.begin(), returnedSet.end());
            }
            returnedSetOfEachDefinition.insert(eps.begin(), eps.end());

            //if there are no destination nodes
            if(returnedSetOfEachDefinition.empty()) {

                //first create the row of dummy state with certain id row with dummy nodes under each def
                // states |  DEF1  |  DEF2
                //  dummy |    --- | ---
                if (dummyState == NULL) {
                    dummyState = new Node(id);
                    dummyState->set_accepted_input(normal_state);
                    map<string, RegularDef*> definitions = GeneralMethods::getInstance()->getTable();
                    transition_table.push_back(make_pair(dummyState, map<RegularDef *, Node *>()));
                    stateMappingTable.push_back(set<Node*>());
                    for (map<string, RegularDef*>::iterator it = definitions.begin(); it != definitions.end(); ++it) {
                        if(it->second == Eps) {
                            continue;
                        }
                        transition_table[id].second.insert(make_pair((*it).second, dummyState));
                    }
                    id++;
                }
                //set the destination that has empty set withh this dummy node
                transition_table[itVector].second.insert(make_pair(itDef->second, dummyState));
                continue;
            }

            //check if the destination set is already exist in DFA table or not.
            //if exitst so set the destination under this defination with this node
            //if not exist so create a new node set its priority and status
            if (int idOfState = table_with_same_state(returnedSetOfEachDefinition)) {
                Node *stateInDefinition = transition_table[idOfState].first;
                transition_table[itVector].second.insert(make_pair(itDef->second, stateInDefinition));
            } else {
                Node* state = new Node(id);
                id++;
                Node* highestPriorityState = get_highest_priority(returnedSetOfEachDefinition);
                state->set_accepted_input(highestPriorityState->get_accepted_input());
                state->set_priority(highestPriorityState->get_priority());
                transition_table[itVector].second.insert(make_pair(itDef->second, state));
                transition_table.push_back(make_pair(state, map<RegularDef *, Node *>()));
                stateMappingTable.push_back(returnedSetOfEachDefinition);
            }
        }
    }
    //TODO set memory free for all data structures unused
    testDFA();
}

//get the end states for the certain state and certain def
set<Node*> DFA::loop_definition(RegularDef* def, Node* state) {
    set<Node*> set;
    vector<Edge*> edges = state->get_leaving_edges();
    for (vector<Edge*>::iterator it = edges.begin() ; it != edges.end(); ++it) {
        if((*it)->get_weight() == def) {
            set.insert((*it)->get_dest());
        }
    }
    return set;
}

void DFA::create_new_row(Node* state) {
    map<RegularDef*, set<Node*>> pairMap;
    map<string, RegularDef*> definitions = GeneralMethods::getInstance()->getTable();
    //loop for all the definations to create the table with the states and the end nodes for each state
    for (map<string, RegularDef*>::iterator it = definitions.begin(); it != definitions.end(); ++it) {
        set<Node*> set = loop_definition(it->second, state);
        if(!set.empty()) {
                //pairMap contains the definations and the end states of the same defination
            pairMap.insert(make_pair((it->second), set));
        }
    }
    //create the row of the current state for all the definations
    this->nfa_table.insert(make_pair(state, pairMap));
}

//Applay BFS on the NFA graph to create the row for each state
void DFA::BFS(Node* start) {
    map <int, bool> visited;
    list<Node*> queue;

    visited.insert(make_pair(start->get_id(),true));
    queue.push_back(start);

    while(!queue.empty()) {
        start = queue.front();
        queue.pop_front();
        visited.insert(make_pair(start->get_id(),true));
        create_new_row(start);
        vector<Edge*> edges = start->get_leaving_edges();
        for (vector<Edge*>::iterator it = edges.begin() ; it != edges.end(); ++it) {
            if (visited.find((*it)->get_dest()->get_id()) == visited.end()) {
                visited.insert(make_pair((*it)->get_dest()->get_id(), true));
                queue.push_back((*it)->get_dest());
                create_new_row((*it)->get_dest());
            }
        }
    }
}

vector< pair <Node*,  map<RegularDef*, Node*>>> DFA::get_dfa() {
    return this->transition_table;
}
