#include "optimizer.h"
#include <regex>
#include <map>
#include <iostream>

void optimizeIntermediateCode(std::vector<std::string>& intermediateCode) {
    std::vector<std::string> optimizedCode;
    std::map<std::string, int> constants;  // Tracks variables with known constant values
    std::smatch matches;

    std::regex assignConst(R"(t(\d+)\s*=\s*(\d+))");  // tX = 5
    std::regex binaryExpr(R"(t(\d+)\s*=\s*t(\d+)\s*([\+\-\*/])\s*t(\d+))");  // tX = tY + tZ

    for (std::string& line : intermediateCode) {
        if (std::regex_match(line, matches, assignConst)) {
            std::string var = "t" + matches[1].str();
            int value = std::stoi(matches[2].str());
            constants[var] = value;
            optimizedCode.push_back(line);
        }
        else if (std::regex_match(line, matches, binaryExpr)) {
            std::string resultVar = "t" + matches[1].str();
            std::string leftVar = "t" + matches[2].str();
            std::string rightVar = "t" + matches[4].str();
            char op = matches[3].str()[0];

            if (constants.count(leftVar) && constants.count(rightVar)) {
                int left = constants[leftVar];
                int right = constants[rightVar];
                int result;

                switch (op) {
                    case '+': result = left + right; break;
                    case '-': result = left - right; break;
                    case '*': result = left * right; break;
                    case '/': result = (right != 0) ? left / right : 0; break;
                    default: result = 0;
                }

                constants[resultVar] = result;
                optimizedCode.push_back(resultVar + " = " + std::to_string(result));
            } else {
                optimizedCode.push_back(line);  // Keep original if not foldable
            }
        } else {
            optimizedCode.push_back(line);  // Pass through unoptimized
        }
    }

    intermediateCode = optimizedCode;
}
