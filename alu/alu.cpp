#include "alu/alu.hpp"

std::uint32_t Alu::add(std::uint32_t left, std::uint32_t right) {
    return left + right;
}

std::uint32_t Alu::subtract(std::uint32_t left, std::uint32_t right) {
    return left - right;
}

std::uint32_t Alu::bitwiseAnd(std::uint32_t left, std::uint32_t right) {
    return left & right;
}

std::uint32_t Alu::bitwiseOr(std::uint32_t left, std::uint32_t right) {
    return left | right;
}

std::uint32_t Alu::bitwiseXor(std::uint32_t left, std::uint32_t right) {
    return left ^ right;
}
