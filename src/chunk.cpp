#include <cstdio>
#include <string_view>
#include "debug.h"
#include "chunk.h"

void Chunk::write(uint8_t byte) {
    code.push_back(byte);
}

void Chunk::write(OpCode op) {
    write(static_cast<uint8_t>(op));
}

uint8_t Chunk::byte_at(size_t index) {
    return code.at(index);
}

void Chunk::disassemble(std::string_view name) {
    printf("== %s ==\n", name.data());
    for(int offset = 0; static_cast<size_t>(offset) < code.size();) {
        offset = Debug::disassembleInstruction(*this, offset);
    }
}
