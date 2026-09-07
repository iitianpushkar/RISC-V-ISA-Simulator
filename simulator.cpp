#include "cpu/cpu.hpp"
#include "decoder/decoder.hpp"
#include "loader/program_loader.hpp"
#include "program/program.hpp"

#include <cstdint>
#include <iostream>
#include <vector>

int main() {
    Cpu cpu;

    cpu.getRegisters().write(1, 10);
    cpu.getRegisters().write(2, 20);
    cpu.getRegisters().write(7, 100);

    const std::vector<std::uint32_t> machineCode =
        ProgramLoader::load("examples/basic_program.txt");
    const Program program(Decoder::decodeProgram(machineCode));

    cpu.run(program, true);

    std::cout << '\n';
    cpu.dumpState();

    return 0;
}
