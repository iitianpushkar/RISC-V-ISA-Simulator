#include "cpu/cpu.hpp"
#include "decoder/decoder.hpp"
#include "loader/program_loader.hpp"
#include "program/program.hpp"

#include <cstdint>
#include <exception>
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <program-file>\n";
        return 1;
    }

    try {
        const std::vector<std::uint32_t> machineCode =
            ProgramLoader::load(argv[1]);
        const Program program(Decoder::decodeProgram(machineCode));

        Cpu cpu;

        cpu.getRegisters().write(1, 10);
        cpu.getRegisters().write(2, 20);
        cpu.getRegisters().write(7, 100);

        cpu.run(program, true);

        std::cout << '\n';
        cpu.dumpState();
    } catch (const std::exception& error) {
        std::cerr << "Simulator error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
