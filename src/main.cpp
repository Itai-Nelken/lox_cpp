#include "chunk.h"

int main(void) {
    Chunk::chunk chunk;
    chunk.write(Chunk::OpCodes::RETURN);
    return 0;
}
