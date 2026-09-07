#include "cpu/cpu.hpp"

#include "alu/alu.hpp"
#include "control/control_unit.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>

namespace {

std::uint32_t pcWithOffset(std::uint32_t pc, std::int32_t offset) {
    return static_cast<std::uint32_t>(static_cast<std::int32_t>(pc) + offset);
}

std::string registerWriteText(int reg, std::uint32_t value) {
    std::ostringstream output;
    output << "x" << reg << " = " << value;
    return output.str();
}

} // namespace

Registers& Cpu::getRegisters() {
    return registers;
}

const Registers& Cpu::getRegisters() const {
    return registers;
}

Memory& Cpu::getMemory() {
    return memory;
}

const Memory& Cpu::getMemory() const {
    return memory;
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

void Cpu::traceExecution(const Instruction& instruction,
                         const ExecutionResult& result) const {
    const ControlSignals signals = ControlUnit::generate(instruction.operation);

    std::cout << "pc " << result.oldPc << ": " << instruction.toString() << '\n';
    std::cout << "  IF: fetch instruction at pc " << result.oldPc << '\n';
    std::cout << "  ID: decode " << instruction.toString() << '\n';
    std::cout << "  CTRL: RegWrite=" << signals.regWrite
              << " MemRead=" << signals.memRead
              << " MemWrite=" << signals.memWrite
              << " Branch=" << signals.branch
              << " Jump=" << signals.jump
              << " ALUSrc=" << (signals.aluSrcImmediate ? "imm" : "reg")
              << " ALU=" << signals.aluOperation
              << " WB=" << signals.writeBackSource << '\n';
    std::cout << "  EX: " << result.executeStage << '\n';
    std::cout << "  MEM: " << result.memoryStage << '\n';
    std::cout << "  WB: " << result.writeBackStage << '\n';
    std::cout << "  PC: pc -> " << result.nextPc << '\n';
}

ExecutionResult Cpu::execute(const Instruction& instruction) {
    ExecutionResult result;
    result.oldPc = pc;
    result.nextPc = pc + 4;

    std::ostringstream executeStage;

    switch (instruction.operation) {
        case Operation::ADD: {
            const std::uint32_t left = registers.read(instruction.rs1);
            const std::uint32_t right = registers.read(instruction.rs2);
            const std::uint32_t value = Alu::add(left, right);

            executeStage << "x" << instruction.rs1 << "(" << left << ") + x"
                         << instruction.rs2 << "(" << right << ") = " << value;
            result.regWritten = instruction.rd != 0;
            result.writtenRegister = instruction.rd;
            result.writtenValue = value;
            result.writeBackStage = registerWriteText(instruction.rd, value);
            registers.write(instruction.rd, value);
            break;
        }
        case Operation::SUB: {
            const std::uint32_t left = registers.read(instruction.rs1);
            const std::uint32_t right = registers.read(instruction.rs2);
            const std::uint32_t value = Alu::subtract(left, right);

            executeStage << "x" << instruction.rs1 << "(" << left << ") - x"
                         << instruction.rs2 << "(" << right << ") = " << value;
            result.regWritten = instruction.rd != 0;
            result.writtenRegister = instruction.rd;
            result.writtenValue = value;
            result.writeBackStage = registerWriteText(instruction.rd, value);
            registers.write(instruction.rd, value);
            break;
        }
        case Operation::ADDI: {
            const std::uint32_t left = registers.read(instruction.rs1);
            const std::uint32_t value =
                Alu::add(left, static_cast<std::uint32_t>(instruction.immediate));

            executeStage << "x" << instruction.rs1 << "(" << left << ") + "
                         << instruction.immediate << " = " << value;
            result.regWritten = instruction.rd != 0;
            result.writtenRegister = instruction.rd;
            result.writtenValue = value;
            result.writeBackStage = registerWriteText(instruction.rd, value);
            registers.write(instruction.rd, value);
            break;
        }
        case Operation::AND: {
            const std::uint32_t left = registers.read(instruction.rs1);
            const std::uint32_t right = registers.read(instruction.rs2);
            const std::uint32_t value = Alu::bitwiseAnd(left, right);

            executeStage << "x" << instruction.rs1 << "(" << left << ") & x"
                         << instruction.rs2 << "(" << right << ") = " << value;
            result.regWritten = instruction.rd != 0;
            result.writtenRegister = instruction.rd;
            result.writtenValue = value;
            result.writeBackStage = registerWriteText(instruction.rd, value);
            registers.write(instruction.rd, value);
            break;
        }
        case Operation::OR: {
            const std::uint32_t left = registers.read(instruction.rs1);
            const std::uint32_t right = registers.read(instruction.rs2);
            const std::uint32_t value = Alu::bitwiseOr(left, right);

            executeStage << "x" << instruction.rs1 << "(" << left << ") | x"
                         << instruction.rs2 << "(" << right << ") = " << value;
            result.regWritten = instruction.rd != 0;
            result.writtenRegister = instruction.rd;
            result.writtenValue = value;
            result.writeBackStage = registerWriteText(instruction.rd, value);
            registers.write(instruction.rd, value);
            break;
        }
        case Operation::XOR: {
            const std::uint32_t left = registers.read(instruction.rs1);
            const std::uint32_t right = registers.read(instruction.rs2);
            const std::uint32_t value = Alu::bitwiseXor(left, right);

            executeStage << "x" << instruction.rs1 << "(" << left << ") ^ x"
                         << instruction.rs2 << "(" << right << ") = " << value;
            result.regWritten = instruction.rd != 0;
            result.writtenRegister = instruction.rd;
            result.writtenValue = value;
            result.writeBackStage = registerWriteText(instruction.rd, value);
            registers.write(instruction.rd, value);
            break;
        }
        case Operation::ANDI: {
            const std::uint32_t left = registers.read(instruction.rs1);
            const std::uint32_t value =
                Alu::bitwiseAnd(left, static_cast<std::uint32_t>(instruction.immediate));

            executeStage << "x" << instruction.rs1 << "(" << left << ") & "
                         << instruction.immediate << " = " << value;
            result.regWritten = instruction.rd != 0;
            result.writtenRegister = instruction.rd;
            result.writtenValue = value;
            result.writeBackStage = registerWriteText(instruction.rd, value);
            registers.write(instruction.rd, value);
            break;
        }
        case Operation::ORI: {
            const std::uint32_t left = registers.read(instruction.rs1);
            const std::uint32_t value =
                Alu::bitwiseOr(left, static_cast<std::uint32_t>(instruction.immediate));

            executeStage << "x" << instruction.rs1 << "(" << left << ") | "
                         << instruction.immediate << " = " << value;
            result.regWritten = instruction.rd != 0;
            result.writtenRegister = instruction.rd;
            result.writtenValue = value;
            result.writeBackStage = registerWriteText(instruction.rd, value);
            registers.write(instruction.rd, value);
            break;
        }
        case Operation::XORI: {
            const std::uint32_t left = registers.read(instruction.rs1);
            const std::uint32_t value =
                Alu::bitwiseXor(left, static_cast<std::uint32_t>(instruction.immediate));

            executeStage << "x" << instruction.rs1 << "(" << left << ") ^ "
                         << instruction.immediate << " = " << value;
            result.regWritten = instruction.rd != 0;
            result.writtenRegister = instruction.rd;
            result.writtenValue = value;
            result.writeBackStage = registerWriteText(instruction.rd, value);
            registers.write(instruction.rd, value);
            break;
        }
        case Operation::LW: {
            const std::uint32_t base = registers.read(instruction.rs1);
            const std::uint32_t address =
                Alu::add(base, static_cast<std::uint32_t>(instruction.immediate));
            const std::uint32_t value = memory.readWord(address);

            executeStage << "address = x" << instruction.rs1 << "(" << base
                         << ") + " << instruction.immediate << " = " << address;
            result.memoryRead = true;
            result.memoryAddress = address;
            result.memoryValue = value;
            result.memoryStage = "read memory[" + std::to_string(address) +
                                 "] = " + std::to_string(value);
            result.regWritten = instruction.rd != 0;
            result.writtenRegister = instruction.rd;
            result.writtenValue = value;
            result.writeBackStage = registerWriteText(instruction.rd, value);
            registers.write(instruction.rd, value);
            break;
        }
        case Operation::SW: {
            const std::uint32_t base = registers.read(instruction.rs1);
            const std::uint32_t address =
                Alu::add(base, static_cast<std::uint32_t>(instruction.immediate));
            const std::uint32_t value = registers.read(instruction.rs2);

            executeStage << "address = x" << instruction.rs1 << "(" << base
                         << ") + " << instruction.immediate << " = " << address;
            result.memoryWritten = true;
            result.memoryAddress = address;
            result.memoryValue = value;
            result.memoryStage = "memory[" + std::to_string(address) + "] = x" +
                                 std::to_string(instruction.rs2) + "(" +
                                 std::to_string(value) + ")";
            memory.writeWord(address, value);
            break;
        }
        case Operation::BEQ: {
            const std::uint32_t left = registers.read(instruction.rs1);
            const std::uint32_t right = registers.read(instruction.rs2);
            result.branchTaken = left == right;
            result.nextPc = result.branchTaken ? pcWithOffset(pc, instruction.immediate) : pc + 4;

            executeStage << "compare x" << instruction.rs1 << "(" << left
                         << ") == x" << instruction.rs2 << "(" << right
                         << "): " << (result.branchTaken ? "true" : "false");
            break;
        }
        case Operation::BNE: {
            const std::uint32_t left = registers.read(instruction.rs1);
            const std::uint32_t right = registers.read(instruction.rs2);
            result.branchTaken = left != right;
            result.nextPc = result.branchTaken ? pcWithOffset(pc, instruction.immediate) : pc + 4;

            executeStage << "compare x" << instruction.rs1 << "(" << left
                         << ") != x" << instruction.rs2 << "(" << right
                         << "): " << (result.branchTaken ? "true" : "false");
            break;
        }
        case Operation::JAL: {
            const std::uint32_t returnAddress = pc + 4;
            result.nextPc = pcWithOffset(pc, instruction.immediate);

            executeStage << "target = pc(" << pc << ") + "
                         << instruction.immediate << " = " << result.nextPc;
            result.regWritten = instruction.rd != 0;
            result.writtenRegister = instruction.rd;
            result.writtenValue = returnAddress;
            result.writeBackStage = "x" + std::to_string(instruction.rd) +
                                    " = return address " +
                                    std::to_string(returnAddress);
            registers.write(instruction.rd, returnAddress);
            break;
        }
        case Operation::JALR: {
            const std::uint32_t base = registers.read(instruction.rs1);
            const std::uint32_t rawTarget =
                Alu::add(base, static_cast<std::uint32_t>(instruction.immediate));
            const std::uint32_t returnAddress = pc + 4;
            result.nextPc = rawTarget & ~1u;

            executeStage << "target = (x" << instruction.rs1 << "(" << base
                         << ") + " << instruction.immediate << ") & ~1 = "
                         << result.nextPc;
            result.regWritten = instruction.rd != 0;
            result.writtenRegister = instruction.rd;
            result.writtenValue = returnAddress;
            result.writeBackStage = "x" + std::to_string(instruction.rd) +
                                    " = return address " +
                                    std::to_string(returnAddress);
            registers.write(instruction.rd, returnAddress);
            break;
        }
        default:
            throw std::invalid_argument("unsupported instruction operation");
    }

    result.executeStage = executeStage.str();
    pc = result.nextPc;
    return result;
}

void Cpu::run(const Program& program, bool trace) {
    while (program.hasInstructionAt(pc)) {
        const Instruction& instruction = program.getInstructionAt(pc);
        const ExecutionResult result = execute(instruction);

        if (trace) {
            traceExecution(instruction, result);
        }
    }
}

void Cpu::dumpState() const {
    std::cout << "pc: " << pc << '\n';
    registers.dump();
}
