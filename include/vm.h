#pragma once

#include "common.h"
#include "value.h"
#include "chunk.h"

enum class InterpretResult {
    OK,
    COMPILE_ERROR,
    RUNTIME_ERROR,
    OTHER_ERROR
};

class VM {
private:
    Chunk *chunk;
    uint8_t *pc;
    Value stack[STACK_SIZE];
    Value *sp;

    InterpretResult run();
    void resetStack();
    void push(Value valie);
    Value pop();
public:
    VM();
    ~VM();
    InterpretResult interpret(const char *source);
};
