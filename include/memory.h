#pragma once

#include "common.h"

void *reallocate_internal(void *ptr, size_t old_size, size_t new_size);

template<typename T>
T *reallocate(T *ptr, size_t old_size, size_t new_size) {
    return static_cast<T *>(reallocate(static_cast<void *>(ptr), old_size, new_size));
}
