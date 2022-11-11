#pragma once

#include <cstdlib>

namespace memory {
    template <typename T>
    T *reallocate(T *ptr, size_t oldSize, size_t newSize) {
        (void)oldSize; // unused
        if(newSize == 0) {
            ::free(ptr);
            return nullptr;
        }
        T *result = static_cast<T*>(::realloc(ptr, newSize));
        if(result == NULL) exit(1);
        return result;
    }

    template<typename T>
    T *alloc(size_t size) {
        return static_cast<T*>(malloc(size));
    }

    template<typename T>
    T *realloc(T *ptr, size_t size) {
        return static_cast<T*>(::realloc(ptr, size));
    }

    inline void free(void *ptr) {
        ::free(ptr);
    }

} // namespace memory

#define ALLOCATE(type, size) memory::reallocate<type>(nullptr, 0, sizeof(type) * (size))
#define FREE(type, ptr) memory::reallocate<type>(ptr, sizeof(type), 0)

#define GROW_CAPACITY(capacity) ((capacity) < 8 ? 8 : (capacity) * 2)
#define GROW_ARRAY(type, ptr, oldCount, newCount) memory::reallocate<type>(ptr, sizeof(type) * (oldCount), sizeof(type) * (newCount))
#define FREE_ARRAY(type, ptr, oldCount) memory::reallocate<type>(ptr, sizeof(type) * oldCount, 0)
