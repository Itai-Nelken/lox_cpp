#pragma once

#include <vector>
#include "common.h"
#include "value.h"
#include "chunk.h"

enum class InterpretResult {
    Ok,
    CompileError,
    RuntimeError
};

class VM {
public:
    VM() = default;
    ~VM() = default;

    InterpretResult interpret(Chunk &chunk);
private:
    InterpretResult run(void);
    void reset_stack();
    void push(Value value);
    Value pop();

    Chunk *chunk = nullptr;
    size_t pc = 0;
    std::vector<Value> stack;
    size_t sp = 0;
};
