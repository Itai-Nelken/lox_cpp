#include "common.h"
#include "../include/memory.h"
#include "string_builder.h"

StringBuilder::StringBuilder() {}

StringBuilder::StringBuilder(size_t initial_size) : size(initial_size) {
    buffer = memory::alloc<char>(size);
    allocated = true;
}

StringBuilder::~StringBuilder() {
    memory::free(buffer);
}

bool StringBuilder::isFull() {
    return current + 1 == size;
}

void StringBuilder::grow() {
    if(size == 0) {
        size = 1;
    }
    size *= StringBuilder::STEP;
    buffer = memory::realloc<char>(buffer, size);
}

void StringBuilder::appendChar(char c) {
    if(buffer == nullptr || isFull()) {
        grow();
    }
    buffer[current++] = c;
}

void StringBuilder::appendString(const char *s) {
    while(*s != '\0') {
        appendChar(*s++);
    }
}

void StringBuilder::copyTo(char *dest, size_t size) {
    // NULL == nullptr
    // so that is also handled
    if(dest == nullptr || size == 0) {
        return;
    }

    char *r = buffer;
    size_t i;
    for(i = 0; i < size && (size_t)(r - buffer) < current; ++i) {
        dest[i] = *r++;
    }
    dest[i] = '\0';
}

char *StringBuilder::string() {
    return buffer;
}

void StringBuilder::clear() {
    memory::free(buffer);
    buffer = nullptr;
    allocated = false;
    size = 0;
    current = 0;
}

StringBuilder &StringBuilder::operator<<(char c) {
    appendChar(c);
    return *this;
}

StringBuilder &StringBuilder::operator<<(const char *s) {
    appendString(s);
    return *this;
}
