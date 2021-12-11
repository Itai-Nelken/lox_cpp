#pragma once

#include "common.h"

template <class T>
class Array {
protected:
    T *data = nullptr;
    bool has_allocated = false;
    size_t capacity = 0, current = 0;
public:
    ~Array();
    void reinitialize();
    void append(T data);
    T get(int index);
    // check if a value exists in the array
    bool exists(T value);
    // return the index of a value
    // return -1 if value doesn't exist
    int indexOf(T value);
    int get_current();

    T operator[](int index);
};

#include "array_impl.h"

