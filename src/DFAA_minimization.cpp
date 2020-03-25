#include "DFAA_minimization.h"
/* Null, because instance will be initialized on demand. */

DFAMinimizer* DFAMinimizer::instance;
//constructor
DFAMinimizer::DFAMinimizer()
{
    this->dfa = DFA::get_instance();
    this->setFirstPartition(&this->Accepted,&this->NotAccepted,&this->previousPartition);
    this->partitioning(this->dfa, &this->previousPartition, &this->nextPartition);
    this->buildMinimizedDFA(this->dfa,&this->minimizedTransitionStateTable, &this->previousPartition);
    this->printMinimizedDFA();
}

DFAMinimizer* DFAMinimizer::getInstance()
{
    if (instance == nullptr)
    {
        instance = new DFAMinimizer();
    }
    return instance;
}


//It divides the partition to 2 sets accepted set and non accepted set
// and put them in the partitions sets
void DFAMinimizer:: setFirstPartition(set<Node*> *Acc, set<Node*> *Not_Acc, vector<set<Node*>> *partitions){ //p0
    vector<pair<Node*, map<RegularDef*,Node*>>> transitionStateTable = this->dfa->get_dfa();
    for (auto &ptr : transitionStateTable) {
        Node* temp = ptr.first;
        set<Node*>ptrNode; //////////////////////////////////////////////////////////////////
        if (temp->get_accepted_input() == normal_state) {
           Not_Acc->insert(temp);
        } else {
              Acc->insert(temp);
        }

    }
    cout<<"Accept "<<Acc->size()<<endl;
    cout<<"NotAccept "<<Not_Acc->size()<<endl;
    partitions->push_back(*Acc);
    partitions->push_back(*Not_Acc);
}


void DFAMinimizer::partitioning(DFA* dfa, vector<set<Node*>> *pre, vector<set<Node*>> *next ){

     this->partitioningHelper(dfa, pre,next);
     while (!(this->isEqualPartition(pre, next))) {
      //  cout<<"size of next partition "<< next->size() <<endl;
        pre->clear();
         for (auto &ptr : *next) {
             pre->push_back(ptr);
        }
        partitioningHelper(dfa,pre,next);
    }

}
void DFAMinimizer::partitioningHelper(DFA* dfa , vector<set<Node*>> *pre ,vector<set<Node*>> *next ){
    vector<set<Node*>> temp;
    for(auto ptr = pre->begin(); ptr != pre->end(); ++ptr) { //loop on each set on the partition
        this->distinguishStates(dfa,pre,&temp,*ptr);
    }
    next->clear();
    for (auto &ptr : temp) { //add new sets to next
        next->push_back(ptr);
    }

}

void DFAMinimizer::distinguishStates(DFA* dfa,vector<set<Node*>>* P,vector<set<Node*>> *n ,set<Node*> curr){
    Node* A  = *curr.begin();
    set<Node*>::iterator ptr ; // loop on every state //////////////////////////////
    set<Node*> set1;
    set<Node*> set2;
    for (auto B : curr) {
        if (!areEquivalentStates(dfa,P,A,B)) {
          // cout<<" Not Eq "<<endl;
            set2.insert(B);
        }else {
           // cout<<" Eq  "<<endl;
            set1.insert(B);
        }
    }
    if (set2.empty()) {
        n->push_back(set1);
    }else {
        n->push_back(set1);
        n->push_back(set2);
    }
}


// check if A and B are in the same group or not.
bool DFAMinimizer::areEquivalentStates(DFA* dfa , vector<set<Node*>> *P, Node* A, Node *B){
    if (A == B) {
        return true;
    }
    //say A in acc set and B in n-acc
    if (A->get_accepted_input() != B->get_accepted_input()) {
        return false;
    }
    vector<pair<Node*, map<RegularDef*,Node*>>> TT = dfa->get_dfa();
    //row of first state
    map<RegularDef*,Node*> a_map;
    //row of second state
    map<RegularDef*,Node*> b_map;
    for (auto &ptr : TT) {
        if (ptr.first == A) {
            //a_map= transition state of first state under all def
            a_map = ptr.second;
        }
        if (ptr.first == B) {
            //a_map= transition state of first state under all def
            b_map = ptr.second;
        }
    }
    map<string,RegularDef*> DT = GeneralMethods::getInstance()->getTable();
    int counter = 0;
    for (auto ptr2 = DT.begin(); ptr2 != DT.end() && counter < DT.size() - 1; ++ptr2) {
        RegularDef *j = ptr2->second; // take each def in each loop
        Node* stateA = a_map[j]; //transition state of 1st state under def j
        Node*stateB = b_map[j];//transition state of 2nd state under def j
        vector<set<Node*>>::iterator s; ////////////////////////////////////////
        for (auto temp : *P) {
            auto it1 = temp.find(stateA);
            auto it2 = temp.find(stateB);
            if ((it1 != temp.end() && it2 == temp.end())||(it1 == temp.end() && it2 != temp.end())) {
                return false;
            }
        }
        counter++; /////////////////////////////////////////////////
    }
    return  true;
}


