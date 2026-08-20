#ifndef CPU_CPU_HPP
#define CPU_CPU_HPP

#include "instruction/instruction.hpp"
#include "memory/memory.hpp"
#include "program/program.hpp"
#include "register/registers.hpp"

#include <cstdint>

class Cpu {
private:
    Registers registers;
    Memory memory;
    std::uint32_t pc = 0;

    void traceExecution(const Instruction& instruction) const;

public:
    Registers& getRegisters();
    const Registers& getRegisters() const;
    Memory& getMemory();
    const Memory& getMemory() const;

    std::uint32_t getPc() const;
    void setPc(std::uint32_t value);
    void advancePc();

    void executeAdd(int rd, int rs1, int rs2);
    void executeSub(int rd, int rs1, int rs2);
    void executeAddi(int rd, int rs1, std::int32_t immediate);
    void executeLw(int rd, int rs1, std::int32_t immediate);
    void executeSw(int rs2, int rs1, std::int32_t immediate);
    void executeBeq(int rs1, int rs2, std::int32_t immediate);
    void executeBne(int rs1, int rs2, std::int32_t immediate);
    void executeJal(int rd, std::int32_t immediate);
    void executeJalr(int rd, int rs1, std::int32_t immediate);
    void execute(const Instruction& instruction);
    void run(const Program& program, bool trace = false);

    void dumpState() const;
};

#endif
