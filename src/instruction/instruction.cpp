#include "instruction/instruction.hpp"

Instruction Instruction::add(int rd, int rs1, int rs2) {
    return {Operation::ADD, rd, rs1, rs2, 0};
}

Instruction Instruction::sub(int rd, int rs1, int rs2) {
    return {Operation::SUB, rd, rs1, rs2, 0};
}

Instruction Instruction::addi(int rd, int rs1, std::uint32_t immediate) {
    return {Operation::ADDI, rd, rs1, 0, immediate};
}
