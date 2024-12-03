#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <iostream>
#include "grammar.h"

struct Token {
    std::string type;
    std::string value;
};

std::vector<Token> tokenize(const std::string& code);

#endif
