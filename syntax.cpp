#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Token {
    string type;
    string value;
};

vector<Token> syntax_analysis(vector<Token> tokens) {

    if (tokens.size() >= 7 &&
        tokens[0].type == "keyword" && tokens[0].value == "int" &&
        tokens[1].type == "identifier" &&
        tokens[2].type == "symbol" && tokens[2].value == "(" &&
        tokens[3].type == "symbol" && tokens[3].value == ")" &&
        tokens[4].type == "symbol" && tokens[4].value == "{" &&
        tokens[5].type == "keyword" && tokens[5].value == "return" &&
        tokens[6].type == "number" &&
        tokens[7].type == "symbol" && tokens[7].value == ";") {

        vector<Token> parse_tree = {
                {"FunctionDeclaration", ""},
                {"ReturnType", "int"},
                {"FunctionName", tokens[1].value},
                {"ReturnValue", tokens[6].value}
        };
        return parse_tree;
    } else {

        return {};
    }
}

int main() {
    string input = "int main() { return 0; }";

    vector<Token> tokens = {
            {"keyword", "int"},
            {"identifier", "main"},
            {"symbol", "("},
            {"symbol", ")"},
            {"symbol", "{"},
            {"keyword", "return"},
            {"number", "0"},
            {"symbol", ";"},
            {"symbol", "}"},
    };

    vector<Token> parse_tree = syntax_analysis(tokens);

    if (!parse_tree.empty()) {
        for (Token token : parse_tree) {
            cout << token.type << ": " << token.value << endl;
        }
    } else {
        cout << "Syntax error: Invalid program structure." << endl;
    }

    return 0;
}
