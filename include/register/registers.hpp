#ifndef REGISTER_REGISTERS_HPP
#define REGISTER_REGISTERS_HPP

#include <array>
#include <cstdint>

class Registers {
private:
    std::array<std::uint32_t, 32> regs{};

public:
    std::uint32_t read(int index) const;
    void write(int index, std::uint32_t value);
    void dump() const;
};

#endif
