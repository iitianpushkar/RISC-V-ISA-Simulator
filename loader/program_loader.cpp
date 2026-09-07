#include "loader/program_loader.hpp"

#include <fstream>
#include <limits>
#include <stdexcept>
#include <string>

std::vector<std::uint32_t> ProgramLoader::load(const std::string& filePath) {
    std::ifstream input(filePath);

    if (!input.is_open()) {
        throw std::runtime_error("could not open program file: " + filePath);
    }

    std::vector<std::uint32_t> words;
    std::string line;
    int lineNumber = 0;

    while (std::getline(input, line)) {
        ++lineNumber;

        const std::size_t firstCharacter = line.find_first_not_of(" \t\r");
        if (firstCharacter == std::string::npos) {
            continue;
        }

        std::size_t parsedCharacters = 0;
        unsigned long long value = 0;

        try {
            value = std::stoull(line.substr(firstCharacter), &parsedCharacters, 16);
        } catch (const std::exception&) {
            throw std::runtime_error("invalid instruction at line " +
                                     std::to_string(lineNumber));
        }

        const std::string remaining = line.substr(firstCharacter + parsedCharacters);
        if (remaining.find_first_not_of(" \t\r") != std::string::npos ||
            value > std::numeric_limits<std::uint32_t>::max()) {
            throw std::runtime_error("invalid instruction at line " +
                                     std::to_string(lineNumber));
        }

        words.push_back(static_cast<std::uint32_t>(value));
    }

    return words;
}
