#include <iostream>
#include "lexer.hpp"
using namespace std;

int main() {
    //int pos = 0;
    //char current_char, next_char;
    //string txt = stringify_file("ck3_history_char_example.txt");
    //current_char = txt[pos++];
    //next_char = txt[pos];
    //cout << current_char << next_char;
    vector<token> tokenized_doc = tokenize("ck3_history_char_example.txt");
    //cout << tokenized_doc.size();
    for (int i = 0; i < tokenized_doc.size(); i++) {
        cout << "Token Type: " << tokenized_doc[i].type << " " << "Value: " << tokenized_doc[i].value << "\n";
    }
    return 0;
}