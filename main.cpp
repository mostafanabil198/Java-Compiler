#include <iostream>

#include "ReadInput.h"
using namespace std;


vector<string> split(string line, char del) {
    std::istringstream line_stream(line);
    std::string word;
    vector<string> words;
    // get word by word separated by a del
    while(std::getline(line_stream, word, del)) {
        words.push_back(word);
    }
    return words;
}


int main()
{
    // params --> program, rules file, output file
    //ReadInput *r = new ReadInput("Test/program.txt","Test/rules.txt" ,"tokens.txt");
    string elem = "'if'";
    if(elem[0] == '\'' && elem[elem.size()-1] == '\''){
        elem = elem.substr(1, elem.size() - 2);
    }
    cout << elem;
    return 0;
}
