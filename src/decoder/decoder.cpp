#include "decoder/decoder.hpp"

#include <stdexcept>

int Decoder::getBits(std::uint32_t word, int start, int length) {
    const std::uint32_t mask = (1u << length) - 1;
    return static_cast<int>((word >> start) & mask);
}

std::int32_t Decoder::signExtend12(std::uint32_t value) {
    if ((value & 0x800u) != 0) {
        value |= 0xfffff000u;
    }

    return static_cast<std::int32_t>(value);
}

Instruction Decoder::decode(std::uint32_t word) {
    const int opcode = getBits(word, 0, 7);
    const int rd = getBits(word, 7, 5);
    const int funct3 = getBits(word, 12, 3);
    const int rs1 = getBits(word, 15, 5);

    if (opcode == 0x33) {
        const int rs2 = getBits(word, 20, 5);
        const int funct7 = getBits(word, 25, 7);

        if (funct3 == 0x0 && funct7 == 0x00) {
            return Instruction::add(rd, rs1, rs2);
        }

        if (funct3 == 0x0 && funct7 == 0x20) {
            return Instruction::sub(rd, rs1, rs2);
        }
    }

    if (opcode == 0x13) {
        const std::int32_t immediate = signExtend12(getBits(word, 20, 12));

        if (funct3 == 0x0) {
            return Instruction::addi(rd, rs1, immediate);
        }
    }

    throw std::invalid_argument("unsupported instruction word");
}

std::vector<Instruction> Decoder::decodeProgram(const std::vector<std::uint32_t>& words) {
    std::vector<Instruction> instructions;
    instructions.reserve(words.size());

    for (std::uint32_t word : words) {
        instructions.push_back(decode(word));
    }

    return instructions;
}
