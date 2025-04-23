#include "optimizer.h"
#include <regex>
#include <set>
#include <iostream>

void optimizeIntermediateCode(std::vector<std::string>& intermediateCode) {
    std::vector<std::string> optimizedCode;
    std::set<std::string> usedVars; // Track used variables
    std::smatch matches;           // For regex matching

    for (std::string line : intermediateCode) {
        std::regex constFoldRegex(R"((t\d+) = (\d+) ([+\-*/]) (\d+))");
        if (std::regex_match(line, matches, constFoldRegex)) {
            int left = std::stoi(matches[2].str());
            int right = std::stoi(matches[4].str());
            char op = matches[3].str()[0];
            int result = (op == '+') ? left + right :
                         (op == '-') ? left - right :
                         (op == '*') ? left * right :
                         (right != 0 ? left / right : 0);
            line = matches[1].str() + " = " + std::to_string(result);
        }
        optimizedCode.push_back(line);
    }
    intermediateCode = optimizedCode;
}
