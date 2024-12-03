#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <string>
#include <vector>

// Reserved keywords
const std::vector<std::string> keywords = { "int", "return", "if", "while", "for" };

// Operators and delimiters
const std::vector<char> operators = { '+', '-', '*', '/', '=' };
const std::vector<char> delimiters = { ';', '(', ')', '{', '}', ',' };  


#endif
