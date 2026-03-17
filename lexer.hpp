#pragma once

#include <string>
#include <vector>
using namespace std;

// Paradox Script Grammar

enum token_type {
    END_OF_LINE,

    //STRING,

    IDENTIFIER,
    
    KEYWORD,

    PUNCTUATION,

    OPERATOR,

    NUM,

    COMMENT,

    WHITESPACE
};

struct token {
    token_type type;
    string value;
};

string stringify_file(string txt_file, bool add_line_breaks = false);

// Lexer function returns text as list of tokens
vector<token> tokenize(string txt);