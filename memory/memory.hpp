#ifndef MEMORY_MEMORY_HPP
#define MEMORY_MEMORY_HPP

#include <cstdint>
#include <vector>

class Memory {
private:
    std::vector<std::uint8_t> bytes;

    void validateWordAddress(std::uint32_t address) const;

public:
    explicit Memory(std::uint32_t sizeInBytes = 1024);

    std::uint32_t readWord(std::uint32_t address) const;
    void writeWord(std::uint32_t address, std::uint32_t value);
};

#endif
