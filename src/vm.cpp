#include <cstdio>
#include "debug.h"
#include "chunk.h"
#include "value.h"
#include "vm.h"

InterpretResult VM::interpret(Chunk &chunk) {
    this->chunk = &chunk;
    pc = 0;
    return run();
}

void VM::reset_stack() {
    stack.clear();
    sp = 0;
}

void VM::push(Value value) {
    stack.push_back(value);
}

Value VM::pop() {
    Value top = stack.at(stack.size() - 1);
    stack.pop_back();
    return std::move(top);
}

InterpretResult VM::run(void) {
    auto read_byte = [this]() -> uint8_t { return chunk->byte_at(pc++); };
    auto read_constant = [this, read_byte]() -> Value { return chunk->constant_at(read_byte()); };
#define BINARY_OP(op) do { \
    double b = pop(); \
    double a = pop(); \
    push(a op b); \
 } while(0)

    for(;;) {
#ifdef DEBUG_TRACE_EXECUTION
        printf("        ");
        for(Value &v : stack) {
            printf("[ ");
            printValue(v);
            printf(" ]");
        }
        printf("\n");
        Debug::disassembleInstruction(*chunk, static_cast<int>(pc));
#endif
        OpCode instruction;
        switch(instruction = static_cast<OpCode>(read_byte())) {
            case OpCode::Constant: {
                Value constant = read_constant();
                push(constant);
                break;
            }
            case OpCode::Add: BINARY_OP(+); break;
            case OpCode::Subtract: BINARY_OP(-); break;
            case OpCode::Multiply: BINARY_OP(*); break;
            case OpCode::Divide: BINARY_OP(/); break;
            case OpCode::Negate: push(-pop()); break;
            case OpCode::Return:
                printValue(pop());
                printf("\n");
                return InterpretResult::Ok;
            default:
                return InterpretResult::RuntimeError;
        }
    }
#undef BINARY_OP
}
