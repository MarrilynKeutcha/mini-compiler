#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include <memory>
#include <vector>
#include <string>

// Node structure for the syntax tree
struct Node {
    std::string type;
    std::string value;
    std::vector<std::shared_ptr<Node>> children;
};

// Function to parse the tokens into a syntax tree
std::shared_ptr<Node> parse(const std::vector<Token>& tokens);

// Function to print the syntax tree (for debugging purposes)
void printSyntaxTree(const std::shared_ptr<Node>& node, int depth = 0);

#endif
