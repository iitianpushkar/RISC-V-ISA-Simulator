#ifndef CPU_CPU_HPP
#define CPU_CPU_HPP

#include "instruction/instruction.hpp"
#include "memory/memory.hpp"
#include "program/program.hpp"
#include "register/registers.hpp"

#include <cstdint>
#include <string>

struct ExecutionResult {
    std::uint32_t oldPc = 0;
    std::uint32_t nextPc = 0;

    bool regWritten = false;
    int writtenRegister = 0;
    std::uint32_t writtenValue = 0;

    bool memoryRead = false;
    bool memoryWritten = false;
    std::uint32_t memoryAddress = 0;
    std::uint32_t memoryValue = 0;

    bool branchTaken = false;

    std::string executeStage;
    std::string memoryStage = "no memory access";
    std::string writeBackStage = "no register write";
};

class Cpu {
private:
    Registers registers;
    Memory memory;
    std::uint32_t pc = 0;

    void traceExecution(const Instruction& instruction,
                        const ExecutionResult& result) const;

public:
    Registers& getRegisters();
    const Registers& getRegisters() const;
    Memory& getMemory();
    const Memory& getMemory() const;

    std::uint32_t getPc() const;
    void setPc(std::uint32_t value);
    void advancePc();

    ExecutionResult execute(const Instruction& instruction);
    void run(const Program& program, bool trace = false);

    void dumpState() const;
};

#endif
