#include <iostream>

#include "array.h"

int main(void) {
    Array<int> a;
    a.append(12);
    std::cout << a.get(0) << std::endl;
    return 0;
}