void DFAMinimizer::printMinimizedDFA(){
    map<string,RegularDef*> DT = GeneralMethods::getInstance()->getTable();
    int counter = 0;
    cout << "Def  ";
    for (auto ptr2 = DT.begin(); ptr2 != DT.end() && counter < DT.size() - 1; ++ptr2) {
        cout << " " << ptr2->first;
        counter++;
    }
    vector<pair<Node*, map<RegularDef*, Node*>>>* min = this->getMinimizedDFA();
    cout<< "  Accepted" <<endl;
    for (auto &it : *min) {
        map<RegularDef*, Node*> map = it.second;
        cout<< it.first->get_id()<<":   ";
        for (auto &itDef : map) {
            cout<<" "<< itDef.second->get_id()<<" ";
        }
        cout<<"<"<< it.first->get_accepted_input()<<">"<<endl;
    }


}

//compare the next and previous with size
bool DFAMinimizer::isEqualPartition(vector<set<Node*>> *P,vector<set<Node*>> *N){

    return P->size() == N->size();
}

std::vector<std::pair<Node*, std::map<RegularDef*,Node*>>>*  DFAMinimizer::getMinimizedDFA(){
    return &this->minimizedTransitionStateTable;
}

//dfa , minimizedTransitionStateTable, previousPartition
void DFAMinimizer::buildMinimizedDFA(DFA* dfa,vector<pair<Node*, map<RegularDef*, Node*>>>*ret, vector<set<Node*>> *partition){
    vector<pair<Node*, map<RegularDef*,Node*>>> transitionStateTable = dfa->get_dfa();
    auto ptrTT = transitionStateTable.begin();
    map<set<Node*>, Node*> minDFA;
    Node* s = ptrTT->first; // START state A
    int counter = 0;
    //create node node for each partition
    //check if the start node in which gp
    //make the status of each gp with its  first node
    //make the new node is the representer of this gp
    for (auto &ptrP : *partition) { // loop for all groups
        Node *node = new Node(counter);
        this->findStartState(s, node, ptrP); //A ,node with id 0, gp i
        auto ptrS = *ptrP.begin();
        node->set_accepted_input(ptrS->get_accepted_input());
        minDFA[ptrP] = node;
        counter++;
    }
    for(auto itMap = minDFA.begin(); itMap != minDFA.end(); ++itMap){
            //find the first node in the first gp
            //check where is that node in the set of states in DFA
            //get the row of that state in DFA
        auto ptrS = *itMap->first.begin(); //{A}
        map<RegularDef*, Node*> values;
        for (auto &ptrTT : transitionStateTable) { //loop for each row
            Node* temp = ptrTT.first;
            if (temp == ptrS) {
                values = ptrTT.second;
                break;
            }
        }

        //replace the transition states under all the def with the min new states
        //to create the final minimized DFA table
        map<RegularDef*, Node*> tAfterMin;
        for (auto &value : values) { //loop for the a
            for (auto &itMap : minDFA) { // loop for the 0 --> {A,B,C}
                auto it1 = itMap.first.find(value.second);
                if (it1 != itMap.first.end()){ //find transition state in the set of states that represent 0
                    tAfterMin[value.first]= itMap.second;
                    break;
                }
            }
        }
        pair<Node*,map<RegularDef*, Node*>> pair1;
        pair1.first =  itMap->second;
        pair1.second = tAfterMin;
        ret->push_back(pair1);
    }

}

Node *DFAMinimizer::getStartState() const {
    return startState;
}

// Set the START state with the node with id =0 that contains the START node in DFA
void DFAMinimizer::setStartState(Node *startState) {
    DFAMinimizer::startState = startState;
}
//A ,node with id 0, gp1
void DFAMinimizer::findStartState(Node *old, Node *current, set<Node *> &set1) {
    auto it = set1.find(old);

    if (it != set1.end()) {
        this->setStartState(current);
        cout<< "Start state "<< this->getStartState()->get_id()<<endl;
    }

}
