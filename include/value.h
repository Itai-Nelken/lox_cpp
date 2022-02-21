#pragma once

#include "common.h"
#include "array.h"

enum class ValueType {
    BOOL,
    NIL,
    NUMBER
};

struct Value {
    ValueType type;
    union {
        bool boolean;
        double number;
    } as;
    bool operator==(Value &b);
};

#define IS_BOOL(value) ((value).type == ValueType::BOOL)
#define IS_NIL(value) ((value).type == ValueType::NIL)
#define IS_NUMBER(value) ((value).type == ValueType::NUMBER)

#define AS_BOOL(value)   ((value).as.boolean)
#define AS_NUMBER(value) ((value).as.number)

#define BOOL_VAL(value)   (Value{ValueType::BOOL, {.boolean = value}})
#define NIL_VAL           (Value{ValueType::NIL, {.number = 0}})
#define NUMBER_VAL(value) (Value{ValueType::NUMBER, {.number = value}})

typedef Array<Value> ValueArray;

bool valuesEqual(Value a, Value b);
void printValue(Value value);
