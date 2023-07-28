#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string_view>
#include <vector>

#include "inc/cmdlineParser.hpp"

namespace cmdlineParser {
int parse(int argc, char* argv[]) {
    if (argc == 1) {
        throw std::runtime_error("parser: No extra parameter passed in");
        return EXIT_FAILURE;
    }
    const std::vector<std::string_view> args(argv + 1, argv + argc);
    for (const auto& arg : args) {
        if (arg == "-h" || arg == "--help") {
            _isHelpMessage = 1;
            return EXIT_SUCCESS;
        }
        if (arg == "-i" || arg == "--inexisted") {
            _isCompInexisted = 1;
        } else if (arg == "-d" || arg == "--duplicated") {
            _isCompDuplicated = 1;
        }
    }
    if (_isCompDuplicated == 1 && _isCompInexisted == 1) {
        throw std::runtime_error("parser: -d and -i cannot be true at the same time.");
        return EXIT_FAILURE;
    }
    return 0;
}

int getInex() {
    return _isCompInexisted;
}

int getDup() {
    return _isCompDuplicated;
}

int getHelp() {
    return _isHelpMessage;
}
} // namespace cmdlineParser
