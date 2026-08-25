#ifndef INSTRUCTION_INSTRUCTION_HPP
#define INSTRUCTION_INSTRUCTION_HPP

#include <cstdint>
#include <string>

enum class Operation {
    ADD,
    SUB,
    ADDI,
    AND,
    OR,
    XOR,
    ANDI,
    ORI,
    XORI,
    LW,
    SW,
    BEQ,
    BNE,
    JAL,
    JALR
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
    static Instruction bitwiseAnd(int rd, int rs1, int rs2);
    static Instruction bitwiseOr(int rd, int rs1, int rs2);
    static Instruction bitwiseXor(int rd, int rs1, int rs2);
    static Instruction andi(int rd, int rs1, std::int32_t immediate);
    static Instruction ori(int rd, int rs1, std::int32_t immediate);
    static Instruction xori(int rd, int rs1, std::int32_t immediate);
    static Instruction lw(int rd, int rs1, std::int32_t immediate);
    static Instruction sw(int rs2, int rs1, std::int32_t immediate);
    static Instruction beq(int rs1, int rs2, std::int32_t immediate);
    static Instruction bne(int rs1, int rs2, std::int32_t immediate);
    static Instruction jal(int rd, std::int32_t immediate);
    static Instruction jalr(int rd, int rs1, std::int32_t immediate);

    std::string toString() const;
};

#endif
