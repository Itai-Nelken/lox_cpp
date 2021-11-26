#include <cstdio>
#include "debug.h"
#include "value.h"
#include "chunk.h"

void Chunk::disassemble(const char *name) {
    printf("== %s ==\n", name);

    for(int offset = 0; offset < (int)current;) {
        offset = disassembleInstruction(this, offset);
    }
}

int Chunk::addConstant(Value value) {
    constants.append(value);
    return constants.get_current() - 1;
}

Value Chunk::getConstant(int index) {
    return constants[index];
}
