#include <cstdio>
#include "common.h"
#include "chunk.h"
#include "value.h"
#include "debug.h"
#include "vm.h"

VM::VM() {
    resetStack();
}

VM::~VM() {

}

void VM::resetStack() {
    sp = stack;
}

void VM::push(Value value) {
    *sp = value;
    sp++;
}

Value VM::pop() {
    sp--;
    return *sp;
}

InterpretResult VM::interpret(Chunk *chunk) {
    this->chunk = chunk;
    pc = this->chunk->getDataPtr();
    return run();
}

InterpretResult VM::run() {
#define READ_BYTE() (*(this->pc)++)
#define READ_CONSTANT() (this->chunk->getConstant(READ_BYTE()))
#define BINARY_OP(op) \
    do { \
        double b = pop(); \
        double a = pop(); \
        push(a op b); \
    } while(false)

    for(;;) {
#ifdef DEBUG_TRACE_EXECUTION
        printf("    ");
        for(Value *slot = stack; slot < sp; slot++) {
            printf("[");
            printValue(*slot);
            printf("] ");
        }
        printf("\n");
        disassembleInstruction(this->chunk, (int)(pc - chunk->getDataPtr()));
#endif
        uint8_t instruction;
        switch(instruction = READ_BYTE()) {
            case OpCodes::CONSTANT: {
                Value constant = READ_CONSTANT();
                push(constant);
                break;
            }
            case OpCodes::ADD: BINARY_OP(+); break;
            case OpCodes::SUBTRRACT: BINARY_OP(-); break;
            case OpCodes::MULTIPLY: BINARY_OP(*); break;
            case OpCodes::DIVIDE: BINARY_OP(/); break;
            case OpCodes::NEGATE: push(-pop()); break;
            case OpCodes::RETURN: {
                printValue(pop());
                printf("\n");
                return InterpretResult::OK;
            }
        }
    }

#undef READ_BYTE
#undef READ_CONSTANT
#undef BINARY_OP
}
