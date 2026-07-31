#ifndef CPU_CPU_HPP
#define CPU_CPU_HPP

#include "instruction/instruction.hpp"
#include "program/program.hpp"
#include "register/registers.hpp"

#include <cstdint>

class Cpu {
private:
    Registers registers;
    std::uint32_t pc = 0;

public:
    Registers& getRegisters();
    const Registers& getRegisters() const;

    std::uint32_t getPc() const;
    void setPc(std::uint32_t value);
    void advancePc();

    void executeAdd(int rd, int rs1, int rs2);
    void executeSub(int rd, int rs1, int rs2);
    void executeAddi(int rd, int rs1, std::uint32_t immediate);
    void execute(const Instruction& instruction);
    void run(const Program& program);

    void dumpState() const;
};

#endif
