#ifndef DECODER_DECODER_HPP
#define DECODER_DECODER_HPP

#include "instruction/instruction.hpp"

#include <cstdint>
#include <vector>

class Decoder {
private:
    static int getBits(std::uint32_t word, int start, int length);
    static std::int32_t signExtend12(std::uint32_t value);

public:
    static Instruction decode(std::uint32_t word);
    static std::vector<Instruction> decodeProgram(const std::vector<std::uint32_t>& words);
};

#endif
