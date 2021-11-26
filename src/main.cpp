#include "chunk.h"

int main(void) {
    Chunk chunk;
    
    int constantIndex = chunk.addConstant(1.2);
    chunk.write(OpCodes::CONSTANT);
    chunk.write(constantIndex);

    chunk.write(OpCodes::RETURN);

    chunk.disassemble("test chunk");
    return 0;
}
