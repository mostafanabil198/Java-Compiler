#include "DefTable.h"
#include <bits/stdc++.h>
#include <iostream>

DefTable::DefTable()
{
    Graph* initial_graph = new Graph();
    Node* n = new Node(0);
    initial_graph->set_start(n);
    initial_graph->set_accept_state(n);
    initial_graph->get_start_state()->set_accepted_input("eps");
    this->insertInMap(EPS, new RegularDef(initial_graph));
}

static DefTable* DefTable::getInstance()
{
    if(instance == NULL) {
        instance = new DefTable();
    }
    return instance;
}
map<string, RegularDef*> DefTable::getTable()
{
        return this->definitions;
}
RegularDef* DefTable::getDefinitions(string id)
{
       if(this->definitions.count(id)) return definitions[id];
        return NULL;
}
void DefTable::insertInMap(string id, RegularDef* definition)
{
    this->definitions.insert(pair<string, RegularDef*>(id, definition));
}
