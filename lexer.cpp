#include "lexer.h"
#include <algorithm>

std::vector<Token> tokenize(const std::string& code) {
    std::vector<Token> tokens;
    std::string current;

    for (size_t i = 0; i < code.length(); i++) {
        char c = code[i];

   
        if (isspace(c)) continue;

        // Handle numbers
        if (isdigit(c)) {
            current += c;
            while (i + 1 < code.length() && isdigit(code[i + 1])) {
                current += code[++i];
            }
            tokens.push_back({ "NUMBER", current });
            current = "";
        }
        // Handle keywords and identifiers
        else if (isalpha(c)) {
            current += c;
            while (i + 1 < code.length() && (isalnum(code[i + 1]) || code[i + 1] == '_')) {
                current += code[++i];
            }
            if (std::find(keywords.begin(), keywords.end(), current) != keywords.end()) {
                tokens.push_back({ "KEYWORD", current });  // Recognize as a keyword
            }
            else {
                tokens.push_back({ "IDENTIFIER", current });  // Recognize as an identifier
            }
            current = "";
        }
        // Handle operators and delimiters
        else if (std::find(operators.begin(), operators.end(), static_cast<char>(c)) != operators.end()) {
            tokens.push_back({ "OPERATOR", std::string(1, c) });
        }
        else if (std::find(delimiters.begin(), delimiters.end(), static_cast<char>(c)) != delimiters.end()) {
            tokens.push_back({ "DELIMITER", std::string(1, c) });
        }        
        else {
            std::cerr << "Error: Unrecognized character '" << c << "'\n";
        }
    }
    return tokens;
}
