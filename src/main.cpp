#include <cstdio>
#include "common.h"
#include "chunk.h"
#include "vm.h"

int main(void) {
    VM vm;
    Chunk chunk;

    int constant = chunk.add_constant(1.2);
    chunk.write(OpCode::Constant, 123);
    chunk.write(constant, 123);

    constant = chunk.add_constant(3.4);
    chunk.write(OpCode::Constant, 123);
    chunk.write(constant, 123);

    chunk.write(OpCode::Add, 123);

    constant = chunk.add_constant(5.6);
    chunk.write(OpCode::Constant, 123);
    chunk.write(constant, 123);

    chunk.write(OpCode::Divide, 123);
    chunk.write(OpCode::Negate, 123);

    chunk.write(OpCode::Return, 123);
    chunk.disassemble("test chunk");
    puts("== executing ==");
    vm.interpret(chunk);
    return 0;
}
