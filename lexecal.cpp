#include <iostream>
#include <regex>
#include <vector>
#include <string>
#include <map>

using namespace std;

// Enum for token types
enum TokenType {
    ID,
    NUM,
    PLUS,
    MINUS,
    MULT,
    DIV,
    LEFTPAREN,
    RIGHTPAREN
};

// Map enum values to string names
map<TokenType, string> tokenTypeNames = {
        {ID, "ID"},
        {NUM, "NUM"},
        {PLUS, "PLUS"},
        {MINUS, "MINUS"},
        {MULT, "MULT"},
        {DIV, "DIV"},
        {LEFTPAREN, "LEFTPAREN"},
        {RIGHTPAREN, "RIGHTPAREN"}
};

// Define a token structure
struct Token {
    TokenType type;
    string value;
};

// Lexical analyzer function
vector<Token> lexer(const string& sourceCode) {
    vector<Token> tokens;

    vector<pair<TokenType, string>> patterns = {
            {ID, "[a-zA-Z_]\\w*"},
            {NUM, "\\d+"},
            {PLUS, "\\+"},
            {MINUS, "\\-"},
            {MULT, "\\*"},
            {DIV, "\\/"},
            {LEFTPAREN, "\\("},
            {RIGHTPAREN, "\\)"}
    };

    smatch match;

    string remaining = sourceCode;
    while (!remaining.empty()) {
        bool matched = false;

        // Try to match each pattern
        for (const auto& [type, pattern] : patterns) {
            regex regex(pattern);
            if (regex_search(remaining, match, regex)) {
                tokens.push_back({type, match.str()});
                remaining = match.suffix();
                matched = true;
                break;
            }
        }

        if (!matched) {
            cerr << "Error: Invalid character in source code: " << remaining[0] << endl;
            break;
        }
    }

    return tokens;
}

// Function to print tokens with type names
void printTokens(const vector<Token>& tokens) {
    for (const auto& token : tokens) {
        cout << "Type: " << tokenTypeNames[token.type] << "\tValue: " << token.value << endl;
    }
}

int main() {
    string sourceCode = "32 1 \\ / 3 ; . < ?";
    vector<Token> tokens = lexer(sourceCode);

    printTokens(tokens);

    return 0;
}
