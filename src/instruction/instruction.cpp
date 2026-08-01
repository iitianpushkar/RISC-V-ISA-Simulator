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
        default:
            throw std::invalid_argument("unsupported instruction operation");
    }

    return output.str();
}
