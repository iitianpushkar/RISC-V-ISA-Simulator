#include "cpu/cpu.hpp"
#include "decoder/decoder.hpp"
#include "program/program.hpp"

#include <iostream>
#include <vector>

int main() {
    Cpu cpu;

    cpu.getRegisters().write(1, 10);
    cpu.getRegisters().write(2, 20);
    cpu.getRegisters().write(7, 100);

    const std::vector<std::uint32_t> machineCode = {
        0x002081b3, // add x3, x1, x2
        0x40110233, // sub x4, x2, x1
        0x06408293, // addi x5, x1, 100
        0xffb08313, // addi x6, x1, -5
        0x0053a023, // sw x5, 0(x7)
        0x0003a403  // lw x8, 0(x7)
    };

    const Program program(Decoder::decodeProgram(machineCode));

    cpu.run(program, true);

    std::cout << '\n';
    cpu.dumpState();

    return 0;
}
