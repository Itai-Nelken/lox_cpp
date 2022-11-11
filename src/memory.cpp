#include <cstdlib>
#include <stdexcept>
#include "common.h"
#include "memory.h"

void *reallocate_internal(void *ptr, size_t old_size, size_t new_size) {
    (void)old_size;
    if(new_size == 0) {
        free(ptr);
        return nullptr;
    }

    void *result = realloc(ptr, new_size);
    if(result == nullptr) {
        throw std::runtime_error("Failed to allocate memory!");
    }
    return result;
}
