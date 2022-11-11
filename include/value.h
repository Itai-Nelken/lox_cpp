#pragma once

#include "common.h"
#include "array.h"

// can't include object.h as it includes this file
struct Obj;

enum class ValueType {
    BOOL,
    NIL,
    NUMBER,
    OBJ
};


struct Value {
    ValueType type;
    union {
        bool boolean;
        double number;
        Obj *obj;
    } as;
    bool operator==(Value &b);
};

#define IS_BOOL(value)   ((value).type == ValueType::BOOL)
#define IS_NIL(value)    ((value).type == ValueType::NIL)
#define IS_NUMBER(value) ((value).type == ValueType::NUMBER)
#define IS_OBJ(value)    ((value).type == ValueType::OBJ)

#define AS_BOOL(value)   ((value).as.boolean)
#define AS_NUMBER(value) ((value).as.number)
#define AS_OBJ(value)    ((value).as.obj)

#define BOOL_VAL(value)   (Value{ValueType::BOOL, {.boolean = value}})
#define NIL_VAL           (Value{ValueType::NIL, {.number = 0}})
#define NUMBER_VAL(value) (Value{ValueType::NUMBER, {.number = value}})
#define OBJ_VAL(object)   (Value{ValueType::OBJ, {.obj = static_cast<Obj *>(object)}})

typedef Array<Value> ValueArray;

bool valuesEqual(Value a, Value b);
void printValue(Value value);
