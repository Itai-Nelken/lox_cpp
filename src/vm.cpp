#include <cstdio>
#include <cstdarg>
#include "common.h"
#include "chunk.h"
#include "value.h"
#include "debug.h"
#include "compiler.h"
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

// TODO: check that -1-offset is inside the stack array.
Value VM::peek(int offset) {
    return sp[-1 - offset];
}

// nil & false are falsey
// true and any other value are truthy
static bool isFalsey(Value value) {
    return IS_NIL(value) || (IS_BOOL(value) && !AS_BOOL(value));
}

void VM::runtimeError(const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    vfprintf(stderr, format, ap);
    va_end(ap);
    fprintf(stderr, "\n");

    size_t instruction = pc - chunk->data - 1;
    int line = chunk->getLine(instruction);
    fprintf(stderr, "[line %d] in script.\n", line);
    resetStack();
}

InterpretResult VM::interpret(const char *source) {
    Chunk chunk;

    if(!compile(source, chunk)) {
        return InterpretResult::COMPILE_ERROR;
    }
    this->chunk = &chunk;
    //pc = this->chunk->getDataPtr();
    pc = this->chunk->data;

    InterpretResult result = run();

    return result;
}

InterpretResult VM::run() {
#define READ_BYTE() (*(this->pc)++)
#define READ_CONSTANT() (this->chunk->getConstant(READ_BYTE()))
#define BINARY_OP(value_type, op) \
    do { \
        if(!IS_NUMBER(peek(0)) || !IS_NUMBER(peek(1))) { \
            runtimeError("Operands must be numbers!"); \
            return InterpretResult::RUNTIME_ERROR; \
        } \
        double b = AS_NUMBER(pop()); \
        double a = AS_NUMBER(pop()); \
        push(value_type(a op b)); \
    } while(0)

#ifdef DEBUG_TRACE_EXECUTION
    printf("== executing ==\n");
#endif

    for(;;) {
#ifdef DEBUG_TRACE_EXECUTION
        printf("    ");
        for(Value *slot = stack; slot < sp; slot++) {
            printf("[");
            printValue(*slot);
            printf("] ");
        }
        printf("\n");
        disassembleInstruction(*(this->chunk), (int)(pc - chunk->data));
#endif
        uint8_t instruction;
        switch(instruction = READ_BYTE()) {
            case OpCodes::CONSTANT: {
                Value constant = READ_CONSTANT();
                push(constant);
                break;
            }
            case OpCodes::TRUE: push(BOOL_VAL(true)); break;
            case OpCodes::FALSE: push(BOOL_VAL(false)); break;
            case OpCodes::NIL: push(NIL_VAL); break;
            case OpCodes::EQUAL: {
                Value b = pop();
                Value a = pop();
                push(BOOL_VAL(valuesEqual(a, b)));
                break;
            }
            case OpCodes::GREATER: BINARY_OP(BOOL_VAL, >); break;
            case OpCodes::LESS: BINARY_OP(BOOL_VAL, <); break;
            case OpCodes::ADD: BINARY_OP(NUMBER_VAL, +); break;
            case OpCodes::SUBTRACT: BINARY_OP(NUMBER_VAL, -); break;
            case OpCodes::MULTIPLY: BINARY_OP(NUMBER_VAL, *); break;
            case OpCodes::DIVIDE: BINARY_OP(NUMBER_VAL, /); break;
            case OpCodes::NOT:
                push(BOOL_VAL(isFalsey(pop())));
                break;
            case OpCodes::NEGATE:
                if(!IS_NUMBER(peek(0))) {
                    runtimeError("Operand must be a number!");
                    return InterpretResult::RUNTIME_ERROR;
                }
                push(NUMBER_VAL(-AS_NUMBER(pop())));
                break;
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
