#include "optimizer.h"
#include <regex>
#include <map>
#include <iostream>

void optimizeIntermediateCode(std::vector<std::string>& intermediateCode) {
    std::vector<std::string> optimizedCode;
    std::map<std::string, int> constants;  // Known constant values for temporaries
    std::smatch matches;

    // Regex patterns
    std::regex assignConst(R"(t(\d+)\s*=\s*(\d+))"); // e.g., t1 = 5
    std::regex binaryExpr(R"(t(\d+)\s*=\s*t(\d+)\s*([\+\-\*/])\s*t(\d+))"); // e.g., t3 = t1 + t2

    for (std::string& line : intermediateCode) {
        if (std::regex_match(line, matches, assignConst)) {
            // Handle constant assignment like: t1 = 5
            std::string var = "t" + matches[1].str();
            int value = std::stoi(matches[2].str());
            constants[var] = value;
            optimizedCode.push_back(line);
        } 
        else if (std::regex_match(line, matches, binaryExpr)) {
            // Handle binary expressions like: t3 = t1 + t2
            std::string resultVar = "t" + matches[1].str();
            std::string leftVar = "t" + matches[2].str();
            std::string rightVar = "t" + matches[4].str();
            char op = matches[3].str()[0];

            bool leftIsConst = constants.count(leftVar);
            bool rightIsConst = constants.count(rightVar);

            // === Constant Folding ===
            if (leftIsConst && rightIsConst) {
                int left = constants[leftVar];
                int right = constants[rightVar];
                int result = 0;

                switch (op) {
                    case '+': result = left + right; break;
                    case '-': result = left - right; break;
                    case '*': result = left * right; break;
                    case '/': result = (right != 0) ? left / right : 0; break;
                    default: break;
                }

                constants[resultVar] = result;
                optimizedCode.push_back(resultVar + " = " + std::to_string(result));
            } 

            // === Expression Simplification ===
            else if ((op == '+' || op == '-') && rightIsConst && constants[rightVar] == 0) {
                optimizedCode.push_back(resultVar + " = " + leftVar);
            } 
            else if (op == '+' && leftIsConst && constants[leftVar] == 0) {
                optimizedCode.push_back(resultVar + " = " + rightVar);
            } 
            else if (op == '*' && rightIsConst && constants[rightVar] == 1) {
                optimizedCode.push_back(resultVar + " = " + leftVar);
            } 
            else if (op == '*' && leftIsConst && constants[leftVar] == 1) {
                optimizedCode.push_back(resultVar + " = " + rightVar);
            } 
            else if (op == '*' && 
                    ((leftIsConst && constants[leftVar] == 0) || 
                     (rightIsConst && constants[rightVar] == 0))) {
                constants[resultVar] = 0;
                optimizedCode.push_back(resultVar + " = 0");
            } 
            else if (op == '/' && rightIsConst && constants[rightVar] == 1) {
                optimizedCode.push_back(resultVar + " = " + leftVar);
            } 
            else {
                // No simplification possible
                optimizedCode.push_back(line);
            }
        } 
        else {
            // Any other line — leave untouched
            optimizedCode.push_back(line);
        }
    }

    // Replace original with optimized version
    intermediateCode = optimizedCode;
}
