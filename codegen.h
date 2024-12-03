#ifndef CODEGEN_H
#define CODEGEN_H

#include "parser.h"
#include <vector>
#include <string>

// Declare intermediateCode as an external variable
extern std::vector<std::string> intermediateCode;

void generateIntermediateCode(const std::shared_ptr<Node>& node);

#endif
