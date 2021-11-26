#include <cstdio>
#include "value.h"
#include "chunk.h"
#include "debug.h"

static int simpleInstruction(const char *name, int offset) {
    printf("%s\n", name);
    return offset + 1;
}

static int constantInstruction(const char *name, Chunk *chunk, int offset) {
    uint8_t constantIndex = chunk->get(offset + 1);
    printf("%-16s %4d '", name, constantIndex);
    printValue(chunk->getConstant(constantIndex));
    printf("'\n");

    return offset + 2;
}

int disassembleInstruction(Chunk *chunk, int offset) {
    printf("%04d ", offset);
    if(offset > 0 && chunk->getLine(offset) == chunk->getLine(offset - 1)) {
        printf("  | ");
    } else {
        printf("%4d ", chunk->getLine(offset));
    }

    uint8_t instruction = chunk->get(offset);
    switch(instruction) {
        case OpCodes::CONSTANT:
            return constantInstruction("CONSTANT", chunk, offset);
        case OpCodes::ADD:
            return simpleInstruction("ADD", offset);
        case OpCodes::SUBTRRACT:
            return simpleInstruction("SUBTRACT", offset);
        case OpCodes::MULTIPLY:
            return simpleInstruction("MULTIPLY", offset);
        case OpCodes::DIVIDE:
            return simpleInstruction("DIVIDE", offset);
        case OpCodes::NEGATE:
            return simpleInstruction("NEGATE", offset);
        case OpCodes::RETURN:
            return simpleInstruction("RETURN", offset);
        default:
            printf("Unknown opcode %d!\n", instruction);
            return offset + 1;
    }
}
