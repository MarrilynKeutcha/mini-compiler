#include "lexer.h"
#include "parser.h"
#include "codegen.h"
#include "optimizer.h"
#include <iostream>
#include <string>

int main() {
    while (true) {
        // Step 1: Prompt the user for code input
        std::cout << "Enter your code (or type 'exit' to quit): ";
        std::string code;
        std::getline(std::cin, code);

        // Exit if the user types "exit"
        if (code == "exit") {
            std::cout << "Exiting mini-compiler. Goodbye!\n";
            break;
        }

        // Step 2: Tokenize the input code
        auto tokens = tokenize(code);
        std::cout << "\nTokens:\n";
        for (const auto& token : tokens) {
            std::cout << token.type << " -> " << token.value << "\n";
        }
        std::cout << "\n";

        // Step 3: Parse the tokens into a syntax tree
        auto syntaxTree = parse(tokens);
        if (!syntaxTree) {
            std::cerr << "Parsing failed. Please try again.\n";
            continue;
        }

        // Print the syntax tree for debugging
        std::cout << "Syntax Tree:\n";
        printSyntaxTree(syntaxTree);
        std::cout << "\n";

        // Step 4: Generate intermediate code from the syntax tree
        generateIntermediateCode(syntaxTree);
        std::cout << "Intermediate Code:\n";
        for (const auto& line : intermediateCode) {
            std::cout << line << "\n";
        }
        std::cout << "\n";

        // Step 5: Optimize the intermediate code
        optimizeIntermediateCode(intermediateCode);
        std::cout << "Optimized Intermediate Code:\n";
        for (const auto& line : intermediateCode) {
            std::cout << line << "\n";
        }
        std::cout << "\n";
    }

    return 0;
}
