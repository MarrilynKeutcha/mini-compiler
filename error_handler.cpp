#include "error_handler.h"

void logError(const std::string& error) {
    std::cerr << "Compiler Error: " << error << std::endl;
}
