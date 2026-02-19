#include <string>
using namespace std;

struct token {
    int type;
    string value;
};

// Paradox Script Grammar

enum token_type {
    END_OF_LINE,
    STRING,
    IDENTIFIER,

    OPEN_PAREN,
    CLOSE_PAREN,

    EQUALS,
};