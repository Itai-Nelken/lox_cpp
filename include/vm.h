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
    Obj *objects = nullptr;

    void freeObjects();
    InterpretResult run();
    void resetStack();
    void push(Value valie);
    Value pop();
    Value peek(int offset);
    void concatenate();
    void runtimeError(const char *format, ...);
public:
    VM(Obj *head);
    ~VM();
    Obj *getObjects() { return objects; }
    InterpretResult interpret(const char *source);
};
