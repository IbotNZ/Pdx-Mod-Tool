#include <iostream>
#include "lexer.hpp"
using namespace std;

int main() {
    int pos = 0;
    char current_char, next_char;
    string txt = stringify_file("ck3_history_char_example.txt");
    current_char = txt[pos++];
    next_char = txt[pos];
    cout << current_char << next_char;
    return 0;
}