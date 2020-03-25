#include "Tokenizing.h"

Tokenizing::Tokenizing()
{
    def_symbols = (*GeneralMethods::getInstance()).get_def_symbols();
}

// parse a line and return all tokens found
vector<string> Tokenizing::get_tokens(string line, char del) {
    std::istringstream line_stream(line);
    std::string word;
    // get word by word separated by a del *space*
    while(std::getline(line_stream, word, del)) {
        if(word.find("-") != string::npos && word.length() == 1) {
            word = "\\-";
        } else if(word.find("+") != string::npos && word.length() == 1) {
            word = "\\+";
        }
        this->parse_string(word);
    }
    return tokens;
}

// parse the word char by char and get tokens from it
void Tokenizing::parse_string(string word) {
    string cur_char;
    string prev_string = "";
    for (int i = 0; i < word.length() ; ++i) {
        char c = word.at(i);
        // handle special chars + and - to set the cur char as \\- or \\+
        if(c == '+' || c == '-') {
            if(prev_string == "\\"){
                prev_string.clear();
            }
            cur_char = "\\";
            cur_char += c;
        } else {
        // the general ca where we add the char as it is in cur_char
            cur_char = string(1, c);
        }
        if(prev_string == "\\"){
            if(cur_char == "=") {
                tokens.push_back(cur_char);
            } else {
                tokens.push_back(prev_string + cur_char);
            }
            prev_string.clear();
        } else if (std::find(def_symbols.begin(), def_symbols.end(), cur_char) != def_symbols.end()) {
        // if symbol then i will need the prev to it and the symbol itself as tokens
            if(prev_string.length() > 0) {
                tokens.push_back(prev_string);
            }
            tokens.push_back(cur_char);
            prev_string.clear();
        // if current \\ then the prev_string is a token and the thing after \\ will be another one for sure
        // and i will set the prev to the '\\'
        } else if(cur_char == "\\"){
            if(prev_string.length() > 0)
                tokens.push_back(prev_string);
            prev_string = cur_char;
        } else {
        // if nth worked then its a string that will continue with
            prev_string += cur_char;
        }
    }
    if(prev_string.length() > 0) {
        tokens.push_back(prev_string);
    }
}
