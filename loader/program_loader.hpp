#ifndef LOADER_PROGRAM_LOADER_HPP
#define LOADER_PROGRAM_LOADER_HPP

#include <cstdint>
#include <string>
#include <vector>

class ProgramLoader {
public:
    static std::vector<std::uint32_t> load(const std::string& filePath);
};

#endif
