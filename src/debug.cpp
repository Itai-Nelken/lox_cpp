#include <cstdio>
#include <string_view>
#include "chunk.h"
#include "debug.h"

namespace {

int simpleInstruction(std::string_view name, int offset) {
    printf("%s\n", name.data());
    return offset + 1;
}

}

namespace Debug {

int disassembleInstruction(Chunk &chunk, int offset) {
    printf("%04d ", offset);

    uint8_t instruction = chunk.byte_at(offset);
    switch(static_cast<OpCode>(instruction)) {
        case OpCode::Return:
            return simpleInstruction("Return", offset);
        default:
            printf("Unknown opcode %u\n", instruction);
            return offset + 1;
    }
}

} // namespace Debug

