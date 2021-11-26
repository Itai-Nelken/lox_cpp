#include "memory.h"

template <class T>
Array<T>::~Array() {
    if(has_allocated) {
        FREE_ARRAY(T, data, capacity);
    }
}

template <class T>
void Array<T>::reinitialize() {
    if(has_allocated) {
        FREE_ARRAY(T, data, capacity);
        has_allocated = false;
        data = nullptr;
    }
    capacity = 0;
    current = 0;
}

template <class T>
void Array<T>::append(T data) {
    if(capacity < current + 1) {
        size_t old_capacity = capacity;
        capacity = GROW_CAPACITY(old_capacity);
        this->data = GROW_ARRAY(T, this->data, old_capacity, capacity);
        has_allocated = true;
    }
    this->data[current++] = data;
}

// TODO: check if index < capacity
template <class T>
T Array<T>::get(int index) {
    return data[index];
}

template <class T>
T Array<T>::operator[](int index) {
    return get(index);
}
