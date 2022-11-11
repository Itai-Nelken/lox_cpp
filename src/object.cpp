#include <cstdio>
#include <cstring>
#include "memory.h"
#include "value.h"
#include "object.h"
#include "vm.h"

static Obj *head = nullptr;

Obj *getObjHead() { return head; }

template<typename T>
static T *allocateObj(ObjType type) {
    auto *obj = static_cast<Obj *>(memory::reallocate<Obj>(nullptr, 0, sizeof(T)));
    obj->type = type;

    obj->next = head;
    head = obj;
    return static_cast<T *>(obj);
}

static ObjString *allocateString(char *chars, int length) {
    auto *string = allocateObj<ObjString>(ObjType::STRING);
    string->chars = chars;
    string->length = length;
    return string;
}

ObjString *takeString(char *chars, int length) {
    return allocateString(chars, length);
}

ObjString *copyString(const char *chars, int length) {
    char *heapChars = ALLOCATE(char, length + 1);
    memcpy(heapChars, chars, length);
    heapChars[length] = '\0';
    return allocateString(heapChars, length);
}

void printObject(Value &value) {
    switch(AS_OBJ(value)->type) {
        case ObjType::STRING:
            printf("%s", AS_CSTRING(value));
            break;
    }
}

void freeObject(Obj *object) {
    switch(object->type) {
        case ObjType::STRING: {
            auto *string = static_cast<ObjString *>(object);
            FREE_ARRAY(char, string->chars, string->length + 1);
            FREE(ObjString, string);
            break;
        }
    }
}
