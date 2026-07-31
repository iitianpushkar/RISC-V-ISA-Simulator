#include "cpu/cpu.hpp"
#include "instruction/instruction.hpp"
#include "program/program.hpp"

int main() {
    Cpu cpu;

    cpu.getRegisters().write(1, 10);
    cpu.getRegisters().write(2, 20);

    const Program program({
        Instruction::add(3, 1, 2),      // x3 = x1 + x2
        Instruction::sub(4, 2, 1),      // x4 = x2 - x1
        Instruction::addi(5, 1, 100)    // x5 = x1 + 100
    });

    cpu.run(program);
    cpu.dumpState();

    return 0;
}
