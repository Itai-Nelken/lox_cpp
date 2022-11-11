#pragma once

#include "chunk.h"
#include "debug.h"

namespace Debug {

int disassembleInstruction(Chunk &chunk, int offset);

} // namespace Debug

