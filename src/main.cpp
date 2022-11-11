#include "common.h"
#include "chunk.h"

int main(void) {
    Chunk chunk;

    int constant = chunk.add_constant(1.2);
    chunk.write(OpCode::Constant, 123);
    chunk.write(constant, 123);

    chunk.write(OpCode::Return, 123);
    chunk.disassemble("test chunk");
    return 0;
}
