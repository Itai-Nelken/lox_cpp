#pragma once

#include "value.h"

enum class ObjType {
    STRING
};

struct Obj {
    ObjType type;
    Obj *next = nullptr;
};

struct ObjString : public Obj {
    int length;
    char *chars;
};

ObjString *takeString(char *chars, int length);
ObjString *copyString(const char *chars, int length);
void printObject(Value &value);
void freeObject(Obj *object);
Obj *getObjHead();

static inline bool isObjType(Value value, ObjType type) {
    return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

#define OBJ_TYPE(value) (AS_OBJ(value)->type);

#define IS_STRING(value) isObjType(value, ObjType::STRING)

#define AS_STRING(value) (static_cast<ObjString *>(AS_OBJ(value)))
#define AS_CSTRING(value) (static_cast<ObjString *>(AS_OBJ(value))->chars)
