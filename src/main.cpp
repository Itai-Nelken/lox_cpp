#include "chunk.h"

#include <iostream>
int main(void) {
    Chunk::chunk chunk;
    chunk.write(Chunk::OpCode::RETURN);
    chunk.disassemble("test chunk");
    return 0;
}
