#ifndef CHUNK_H
#define CHUNK_H

#include <cstdio>
#include "common.h"
#include "debug.h"
#include "array.h"

namespace Chunk {
    
    enum class OpCode : uint8_t {
        RETURN
    };

    class chunk : public Array<OpCode> {
    public:
        void disassemble(const char *name) {
            printf("== %s ==\n", name);

            for(int offset = 0; offset < current_index();) {
                offset = disassembleInstruction(this, offset);
            }
        }
    };

} // namespace Chunk

#endif // CHUNK_H
