#include "cpu/cpu.hpp"

#include "alu/alu.hpp"

#include <iostream>
#include <stdexcept>

Registers& Cpu::getRegisters() {
    return registers;
}

const Registers& Cpu::getRegisters() const {
    return registers;
}

std::uint32_t Cpu::getPc() const {
    return pc;
}

void Cpu::setPc(std::uint32_t value) {
    pc = value;
}

void Cpu::advancePc() {
    pc += 4;
}

void Cpu::executeAdd(int rd, int rs1, int rs2) {
    const std::uint32_t result = Alu::add(registers.read(rs1), registers.read(rs2));
    registers.write(rd, result);
    advancePc();
}

void Cpu::executeSub(int rd, int rs1, int rs2) {
    const std::uint32_t result = Alu::subtract(registers.read(rs1), registers.read(rs2));
    registers.write(rd, result);
    advancePc();
}

void Cpu::executeAddi(int rd, int rs1, std::int32_t immediate) {
    const std::uint32_t result = Alu::add(registers.read(rs1), static_cast<std::uint32_t>(immediate));
    registers.write(rd, result);
    advancePc();
}

void Cpu::execute(const Instruction& instruction) {
    switch (instruction.operation) {
        case Operation::ADD:
            executeAdd(instruction.rd, instruction.rs1, instruction.rs2);
            break;
        case Operation::SUB:
            executeSub(instruction.rd, instruction.rs1, instruction.rs2);
            break;
        case Operation::ADDI:
            executeAddi(instruction.rd, instruction.rs1, instruction.immediate);
            break;
        default:
            throw std::invalid_argument("unsupported instruction operation");
    }
}

void Cpu::run(const Program& program, bool trace) {
    while (program.hasInstructionAt(pc)) {
        const Instruction& instruction = program.getInstructionAt(pc);

        if (trace) {
            std::cout << "pc " << pc << ": " << instruction.toString() << '\n';
        }

        execute(instruction);
    }
}

void Cpu::dumpState() const {
    std::cout << "pc: " << pc << '\n';
    registers.dump();
}
