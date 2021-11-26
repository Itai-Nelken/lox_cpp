#include <cstdio>
#include "common.h"
#include "compiler.h"
#include "scanner.h"

void compile(const char *source) {
    Scanner s(source);
    int line = 1;
    for(;;) {
        Token token = s.scanToken();
        if(token.line != line) {
            printf("%4d ", line);
            line = token.line;
        } else {
            printf("  | ");
        }
        printf("%2d '%.*s'\n", (int)token.type, token.length, token.start);
        if(token.type == TokenType::T_EOF) break;
    }
}
