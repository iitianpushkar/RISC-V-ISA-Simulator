#ifndef ALU_ALU_HPP
#define ALU_ALU_HPP

#include <cstdint>

class Alu {
public:
    static std::uint32_t add(std::uint32_t left, std::uint32_t right);
    static std::uint32_t subtract(std::uint32_t left, std::uint32_t right);
};

#endif
