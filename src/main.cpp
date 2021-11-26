#include "chunk.h"

int main(void) {
    Chunk chunk;
    
    int constantIndex = chunk.addConstant(1.2);
    chunk.write(OpCodes::CONSTANT, 123);
    chunk.write(constantIndex, 123);

    chunk.write(OpCodes::RETURN, 123);

    chunk.disassemble("test chunk");
    return 0;
}
