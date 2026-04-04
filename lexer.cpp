#include "lexer.hpp"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

// Constants
const char EMPTYSPACE = ' ';
const char COM = '#';
const char NEWLINE = '\n';

// Classes
class StringReader {
    public:
        string txt;
        int pos = 0;
        char current_char;
        char next_char;

        StringReader (string txt_string) {
            txt = txt_string;
            read_next();
        }

        void read_next() {
            current_char = txt[pos++];
            next_char = txt[pos];
            //cout << current_char;
        }

        bool eof() {
            return (pos) == txt.length();
        }
};


vector<string> keywords {
    "name",
    "dynasty_house",
    "martial",
    "diplomacy",
    "intrigue",
    "stewardship",
    "religion",
    "faith",
    "culture",
    "trait",
    "father",
    "mother",
    "birth",
    "death",
    "effect"
};

vector<char> identifier_chars {
    '.',
    '_',
    '"'
};

vector<char> punctuation {
    '{',
    '}',
    '(',
    ')',
    '.'
};

vector<char> operators {
    '=',
    '+',
    '/'
};


int set_token_val(token* target, token_type _type, string _value) {
    target->type = _type;
    target->value = _value;
    return 0;
}

bool is_valid_identifier_char(char _char) {
    if (isalnum(_char) or count(identifier_chars.begin(), identifier_chars.end(), _char) >> 0) {
        return true;
    }
    else {
        return false;
    }
}

string stringify_file(string txt_file, bool add_line_breaks) {
    string myText;
    string newText;
    ifstream MyReadFile(txt_file);

    while (getline (MyReadFile, myText)) {
        newText += myText;
        if (add_line_breaks) {
            newText += NEWLINE;
        }
    }

    MyReadFile.close();

    return newText;
}

bool char_is_same(char _char, char _char1) {
    return  _char == _char1;
}

vector<token> tokenize(string txt_file) {
    string txt = stringify_file(txt_file, true);
    bool emergencyBreak = false;
    // Denotes what type the lexer assumes the current char is from
    token_type state = WHITESPACE;
    vector<token> token_list;
    token new_token;

    StringReader scriptReader(txt);
    string word = "";

    while (not scriptReader.eof() and not emergencyBreak) {
        switch (state) {
            case WHITESPACE:
                if (scriptReader.current_char == EMPTYSPACE or scriptReader.current_char == NEWLINE or scriptReader.current_char == '\t') {
                    scriptReader.read_next();
                }
                else {
                    word = "";
                    if (scriptReader.current_char == COM) {
                        state = COMMENT;
                    }
                    else if (count(punctuation.begin(), punctuation.end(), scriptReader.current_char) != 0) {
                        state = PUNCTUATION;
                    }
                    else if (count(operators.begin(), operators.end(), scriptReader.current_char) != 0) {
                        state = OPERATOR;
                    }
                    else if (is_valid_identifier_char(scriptReader.current_char)) {
                        state = IDENTIFIER;
                    }
                    else {
                        cout << "BREAK" << "\n";
                        cout << "Current Char: \"" << scriptReader.current_char << '"' << '\n';
                        cout << '"' << scriptReader.next_char << '"';
                        emergencyBreak = true;
                    }
                }
                
                //else if (isdigit(scriptReader.current_char)) {
                //    state = NUM;
                //}
                
                break;

            case COMMENT:
                if (scriptReader.current_char == NEWLINE) {
                    state = WHITESPACE;
                }
                else {
                    scriptReader.read_next();
                }
                break;

            case PUNCTUATION:
                // All punctuation is one char currently so current logic is basic
                word += scriptReader.current_char;
                set_token_val(&new_token, PUNCTUATION, word);
                token_list.push_back(new_token);
                scriptReader.read_next();
                state = WHITESPACE;
                break;
            
            case OPERATOR:
                // All operators are one char currently so current logic is basic
                word += scriptReader.current_char;
                set_token_val(&new_token, OPERATOR, word);
                token_list.push_back(new_token);
                scriptReader.read_next();
                state = WHITESPACE;
                break;

            case IDENTIFIER:
                if (is_valid_identifier_char(scriptReader.current_char)) {
                    word += scriptReader.current_char;
                    //cout << "Word: " << word << '\n';
                    scriptReader.read_next();
                }
                else {
                    if (count(keywords.begin(), keywords.end(), word) > 0) {
                        set_token_val(&new_token, KEYWORD, word);
                    }
                    else {
                        set_token_val(&new_token, IDENTIFIER, word);
                    }
                    token_list.push_back(new_token);
                    state = WHITESPACE;
                }
                break;
            
            //case KEYWORD: // Probably unecessary IDENTIFIER can handle it
            //    break;
            
            //case NUM: // Unused
            //    break;

            default: // If there's no match throw an error.
                emergencyBreak = true;
                break;
        }
    }

    return token_list;
}