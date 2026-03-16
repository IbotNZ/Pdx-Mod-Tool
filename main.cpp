#include <iostream>
#include "lexer.hpp"
using namespace std;

int main() {
    cout << stringify_file("ck3_history_char_example.txt", true);
    return 0;
}