#include "common.h"
#include "chunk.h"

int main(void) {
    Chunk chunk;
    chunk.write(OpCode::Return);
    chunk.disassemble("test chunk");
    return 0;
}
