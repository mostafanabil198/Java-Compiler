#include "ExpNfa.h"

ExpNfa::ExpNfa()
{
    general_methods = GeneralMethods::getInstance();
}

bool ExpNfa::construct_automata(string line)
{
    Tokenizing tokeniser;
    vector<string> tokens = tokeniser.get_tokens(line, ' ');
    if(tokens.size() < 1)
        return false;
    if (tokens[1] == "=")   // case definition
    {
        string def_name = tokens[0];
        tokens.erase(tokens.begin());
        tokens.erase(tokens.begin());
        definitions.insert(pair<string, vector<string>>(def_name, tokens));

        return true;
    }
    if(tokens[1] == ":") // case expression
    {
        string exp_name = tokens[0];
        tokens.erase(tokens.begin());
        tokens.erase(tokens.begin());
        Graph *exp_graph = recurse_build(tokens, &node_id);
        node_id = exp_graph->get_accept_state()->get_id()+1;
        exp_graph->get_accept_state()->set_accepted_input(exp_name);
        exp_graph->get_accept_state()->set_priority(priority++);
        this->exp_graphs.push_back(exp_graph);
    }
    else
    {
        if (tokens[0] == "{") // case keywords
        {
            tokens.erase(tokens.begin());
            tokens.erase(tokens.end());
            construct_keywords(tokens);
        }
        else if (line.at(0) == '[') // case punctuations
        {
            tokens.erase(tokens.begin());
            tokens.erase(tokens.end());
            construct_punct(tokens);
        }
        else
        {
            return false;
        }
    }
    return true;
}

Graph* ExpNfa::recurse_build(vector<string> tokens, int* node_id)
{
    bool brackets = false;
    if(tokens.empty())
    {
        return NULL;
    }

    string cur_token = tokens.front();
    tokens.erase(tokens.begin());
    Graph* exp_graph = new Graph();

    if(cur_token == "(")
    {
        exp_graph = recurse_brackets(&tokens, node_id);
        brackets = true;
    }
    string operation = check_operation(&tokens);

    if(!brackets)
    {
        exp_graph = create_graph(&tokens, cur_token, node_id, operation);
    }

    if(operation == "\\+" || operation == "*")
    {
        if(!(cur_token.length() == 1 || cur_token.find("-") != string::npos || cur_token.at(0) == '\\') && !definitions.count(cur_token))
        {
            operation = check_operation(&tokens);
        }
        else
        {
            exp_graph = general_methods->mergeGraphs(exp_graph, NULL, operation, node_id);
        }
        operation = check_operation(&tokens);
    }
    while (operation == "." && !tokens.empty())
    {
        exp_graph = get_cont(exp_graph, &tokens, node_id);
        //   testGraph(d_g);
        operation = check_operation(&tokens);
    }
    return general_methods->mergeGraphs(exp_graph, recurse_build(tokens, node_id), operation, node_id);

}

bool ExpNfa::construct_nfa()
{
    Graph* nfa_graph = new Graph();
    RegularDef* eps = general_methods->get_def_symbols(EPS);

    Node* new_start = new Node(node_id);
    nfa_graph->set_start(new_start);
    for (int i = 0; i < exp_graphs.size(); ++i)
    {
        //testGraph(exp_graphs[i]); //-
        nfa_graph->mergeGraph(exp_graphs[i]->get_tansitions(), exp_graphs[i]->get_all_nodes());
        nfa_graph->addEdge(new_start, exp_graphs[i]->get_start_state(), eps);
    }
    NFA* nfa = NFA::getInstance();
    nfa->setAutomata(nfa_graph);
    // testGraph(nfa); //-
    return true;
}

Graph *ExpNfa::recurse_brackets(vector<string> *tokens, int *node_id)
{
    string t = "";
    vector<string> inner_tokens;
    t = tokens->front();
    tokens->erase(tokens->begin());
    while(t != ")")
    {
        inner_tokens.push_back(t);
        t = tokens->front();
        tokens->erase(tokens->begin());
    }
    Graph* exp_graph = recurse_build(inner_tokens, node_id);
    string st = "(" + exp_graph->get_accept_state()->get_accepted_input() + ")";
    exp_graph->get_accept_state()->set_accepted_input(st);
    return exp_graph;
}


string ExpNfa::check_operation(vector<string> *tokens)
{
    string operation = ".";
    if(!tokens->empty())
    {
        if(tokens->front() == ".")
        {
            return operation;
        }

        if(tokens->front() != "\\-" && tokens->front() != "\\L" && tokens->front() != "=")
        {
            if (general_methods->is_def_symbol(tokens->front()) && tokens->front() != "(")
            {
                operation = tokens->front();
                tokens->erase(tokens->begin());
            }
        }
    }

    return operation;
}

Graph *ExpNfa::create_char_graph(string character, int *node_id)
{

    RegularDef *char_def = general_methods->getDefinitions(character);
    if(char_def == NULL)
    {
        Graph* def_graph = new Graph();
        Node *node = new Node(1);
        def_graph->set_start(node);
        def_graph->set_accept_state(node);
        def_graph->get_start_state()->set_accepted_input(character);
        char_def = new RegularDef(def_graph);
        general_methods->insertInMap(character, char_def);

    }
    Graph* char_graph = new Graph();
    Node *start_node = new Node((*node_id)++);
    Node *end_node = new Node((*node_id)++);
    end_node->set_accepted_input(character);

    char_graph->addEdge(start_node, end_node, char_def);
    char_graph->setStart(start_node);
    char_graph->set_accept_state(end_node);

    return char_graph;
}

