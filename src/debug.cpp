#include <cstdio>
#include "chunk.h"
#include "debug.h"

using Chunk::chunk;
using Chunk::OpCode;

static int simpleInstruction(const char *name, int offset) {
    printf("%s\n", name);
    return offset + 1;
}

int disassembleInstruction(chunk *chunk, int offset) {
    printf("%04d ", offset);

    OpCode instruction = chunk->get(offset);
    switch(instruction) {
        case OpCode::RETURN:
            return simpleInstruction("RETURN", offset);
        default:
            printf("Unknown opcode %d\n", (int)instruction);
            return offset + 1;
    }
}
