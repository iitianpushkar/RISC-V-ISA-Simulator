#include "register/registers.hpp"

#include <iomanip>
#include <iostream>
#include <stdexcept>

bool Registers::isValidIndex(int index) {
    return index >= 0 && index < REGISTER_COUNT;
}

std::uint32_t Registers::read(int index) const {
    if (!isValidIndex(index)) {
        throw std::out_of_range("register index must be between 0 and 31");
    }

    if (index == 0) {
        return 0;
    }

    return regs[index];
}

void Registers::write(int index, std::uint32_t value) {
    if (!isValidIndex(index)) {
        throw std::out_of_range("register index must be between 0 and 31");
    }

    if (index == 0) {
        return;
    }

    regs[index] = value;
}

std::string_view Registers::abiName(int index) const {
    if (!isValidIndex(index)) {
        throw std::out_of_range("register index must be between 0 and 31");
    }

    static constexpr std::array<std::string_view, REGISTER_COUNT> names = {
        "zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
        "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
        "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
        "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
    };

    return names[index];
}

void Registers::dump() const {
    for (int i = 0; i < REGISTER_COUNT; i++) {
        std::cout << 'x' << std::left << std::setw(2) << i
                  << " (" << std::setw(4) << abiName(i) << "): "
                  << read(i) << '\n';
    }
}
