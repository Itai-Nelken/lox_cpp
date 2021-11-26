#pragma once

#include "common.h"
#include "array.h"
#include "value.h"

namespace OpCodes {
    enum {
        CONSTANT,
        RETURN
    };
} // namespace OpCodes
typedef uint8_t OpCode;

class Chunk : public Array<uint8_t> {
private:
    ValueArray constants;
public:
    inline void write(uint8_t byte) { append(byte); }
    void disassemble(const char *name);
    int addConstant(Value value);
    Value getConstant(int index);
};

