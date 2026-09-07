#include "control/control_unit.hpp"

#include <stdexcept>

ControlSignals ControlUnit::generate(const Operation& operation) {
    switch (operation) {
        case Operation::ADD:
            return {true, false, false, false, false, false, "ADD", "ALU"};
        case Operation::SUB:
            return {true, false, false, false, false, false, "SUB", "ALU"};
        case Operation::ADDI:
            return {true, false, false, false, false, true, "ADD", "ALU"};
        case Operation::AND:
            return {true, false, false, false, false, false, "AND", "ALU"};
        case Operation::OR:
            return {true, false, false, false, false, false, "OR", "ALU"};
        case Operation::XOR:
            return {true, false, false, false, false, false, "XOR", "ALU"};
        case Operation::ANDI:
            return {true, false, false, false, false, true, "AND", "ALU"};
        case Operation::ORI:
            return {true, false, false, false, false, true, "OR", "ALU"};
        case Operation::XORI:
            return {true, false, false, false, false, true, "XOR", "ALU"};
        case Operation::LW:
            return {true, true, false, false, false, true, "ADD", "MEM"};
        case Operation::SW:
            return {false, false, true, false, false, true, "ADD", "NONE"};
        case Operation::BEQ:
        case Operation::BNE:
            return {false, false, false, true, false, false, "COMPARE", "NONE"};
        case Operation::JAL:
            return {true, false, false, false, true, true, "ADD", "PC+4"};
        case Operation::JALR:
            return {true, false, false, false, true, true, "ADD", "PC+4"};
        default:
            throw std::invalid_argument("unsupported operation for control unit");
    }
}
