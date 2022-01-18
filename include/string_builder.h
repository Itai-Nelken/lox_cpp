#pragma once

#include <cstdlib> // for size_t

class StringBuilder {
private:
    char *buffer = nullptr;
    size_t size = 0, current = 0;
    bool allocated = false;
    static constexpr const int STEP = 8;

    bool isFull();
    void grow();
public:
    StringBuilder();
    StringBuilder(size_t initial_size);
    ~StringBuilder();
    StringBuilder &operator<<(char c);
    StringBuilder &operator<<(const char *s);
    void appendChar(char c);
    void appendString(const char *s);
    void copyTo(char *dest, size_t size);
    char *string();
    void clear();
};
