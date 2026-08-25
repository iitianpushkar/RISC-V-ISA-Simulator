#include "instruction/instruction.hpp"

#include <sstream>
#include <stdexcept>

Instruction Instruction::add(int rd, int rs1, int rs2) {
    return {Operation::ADD, rd, rs1, rs2, 0};
}

Instruction Instruction::sub(int rd, int rs1, int rs2) {
    return {Operation::SUB, rd, rs1, rs2, 0};
}

Instruction Instruction::addi(int rd, int rs1, std::int32_t immediate) {
    return {Operation::ADDI, rd, rs1, 0, immediate};
}

Instruction Instruction::bitwiseAnd(int rd, int rs1, int rs2) {
    return {Operation::AND, rd, rs1, rs2, 0};
}

Instruction Instruction::bitwiseOr(int rd, int rs1, int rs2) {
    return {Operation::OR, rd, rs1, rs2, 0};
}

Instruction Instruction::bitwiseXor(int rd, int rs1, int rs2) {
    return {Operation::XOR, rd, rs1, rs2, 0};
}

Instruction Instruction::andi(int rd, int rs1, std::int32_t immediate) {
    return {Operation::ANDI, rd, rs1, 0, immediate};
}

Instruction Instruction::ori(int rd, int rs1, std::int32_t immediate) {
    return {Operation::ORI, rd, rs1, 0, immediate};
}

Instruction Instruction::xori(int rd, int rs1, std::int32_t immediate) {
    return {Operation::XORI, rd, rs1, 0, immediate};
}

Instruction Instruction::lw(int rd, int rs1, std::int32_t immediate) {
    return {Operation::LW, rd, rs1, 0, immediate};
}

Instruction Instruction::sw(int rs2, int rs1, std::int32_t immediate) {
    return {Operation::SW, 0, rs1, rs2, immediate};
}

Instruction Instruction::beq(int rs1, int rs2, std::int32_t immediate) {
    return {Operation::BEQ, 0, rs1, rs2, immediate};
}

Instruction Instruction::bne(int rs1, int rs2, std::int32_t immediate) {
    return {Operation::BNE, 0, rs1, rs2, immediate};
}

Instruction Instruction::jal(int rd, std::int32_t immediate) {
    return {Operation::JAL, rd, 0, 0, immediate};
}

Instruction Instruction::jalr(int rd, int rs1, std::int32_t immediate) {
    return {Operation::JALR, rd, rs1, 0, immediate};
}

std::string Instruction::toString() const {
    std::ostringstream output;

    switch (operation) {
        case Operation::ADD:
            output << "add x" << rd << ", x" << rs1 << ", x" << rs2;
            break;
        case Operation::SUB:
            output << "sub x" << rd << ", x" << rs1 << ", x" << rs2;
            break;
        case Operation::ADDI:
            output << "addi x" << rd << ", x" << rs1 << ", " << immediate;
            break;
        case Operation::AND:
            output << "and x" << rd << ", x" << rs1 << ", x" << rs2;
            break;
        case Operation::OR:
            output << "or x" << rd << ", x" << rs1 << ", x" << rs2;
            break;
        case Operation::XOR:
            output << "xor x" << rd << ", x" << rs1 << ", x" << rs2;
            break;
        case Operation::ANDI:
            output << "andi x" << rd << ", x" << rs1 << ", " << immediate;
            break;
        case Operation::ORI:
            output << "ori x" << rd << ", x" << rs1 << ", " << immediate;
            break;
        case Operation::XORI:
            output << "xori x" << rd << ", x" << rs1 << ", " << immediate;
            break;
        case Operation::LW:
            output << "lw x" << rd << ", " << immediate << "(x" << rs1 << ")";
            break;
        case Operation::SW:
            output << "sw x" << rs2 << ", " << immediate << "(x" << rs1 << ")";
            break;
        case Operation::BEQ:
            output << "beq x" << rs1 << ", x" << rs2 << ", " << immediate;
            break;
        case Operation::BNE:
            output << "bne x" << rs1 << ", x" << rs2 << ", " << immediate;
            break;
        case Operation::JAL:
            output << "jal x" << rd << ", " << immediate;
            break;
        case Operation::JALR:
            output << "jalr x" << rd << ", " << immediate << "(x" << rs1 << ")";
            break;
        default:
            throw std::invalid_argument("unsupported instruction operation");
    }

    return output.str();
}
