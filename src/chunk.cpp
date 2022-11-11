#include <cstdio>
#include <string_view>
#include "value.h"
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

int Chunk::add_constant(Value value) {
    constants.push_back(value);
    return constants.size() - 1;
}

Value Chunk::constant_at(size_t index) {
    return constants.at(index);
}

void Chunk::disassemble(std::string_view name) {
    printf("== %s ==\n", name.data());
    for(int offset = 0; static_cast<size_t>(offset) < code.size();) {
        offset = Debug::disassembleInstruction(*this, offset);
    }
}
