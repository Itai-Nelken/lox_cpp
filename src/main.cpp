#include "chunk.h"
#include "vm.h"

int main(void) {
    Chunk chunk;
    VM vm;

    int constantIndex = chunk.addConstant(1.2);
    chunk.write(OpCodes::CONSTANT, 123);
    chunk.write(constantIndex, 123);

    constantIndex = chunk.addConstant(1.4);
    chunk.write(OpCodes::CONSTANT, 123);
    chunk.write(constantIndex, 123);

    chunk.write(OpCodes::ADD, 123);

    constantIndex = chunk.addConstant(5.6);
    chunk.write(OpCodes::CONSTANT, 123);
    chunk.write(constantIndex, 123);

    chunk.write(OpCodes::DIVIDE, 123);
    chunk.write(OpCodes::NEGATE, 123);

    chunk.write(OpCodes::RETURN, 123);

    //chunk.disassemble("test chunk");
    vm.interpret(&chunk);
    return 0;
}
