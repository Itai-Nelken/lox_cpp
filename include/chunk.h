#pragma once

#include "common.h"
#include "array.h"

namespace OpCodes {
    enum {
        RETURN
    };
} // namespace OpCodes
typedef uint8_t OpCode;

class Chunk : public Array<uint8_t> {
public:
    inline void write(uint8_t byte) { append(byte); }
    void disassemble(const char *name);
};

