#include "memory/memory.hpp"

#include <stdexcept>

Memory::Memory(std::uint32_t sizeInBytes)
    : bytes(sizeInBytes, 0) {}

void Memory::validateWordAddress(std::uint32_t address) const {
    if (address % 4 != 0) {
        throw std::invalid_argument("word address must be 4-byte aligned");
    }

    if (address + 3 >= bytes.size()) {
        throw std::out_of_range("word address is outside memory");
    }
}

std::uint32_t Memory::readWord(std::uint32_t address) const {
    validateWordAddress(address);

    return static_cast<std::uint32_t>(bytes[address])
        | (static_cast<std::uint32_t>(bytes[address + 1]) << 8)
        | (static_cast<std::uint32_t>(bytes[address + 2]) << 16)
        | (static_cast<std::uint32_t>(bytes[address + 3]) << 24);
}

void Memory::writeWord(std::uint32_t address, std::uint32_t value) {
    validateWordAddress(address);

    bytes[address] = value & 0xff;
    bytes[address + 1] = (value >> 8) & 0xff;
    bytes[address + 2] = (value >> 16) & 0xff;
    bytes[address + 3] = (value >> 24) & 0xff;
}
