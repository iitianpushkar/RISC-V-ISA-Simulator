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

void Cpu::executeAnd(int rd, int rs1, int rs2) {
    const std::uint32_t result = Alu::bitwiseAnd(registers.read(rs1), registers.read(rs2));
    registers.write(rd, result);
    advancePc();
}

void Cpu::executeOr(int rd, int rs1, int rs2) {
    const std::uint32_t result = Alu::bitwiseOr(registers.read(rs1), registers.read(rs2));
    registers.write(rd, result);
    advancePc();
}

void Cpu::executeXor(int rd, int rs1, int rs2) {
    const std::uint32_t result = Alu::bitwiseXor(registers.read(rs1), registers.read(rs2));
    registers.write(rd, result);
    advancePc();
}

void Cpu::executeAndi(int rd, int rs1, std::int32_t immediate) {
    const std::uint32_t result =
        Alu::bitwiseAnd(registers.read(rs1), static_cast<std::uint32_t>(immediate));
    registers.write(rd, result);
    advancePc();
}

void Cpu::executeOri(int rd, int rs1, std::int32_t immediate) {
    const std::uint32_t result =
        Alu::bitwiseOr(registers.read(rs1), static_cast<std::uint32_t>(immediate));
    registers.write(rd, result);
    advancePc();
}

void Cpu::executeXori(int rd, int rs1, std::int32_t immediate) {
    const std::uint32_t result =
        Alu::bitwiseXor(registers.read(rs1), static_cast<std::uint32_t>(immediate));
    registers.write(rd, result);
    advancePc();
}

void Cpu::executeLw(int rd, int rs1, std::int32_t immediate) {
    const std::uint32_t address = Alu::add(registers.read(rs1), static_cast<std::uint32_t>(immediate));
    registers.write(rd, memory.readWord(address));
    advancePc();
}

void Cpu::executeSw(int rs2, int rs1, std::int32_t immediate) {
    const std::uint32_t address = Alu::add(registers.read(rs1), static_cast<std::uint32_t>(immediate));
    memory.writeWord(address, registers.read(rs2));
    advancePc();
}

void Cpu::executeBeq(int rs1, int rs2, std::int32_t immediate) {
    if (registers.read(rs1) == registers.read(rs2)) {
        pc = static_cast<std::uint32_t>(static_cast<std::int32_t>(pc) + immediate);
        return;
    }

    advancePc();
}

void Cpu::executeBne(int rs1, int rs2, std::int32_t immediate) {
    if (registers.read(rs1) != registers.read(rs2)) {
        pc = static_cast<std::uint32_t>(static_cast<std::int32_t>(pc) + immediate);
        return;
    }

    advancePc();
}

void Cpu::executeJal(int rd, std::int32_t immediate) {
    const std::uint32_t returnAddress = pc + 4;
    registers.write(rd, returnAddress);
    pc = static_cast<std::uint32_t>(static_cast<std::int32_t>(pc) + immediate);
}

void Cpu::executeJalr(int rd, int rs1, std::int32_t immediate) {
    const std::uint32_t returnAddress = pc + 4;
    const std::uint32_t target =
        Alu::add(registers.read(rs1), static_cast<std::uint32_t>(immediate)) & ~1u;
    registers.write(rd, returnAddress);
    pc = target;
}