// function that split string tokens to independent chars like variables names or keywords
Graph *ExpNfa::split_token(string token, int *node_id, string operation)
{
    vector<string> char_tokens;
    for (int i = 0; i < token.length(); i++)
    {
        char_tokens.push_back(string(1, token.at(i)));
    }
    // we add + or * as the last of it
    if(operation == "+" || operation == "*")
    {
        char_tokens.push_back(operation);
    }
    return recurse_build(char_tokens, node_id);
}

Graph* ExpNfa::create_graph_from_defintition(RegularDef* def, int* node_id, string token)
{
    Graph* def_graph = new Graph();
    Node *start_node = new Node((*node_id)++);
    Node *end_node = new Node((*node_id)++);
    end_node->set_accepted_input(token);
    def_graph->addEdge(start_node, end_node, def);
    def_graph->set_start(start_node);
    def_graph->set_accept_state(end_node);

    return def_graph;
}

Graph *ExpNfa::create_graph(vector<string> *tokens, string cur_token, int *node_id, string operation)
{
    if(definitions.count(cur_token))
    {
        Graph* g = recurse_build(definitions[cur_token], node_id);
        g->get_accept_state()->set_accepted_input(cur_token);
        //defVisited[token] = true;
        return g;
    }
    if (cur_token.length() == 1 ||cur_token.find("-") != string::npos|| cur_token.at(0) == '\\' )
    {
        if (!tokens->empty() || cur_token.find("-") != string::npos)
        {
            if ((tokens->front() == "\\-" && cur_token.length() == 1))
            {
                cur_token += tokens->front();
                tokens->erase(tokens->begin());
                cur_token += tokens->front();
                tokens->erase(tokens->begin());
            }
        }
    }
    RegularDef *d;
    if(cur_token == "\\L")
    {
        d = general_methods->getDefinitions(EPS);
    }
    else
    {
        d = general_methods->getDefinitions(cur_token);
    }

    if (d != NULL)
    {
        return create_graph_from_defintition(d,node_id, cur_token);
    }
    else if (cur_token.length() == 1 ||cur_token.find("-") != string::npos|| cur_token.at(0) == '\\' )
    {
        if(!tokens->empty() || cur_token.find("-") != string::npos)
        {

            if( cur_token.find("-") != string::npos && cur_token.length() == 4)
            {
                return expandedGraph(cur_token, node_id);
            }
        }
        return create_char_graph(cur_token, node_id);
    }
    else if (cur_token.length() > 1)
    {
        return splitToken(cur_token, node_id, operation);
    }
}


Graph* ExpNfa::get_cont(Graph *d_g, vector<string> *tokens, int *node_id)
{
    string token = tokens->front();
    tokens->erase(tokens->begin());
    bool brackets = false;
    Graph* g = new Graph();
    if(token == "(")
    {
        brackets = true;
        g = recurse_brackets(tokens, node_id);
    }
    string operation = check_operation(tokens);
    if(!brackets)
    {
        g = create_graph(tokens, token, node_id, operation);
    }
    if(operation == "*" || operation == "\\+")
    {
        g = general_methods->mergeGraphs(g, NULL, operation, node_id);
        operation = check_operation(tokens);
    }
    else
    {
        if(operation != ".")
            tokens->insert(tokens->begin(), operation);
    }
    return general_methods->mergeGraphs(d_g, g, ".", node_id);
}



void ExpNfa::constructKeyWords(vector<string> tokens)
{
    while (!tokens.empty())
    {
        Graph* d_g = splitToken(tokens.front(), &node_id, ".");
        d_g->get_accept_state()->set_accepted_input(tokens.front());
        d_g->get_accept_state()->set_priority(0);
        tokens.erase(tokens.begin());
        exp_graphs.push_back(d_g);
    }
    return;

}

void ExpNfa::constructPunct(vector<string> tokens)
{
    while (!tokens.empty())
    {
        Graph* d_g = create_char_graph(tokens.front(), &node_id);
        d_g->get_accept_state()->set_accepted_input(tokens.front());
        d_g->get_accept_state()->set_priority(priority);
        tokens.erase(tokens.begin());
        exp_graphs.push_back(d_g);

    }
    ++priority;
    return;
}


vector<string> ExpNfa::expand_def(string def)
{
    vector<string> range_tokens;
    std::stringstream tokens_stream(def);
    string token;
    while(std::getline(tokens_stream, token, '-'))
    {
        range_tokens.push_back(token);
    }

    char start = range_tokens[0].at(0);
    char end = range_tokens[1].at(0);
    vector<string> result;
    while (start <= end)
    {
        result.push_back(string(1,start++));
    }
    return result;
}

Graph *ExpNfa::expanded_graph(string token, int *node_id)
{
    vector<string> tokens =  expand_def(token);
    vector<Graph*> sub_graphs;
    Graph* result;
    while (!tokens.empty())
    {
        Graph* d_g = create_char_graph(tokens.front(), node_id);
        d_g->get_accept_state()->set_accepted_input(tokens.front());
        tokens.erase(tokens.begin());
        sub_graphs.push_back(d_g);
    }
    Node* new_start = new Node((*node_id)++);
    Node* new_end = new Node((*node_id)++);
    new_end->set_accepted_input(token);
    result = new Graph();
    result->setStart(new_start);
    result->set_accept_state(new_end);
    for (int i = 0; i <sub_graphs.size() ; ++i)
    {
        cout<<"Graph #" << i << endl << "-----------------------" << endl;
        result->mergeGraph(sub_graphs[i]->get_tansitions(), sub_graphs[j]->get_all_states());
        result->addEdge(new_start, sub_graphs[j]->get_start_state(), general_methods->getDefinitions(EPS));
        sub_graphs[j]->get_accept_state()->set_accepted_input(normal_state);
        result->addEdge(sub_graphs[j]->get_accept_state(), new_end, general_methods->getDefinitions(EPS));
    }
    return result;
}
