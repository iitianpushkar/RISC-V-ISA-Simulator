#ifndef CONTROL_CONTROL_UNIT_HPP
#define CONTROL_CONTROL_UNIT_HPP

#include "instruction/instruction.hpp"

struct ControlSignals {
    bool regWrite = false;
    bool memRead = false;
    bool memWrite = false;
    bool branch = false;
    bool jump = false;
    bool aluSrcImmediate = false;
    const char* aluOperation = "NONE";
    const char* writeBackSource = "NONE";
};

class ControlUnit {
public:
    static ControlSignals generate(const Operation& operation);
};

#endif
