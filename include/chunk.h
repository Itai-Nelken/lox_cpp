#pragma once

#include <vector>
#include <string_view>
#include "common.h"

enum class OpCode : uint8_t {
    Return
};


class Chunk {
public:
    Chunk() = default;
    ~Chunk() = default;

    void write(uint8_t byte);
    void write(OpCode op);
    uint8_t byte_at(size_t index);
    void disassemble(std::string_view name);
private:
    std::vector<uint8_t> code;
};
