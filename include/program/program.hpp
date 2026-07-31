#ifndef PROGRAM_PROGRAM_HPP
#define PROGRAM_PROGRAM_HPP

#include "instruction/instruction.hpp"

#include <cstdint>
#include <vector>

class Program {
private:
    std::vector<Instruction> instructions;

public:
    explicit Program(std::vector<Instruction> instructions);

    bool hasInstructionAt(std::uint32_t address) const;
    const Instruction& getInstructionAt(std::uint32_t address) const;
};

#endif
