#pragma once

#include "common.h"
#include "array.h"

namespace Chunk {
    namespace OpCodes {
        enum {
            RETURN
        };
    } // namespace OpCodes
    typedef uint8_t OpCode;

    class chunk : public Array<uint8_t> {
    public:
        inline void write(uint8_t byte) { append(byte); }
    };
} // namespace Chunk

