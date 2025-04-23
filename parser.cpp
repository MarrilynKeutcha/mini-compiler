#include "parser.h"
#include "error_handler.h"
#include <iostream>

// Recursive function to parse expressions
std::shared_ptr<Node> parseExpression(const std::vector<Token>& tokens, size_t& pos) {
    auto node = std::make_shared<Node>();

    // Skip "int" if it's mistakenly treated as a term
    if (tokens[pos].type == "KEYWORD" && tokens[pos].value == "int") {
        pos++; // Skip the keyword
    }

    node->type = "TERM";
    node->value = tokens[pos++].value;

    // Check if the next token is an operator
    if (pos < tokens.size() && tokens[pos].type == "OPERATOR") {
        auto exprNode = std::make_shared<Node>();
        exprNode->type = "EXPRESSION";
        exprNode->value = tokens[pos++].value; // Store the operator
        exprNode->children.push_back(node); // Left-hand side of the operator
        exprNode->children.push_back(parseExpression(tokens, pos)); // Right-hand side of the operator
        return exprNode;
    }

    return node; // Return the single term node if no operator is found
}

// Main parse function to handle function definitions
std::shared_ptr<Node> parse(const std::vector<Token>& tokens) {
    size_t pos = 0;

    // Check for function declaration
    if (tokens[pos].type == "KEYWORD" && tokens[pos].value == "int") {
        pos++; // Skip "int"

        auto funcNode = std::make_shared<Node>();
        funcNode->type = "FUNCTION";
        funcNode->value = tokens[pos++].value; // Function name

        // Parse parameters
        if (tokens[pos++].value == "(") {
            while (tokens[pos].value != ")") {
                if (tokens[pos].type == "KEYWORD" && tokens[pos].value == "int") {
                    pos++; // Skip "int" for parameter type
                    funcNode->children.push_back(std::make_shared<Node>(Node{ "PARAMETER", tokens[pos++].value }));
                }
                if (tokens[pos].value == ",") {
                    pos++; // Skip commas
                }
            }
            pos++; // Skip closing parenthesis
        }

        // Parse function body
        if (tokens[pos++].value == "{") {
            while (tokens[pos].value != "return") {
                pos++; // Skip intermediate statements (not handled in this example)
            }

            // Parse return statement
            auto returnNode = std::make_shared<Node>();
            returnNode->type = "RETURN";
            returnNode->children.push_back(parseExpression(tokens, ++pos)); // Parse the return expression
            funcNode->children.push_back(returnNode);

            if (tokens[pos].value == "}") {
                pos++; // Skip closing brace
            }
        }

        return funcNode; // Return the function node
    }

    // Fallback: Just parse as an expression if no function is detected
    return parseExpression(tokens, pos);
}

// Recursive function to print the syntax tree
void printSyntaxTree(const std::shared_ptr<Node>& node, int depth) {
    if (!node) return;

    // Print the current node with indentation
    std::cout << std::string(depth * 2, ' ') << node->type << ": " << node->value << std::endl;

    // Recursively print all children of the current node
    for (const auto& child : node->children) {
        printSyntaxTree(child, depth + 1);
    }
}