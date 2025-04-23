#include "codegen.h"
#include <iostream>

// Define intermediateCode as a global variable
std::vector<std::string> intermediateCode;

int tempVar = 0;

void generateIntermediateCode(const std::shared_ptr<Node>& node) {
    if (!node) return;

    if (node->type == "FUNCTION") {
        intermediateCode.push_back("Function: " + node->value);
        for (const auto& child : node->children) {
            generateIntermediateCode(child); // Process parameters and body
        }
    }
    else if (node->type == "PARAMETER") {
        // Optionally include parameters in the intermediate code (debugging or clarity)
        intermediateCode.push_back("Parameter: " + node->value);
    }
    else if (node->type == "RETURN") {
        generateIntermediateCode(node->children[0]); // Process the return expression
        intermediateCode.push_back("RETURN t" + std::to_string(tempVar - 1)); // Use the last temp variable
    }
    else if (node->type == "EXPRESSION") {
        generateIntermediateCode(node->children[0]); // Process the left operand
        int leftTempVar = tempVar - 1; // Save the left temp variable

        generateIntermediateCode(node->children[1]); // Process the right operand
        int rightTempVar = tempVar - 1; // Save the right temp variable

        intermediateCode.push_back("t" + std::to_string(tempVar++) + " = t" +
            std::to_string(leftTempVar) + " " + node->value + " t" +
            std::to_string(rightTempVar));
    }
    else if (node->type == "TERM") {
        // Handle variables or constants
        intermediateCode.push_back("t" + std::to_string(tempVar++) + " = " + node->value);
    }
}