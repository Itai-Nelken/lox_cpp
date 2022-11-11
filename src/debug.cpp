#include <cstdio>
#include <string_view>
#include "chunk.h"
#include "value.h"
#include "debug.h"

namespace {

int simpleInstruction(std::string_view name, int offset) {
    printf("%s\n", name.data());
    return offset + 1;
}

int constantInstruction(std::string_view name, Chunk &chunk, int offset) {
    uint8_t constant = chunk.byte_at(offset + 1);
    printf("%-16s %4d '", name.data(), constant);
    printValue(chunk.constant_at(constant));
    printf("'\n");
    return offset + 2;
}

}

namespace Debug {

int disassembleInstruction(Chunk &chunk, int offset) {
    printf("%04d ", offset);

    uint8_t instruction = chunk.byte_at(offset);
    switch(static_cast<OpCode>(instruction)) {
        case OpCode::Constant:
            return constantInstruction("Constant", chunk, offset);
        case OpCode::Return:
            return simpleInstruction("Return", offset);
        default:
            printf("Unknown opcode %u\n", instruction);
            return offset + 1;
    }
}

} // namespace Debug