void Cpu::traceExecution(const Instruction& instruction) const {
    std::cout << "pc " << pc << ": " << instruction.toString() << '\n';

    switch (instruction.operation) {
        case Operation::ADD: {
            const std::uint32_t left = registers.read(instruction.rs1);
            const std::uint32_t right = registers.read(instruction.rs2);
            const std::uint32_t result = Alu::add(left, right);
            std::cout << "  x" << instruction.rd << " = x" << instruction.rs1
                      << "(" << left << ") + x" << instruction.rs2
                      << "(" << right << ") = " << result << '\n';
            break;
        }
        case Operation::SUB: {
            const std::uint32_t left = registers.read(instruction.rs1);
            const std::uint32_t right = registers.read(instruction.rs2);
            const std::uint32_t result = Alu::subtract(left, right);
            std::cout << "  x" << instruction.rd << " = x" << instruction.rs1
                      << "(" << left << ") - x" << instruction.rs2
                      << "(" << right << ") = " << result << '\n';
            break;
        }
        case Operation::ADDI: {
            const std::uint32_t left = registers.read(instruction.rs1);
            const std::uint32_t result =
                Alu::add(left, static_cast<std::uint32_t>(instruction.immediate));
            std::cout << "  x" << instruction.rd << " = x" << instruction.rs1
                      << "(" << left << ") + " << instruction.immediate
                      << " = " << result << '\n';
            break;
        }
        case Operation::AND: {
            const std::uint32_t left = registers.read(instruction.rs1);
            const std::uint32_t right = registers.read(instruction.rs2);
            const std::uint32_t result = Alu::bitwiseAnd(left, right);
            std::cout << "  x" << instruction.rd << " = x" << instruction.rs1
                      << "(" << left << ") & x" << instruction.rs2
                      << "(" << right << ") = " << result << '\n';
            break;
        }
        case Operation::OR: {
            const std::uint32_t left = registers.read(instruction.rs1);
            const std::uint32_t right = registers.read(instruction.rs2);
            const std::uint32_t result = Alu::bitwiseOr(left, right);
            std::cout << "  x" << instruction.rd << " = x" << instruction.rs1
                      << "(" << left << ") | x" << instruction.rs2
                      << "(" << right << ") = " << result << '\n';
            break;
        }
        case Operation::XOR: {
            const std::uint32_t left = registers.read(instruction.rs1);
            const std::uint32_t right = registers.read(instruction.rs2);
            const std::uint32_t result = Alu::bitwiseXor(left, right);
            std::cout << "  x" << instruction.rd << " = x" << instruction.rs1
                      << "(" << left << ") ^ x" << instruction.rs2
                      << "(" << right << ") = " << result << '\n';
            break;
        }
        case Operation::ANDI: {
            const std::uint32_t left = registers.read(instruction.rs1);
            const std::uint32_t result =
                Alu::bitwiseAnd(left, static_cast<std::uint32_t>(instruction.immediate));
            std::cout << "  x" << instruction.rd << " = x" << instruction.rs1
                      << "(" << left << ") & " << instruction.immediate
                      << " = " << result << '\n';
            break;
        }
        case Operation::ORI: {
            const std::uint32_t left = registers.read(instruction.rs1);
            const std::uint32_t result =
                Alu::bitwiseOr(left, static_cast<std::uint32_t>(instruction.immediate));
            std::cout << "  x" << instruction.rd << " = x" << instruction.rs1
                      << "(" << left << ") | " << instruction.immediate
                      << " = " << result << '\n';
            break;
        }
        case Operation::XORI: {
            const std::uint32_t left = registers.read(instruction.rs1);
            const std::uint32_t result =
                Alu::bitwiseXor(left, static_cast<std::uint32_t>(instruction.immediate));
            std::cout << "  x" << instruction.rd << " = x" << instruction.rs1
                      << "(" << left << ") ^ " << instruction.immediate
                      << " = " << result << '\n';
            break;
        }
        case Operation::LW: {
            const std::uint32_t base = registers.read(instruction.rs1);
            const std::uint32_t address =
                Alu::add(base, static_cast<std::uint32_t>(instruction.immediate));
            const std::uint32_t value = memory.readWord(address);
            std::cout << "  address = x" << instruction.rs1 << "(" << base
                      << ") + " << instruction.immediate << " = " << address << '\n';
            std::cout << "  x" << instruction.rd << " = memory[" << address
                      << "] = " << value << '\n';
            break;
        }
        case Operation::SW: {
            const std::uint32_t base = registers.read(instruction.rs1);
            const std::uint32_t address =
                Alu::add(base, static_cast<std::uint32_t>(instruction.immediate));
            const std::uint32_t value = registers.read(instruction.rs2);
            std::cout << "  address = x" << instruction.rs1 << "(" << base
                      << ") + " << instruction.immediate << " = " << address << '\n';
            std::cout << "  memory[" << address << "] = x" << instruction.rs2
                      << "(" << value << ")" << '\n';
            break;
        }
        case Operation::BEQ: {
            const std::uint32_t left = registers.read(instruction.rs1);
            const std::uint32_t right = registers.read(instruction.rs2);
            const bool taken = left == right;
            const std::uint32_t nextPc = taken
                ? static_cast<std::uint32_t>(static_cast<std::int32_t>(pc) + instruction.immediate)
                : pc + 4;
            std::cout << "  compare x" << instruction.rs1 << "(" << left
                      << ") == x" << instruction.rs2 << "(" << right
                      << "): " << (taken ? "true" : "false") << '\n';
            std::cout << "  pc -> " << nextPc << '\n';
            return;
        }
        case Operation::BNE: {
            const std::uint32_t left = registers.read(instruction.rs1);
            const std::uint32_t right = registers.read(instruction.rs2);
            const bool taken = left != right;
            const std::uint32_t nextPc = taken
                ? static_cast<std::uint32_t>(static_cast<std::int32_t>(pc) + instruction.immediate)
                : pc + 4;
            std::cout << "  compare x" << instruction.rs1 << "(" << left
                      << ") != x" << instruction.rs2 << "(" << right
                      << "): " << (taken ? "true" : "false") << '\n';
            std::cout << "  pc -> " << nextPc << '\n';
            return;
        }
        case Operation::JAL: {
            const std::uint32_t returnAddress = pc + 4;
            const std::uint32_t nextPc =
                static_cast<std::uint32_t>(static_cast<std::int32_t>(pc) + instruction.immediate);
            std::cout << "  x" << instruction.rd << " = return address "
                      << returnAddress << '\n';
            std::cout << "  pc -> " << nextPc << '\n';
            return;
        }
        case Operation::JALR: {
            const std::uint32_t base = registers.read(instruction.rs1);
            const std::uint32_t rawTarget =
                Alu::add(base, static_cast<std::uint32_t>(instruction.immediate));
            const std::uint32_t nextPc = rawTarget & ~1u;
            const std::uint32_t returnAddress = pc + 4;
            std::cout << "  x" << instruction.rd << " = return address "
                      << returnAddress << '\n';
            std::cout << "  target = (x" << instruction.rs1 << "(" << base
                      << ") + " << instruction.immediate << ") & ~1 = "
                      << nextPc << '\n';
            std::cout << "  pc -> " << nextPc << '\n';
            return;
        }
        default:
            throw std::invalid_argument("unsupported instruction operation");
    }

    std::cout << "  pc -> " << pc + 4 << '\n';
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
        case Operation::AND:
            executeAnd(instruction.rd, instruction.rs1, instruction.rs2);
            break;
        case Operation::OR:
            executeOr(instruction.rd, instruction.rs1, instruction.rs2);
            break;
        case Operation::XOR:
            executeXor(instruction.rd, instruction.rs1, instruction.rs2);
            break;
        case Operation::ANDI:
            executeAndi(instruction.rd, instruction.rs1, instruction.immediate);
            break;
        case Operation::ORI:
            executeOri(instruction.rd, instruction.rs1, instruction.immediate);
            break;
        case Operation::XORI:
            executeXori(instruction.rd, instruction.rs1, instruction.immediate);
            break;
        case Operation::LW:
            executeLw(instruction.rd, instruction.rs1, instruction.immediate);
            break;
        case Operation::SW:
            executeSw(instruction.rs2, instruction.rs1, instruction.immediate);
            break;
        case Operation::BEQ:
            executeBeq(instruction.rs1, instruction.rs2, instruction.immediate);
            break;
        case Operation::BNE:
            executeBne(instruction.rs1, instruction.rs2, instruction.immediate);
            break;
        case Operation::JAL:
            executeJal(instruction.rd, instruction.immediate);
            break;
        case Operation::JALR:
            executeJalr(instruction.rd, instruction.rs1, instruction.immediate);
            break;
        default:
            throw std::invalid_argument("unsupported instruction operation");
    }
}

void Cpu::run(const Program& program, bool trace) {
    while (program.hasInstructionAt(pc)) {
        const Instruction& instruction = program.getInstructionAt(pc);

        if (trace) {
            traceExecution(instruction);
        }

        execute(instruction);
    }
}

void Cpu::dumpState() const {
    std::cout << "pc: " << pc << '\n';
    registers.dump();
}
