#include "lexer.hpp"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Constants
const char EMPTYSPACE = ' ';
const char COM = '/';
const string NEWLINE = "\n";

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
        }

        bool eof() {
            return pos == txt.length();
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

vector<char> punctuation {
    '{',
    '}',
    '.'
};

vector<char> operators {
    '=',
    '+',
    '/'
};


string stringify_file(string txt_file, bool add_line_breaks) {
    string myText;
    string newText;
    ifstream MyReadFile(txt_file);

    while (getline (MyReadFile, myText)) {
        newText += myText;
        if (add_line_breaks) {
            newText += "\n";
        }
    }

    MyReadFile.close();

    return newText;
}

vector<token> tokenize(string txt) {
    // Denotes what type the lexer assumes the current char is from
    token_type state = WHITESPACE;
    vector<token> token_list;

    StringReader scriptReader(txt);
    string word;

    while (not scriptReader.eof()) {
        switch (state) {
            case WHITESPACE:
                if (scriptReader.current_char == EMPTYSPACE) {
                    scriptReader.read_next();
                }
                else if (scriptReader.current_char == COM and scriptReader.next_char == COM) {
                    state = COMMENT;
                }
                else if (any_of(punctuation.begin(), punctuation.end(), scriptReader.current_char)) {
                    state = PUNCTUATION;
                }
                else if (isalnum(scriptReader.current_char)) {
                    state = IDENTIFIER;
                }
                //else if (isdigit(scriptReader.current_char)) {
                //    state = NUM;
                //}
                break;

            case COMMENT:
                if (scriptReader.current_char == NEWLINE[0] and scriptReader.next_char == NEWLINE[1]) {
                    state = WHITESPACE;
                }
                else {
                    scriptReader.read_next();
                }
                break;

            case PUNCTUATION:
                break;

            case KEYWORD:
                break;

            case IDENTIFIER:
                break;
            
            case NUM: // Unused
                break;

            default: // If there's no match throw an error.
                break;
        }
    }

    return token_list;
}