#ifndef PROGRAM_PROGRAM_HPP
#define PROGRAM_PROGRAM_HPP

#include <cstdint>
#include <vector>

class Program {
private:
    std::vector<std::uint32_t> instructionWords;

public:
    explicit Program(std::vector<std::uint32_t> instructionWords);

    bool hasInstructionAt(std::uint32_t address) const;
    std::uint32_t getInstructionWordAt(std::uint32_t address) const;
};

#endif
