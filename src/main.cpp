#include "common.h"
#include "chunk.h"

int main(void) {
    Chunk chunk;

    int constant = chunk.add_constant(1.2);
    chunk.write(OpCode::Constant);
    chunk.write(constant);

    chunk.write(OpCode::Return);
    chunk.disassemble("test chunk");
    return 0;
}
