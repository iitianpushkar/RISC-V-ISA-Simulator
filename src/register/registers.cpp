#include "register/registers.hpp"

#include <iostream>

std::uint32_t Registers::read(int index) const {
    if (index == 0) {
        return 0;
    }

    return regs[index];
}

void Registers::write(int index, std::uint32_t value) {
    if (index == 0) {
        return;
    }

    regs[index] = value;
}

void Registers::dump() const {
    for (int i = 0; i < 32; i++) {
        std::cout << "x" << i << ": " << read(i) << '\n';
    }
}
