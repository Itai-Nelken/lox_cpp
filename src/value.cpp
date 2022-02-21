#include <cstdio>
#include "value.h"

bool Value::operator==(Value &b) {
    if(type != b.type) {
        return false;
    }
    switch(type) {
        case ValueType::BOOL:
            return as.boolean == b.as.boolean;
        case ValueType::NUMBER:
            return as.number == b.as.number;
        case ValueType::NIL:
            break; // handled in last return in function (to silence compiler warning)
    }
    // ValueType::NIL
    // nil == nil
    return true;
}

bool valuesEqual(Value a, Value b) {
    if(a.type != b.type) {
        return false;
    }
    switch(a.type) {
        case ValueType::BOOL: return AS_BOOL(a) == AS_BOOL(b);
        case ValueType::NIL: return true; // nil == nil
        case ValueType::NUMBER: return AS_NUMBER(a) == AS_NUMBER(b);
        default: break;
    }
    // unreachable
    return false;
}

void printValue(Value value) {
    switch(value.type) {
        case ValueType::BOOL:
            printf("%s", AS_BOOL(value) ? "true" : "false");
            break;
        case ValueType::NIL:
            printf("nil");
            break;
        case ValueType::NUMBER:
            printf("%g", AS_NUMBER(value));
            break;
    }
}
