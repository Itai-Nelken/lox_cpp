#include <cstdio>
#include "chunk.h"
#include "debug.h"

static int simpleInstruction(const char *name, int offset) {
    printf("%s\n", name);
    return offset + 1;
}

int disassembleInstruction(Chunk *chunk, int offset) {
    printf("%04d ", offset);

    OpCode instruction = chunk->get(offset);
    switch(instruction) {
        case OpCodes::RETURN:
            return simpleInstruction("RETURN", offset);
        default:
            printf("Unknown opcode %d!\n", instruction);
            return offset + 1;
    }
}
