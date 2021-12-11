#include <cstdio>
#include "debug.h"
#include "value.h"
#include "chunk.h"

void Chunk::write(uint8_t byte, int line) {
    append(byte);
    lines.append(line);
}

void Chunk::disassemble(const char *name) {
    printf("== %s ==\n", name);

    for(int offset = 0; offset < (int)current;) {
        offset = disassembleInstruction(*this, offset);
    }
}

int Chunk::addConstant(Value value) {
    // if constant is already in constant pool, why add it again?
    // instead we return it's index.
    // if the constant doesn't exist, we simply add it and return the new index.
    if(!constants.exists(value)) {
        constants.append(value);
        return constants.get_current() - 1;
    }
    return constants.indexOf(value);
}

Value Chunk::getConstant(int index) {
    return constants[index];
}

int Chunk::getLine(int index) {
    return lines[index];
}

uint8_t *Chunk::getDataPtr() {
	return data;
}
