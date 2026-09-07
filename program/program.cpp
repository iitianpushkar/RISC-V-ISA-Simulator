#include "program/program.hpp"

#include <stdexcept>
#include <utility>

Program::Program(std::vector<std::uint32_t> instructionWords)
    : instructionWords(std::move(instructionWords)) {}

bool Program::hasInstructionAt(std::uint32_t address) const {
    if (address % 4 != 0) {
        return false;
    }

    return (address / 4) < instructionWords.size();
}

std::uint32_t Program::getInstructionWordAt(std::uint32_t address) const {
    if (!hasInstructionAt(address)) {
        throw std::out_of_range("no instruction exists at this address");
    }

    return instructionWords[address / 4];
}
