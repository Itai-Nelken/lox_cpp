#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "memory.h"
#include "vm.h"

static void repl() {
    // TODO: proper repl.
    // linenoise maybe?
    VM vm;
    char line[1024] {};
    for(;;) {
        printf(">>> ");
        if(!fgets(line, sizeof(line), stdin)) {
            printf("\n");
            break;
        }
        vm.interpret(line);
    }
}

static char *readFile(const char *path) {
#define ERROR(...) \
    do { \
        fprintf(stderr, __VA_ARGS__); \
        return nullptr; \
    } while(false)

    FILE *f = fopen(path, "rb");
    if(f == NULL) ERROR("ERROR: failed to open file \"%s\"!\n", path);
    size_t size = 0;
    char *buffer = nullptr;

    fseek(f, 0l, SEEK_END);
    size = ftell(f);
    rewind(f);

    buffer = memory::alloc<char>(size + 1);
    if(buffer == NULL) ERROR("ERROR: insufficient memory to read file \"%s\"!", path);
    size_t bytesRead = fread(buffer, sizeof(char), size, f);
    if(bytesRead < size) ERROR("ERROR: failed to read file \"%s\"!\n", path);
    buffer[bytesRead] = '\0';

    fclose(f);
    return buffer;

#undef ERROR
}

static InterpretResult runFile(const char *path) {
    VM vm;
    char *source = readFile(path);
    if(source == nullptr) return InterpretResult::OTHER_ERROR;
    InterpretResult result = vm.interpret(source);
    free(source);

    return result;
}

int main(int argc, const char **argv) {
    if(argc == 1) {
        repl();
    } else if(argc == 2) {
        runFile(argv[1]);
    } else {
        fprintf(stderr, "USAGE: %s [path]\n", argv[0]);
        return 1;
    }

    return 0;
}
