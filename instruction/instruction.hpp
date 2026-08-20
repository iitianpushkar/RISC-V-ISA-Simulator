#ifndef INSTRUCTION_INSTRUCTION_HPP
#define INSTRUCTION_INSTRUCTION_HPP

#include <cstdint>
#include <string>

enum class Operation {
    ADD,
    SUB,
    ADDI,
    LW,
    SW,
    BEQ,
    BNE
};

struct Instruction {
    Operation operation;
    int rd;
    int rs1;
    int rs2;
    std::int32_t immediate;

    static Instruction add(int rd, int rs1, int rs2);
    static Instruction sub(int rd, int rs1, int rs2);
    static Instruction addi(int rd, int rs1, std::int32_t immediate);
    static Instruction lw(int rd, int rs1, std::int32_t immediate);
    static Instruction sw(int rs2, int rs1, std::int32_t immediate);
    static Instruction beq(int rs1, int rs2, std::int32_t immediate);
    static Instruction bne(int rs1, int rs2, std::int32_t immediate);

    std::string toString() const;
};

#endif
