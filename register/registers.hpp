#ifndef REGISTER_REGISTERS_HPP
#define REGISTER_REGISTERS_HPP

#include <array>
#include <cstdint>
#include <string_view>

class Registers {
private:
    static constexpr int REGISTER_COUNT = 32;

    std::array<std::uint32_t, 32> regs{};

    static bool isValidIndex(int index);

public:
    std::uint32_t read(int index) const;
    void write(int index, std::uint32_t value);
    std::string_view abiName(int index) const;
    void dump() const;
};

#endif
