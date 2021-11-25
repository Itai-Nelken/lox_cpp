#ifndef ARRAY_H
#define ARRAY_H

#include "common.h"
#include "memory.h"

template<class T>
class Array {
private:
    T *data = nullptr;
    size_t capacity = 0, current = 0;
    bool has_allocated = false;
public:
    Array() {}
    ~Array() {
        if(has_allocated) {
            FREE_ARRAY(T, data, capacity);
        }
    }
    
    int current_index() { return static_cast<int>(current); }

    T get(int index) { return data[index]; }

    void initialize() {
        if(has_allocated) {
            FREE_ARRAY(T, data, capacity);
            has_allocated = false;
        }
        capacity = 0;
        current = 0;
    }
    
    void write(T data) {
        if(capacity < current +1) {
            size_t old_capacity = capacity;
            capacity = GROW_CAPACITY(old_capacity);
            this->data = GROW_ARRAY(T, this->data, old_capacity, capacity);
            has_allocated = true;
        }
        this->data[current++] = data;
    }

    T operator[](int index) { return data[index]; }
};

#endif // ARRAY_H
