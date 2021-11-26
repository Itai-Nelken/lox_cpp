#include "chunk.h"

int main(void) {
    Chunk chunk;
    
    chunk.write(OpCodes::RETURN);
    
    chunk.disassemble("test chunk");
    return 0;
}
