#include "lexer.hpp"
#include <fstream>
#include <string>
#include <vector>
using namespace std;

string keywords[] {
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
    char current_char;
    int pos = 0, line = 1, col = 0;

    switch (state) {
        case WHITESPACE:
            break;
        case COMMENT:
            break;
        case PUNCTUATION:
            break;
        case KEYWORD:
            break;
        case IDENTIFIER:
            break;
        default: // If there's no match throw an error.
            break;
    }

    return token_list;
}

// Probably will need to make multiple tokenizers due to how paradox script works.
// So having a standalone object for string reading will be useful.
class InputStream {
    private:
        int pos = 0, line = 1, col = 0;
        char current_char, next_char;
        string txt;

        InputStream(string txt_source) {
            txt = txt_source;
            current_char = txt[0];
            next_char = txt[1];
        }

        char next();

        bool check_eof();

        void croak();
};