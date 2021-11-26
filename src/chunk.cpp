#include <cstdio>
#include "debug.h"
#include "chunk.h"

void Chunk::disassemble(const char *name) {
    printf("== %s ==\n", name);

    for(int offset = 0; offset < (int)current;) {
        offset = disassembleInstruction(this, offset);
    }
}
