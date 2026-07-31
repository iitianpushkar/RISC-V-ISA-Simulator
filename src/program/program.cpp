#include "program/program.hpp"

#include <stdexcept>
#include <utility>

Program::Program(std::vector<Instruction> instructions)
    : instructions(std::move(instructions)) {}

bool Program::hasInstructionAt(std::uint32_t address) const {
    if (address % 4 != 0) {
        return false;
    }

    return (address / 4) < instructions.size();
}

const Instruction& Program::getInstructionAt(std::uint32_t address) const {
    if (!hasInstructionAt(address)) {
        throw std::out_of_range("no instruction exists at this address");
    }

    return instructions[address / 4];
}
