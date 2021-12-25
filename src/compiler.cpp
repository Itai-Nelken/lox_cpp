#include <cstdio>
#include "common.h"
#include "scanner.h"
#include "chunk.h"
#include "compiler.h"

#ifdef DEBUG_PRINT_CODE
#include "debug.h"
#endif

struct Parser {
    Token current, previous;
    Scanner *scanner;
    bool hadError, panicMode;
};

namespace Precedences {
    // precedence levels from lowest to highest.
    // lowest at top, highest at bottom
    enum {
        NONE,
        ASSIGNMENT, // =
        OR, // or
        AND, // and
        EQUALITY, // == !=
        COMPARISON, // < > <= >=
        TERM, // + -
        FACTOR, // * /
        UNARY, // ! -
        CALL, // . ()
        PRIMARY 
    };
} // namespace Precedence
typedef uint8_t Precedence;

typedef void (*ParseFn)();

typedef struct parse_rule {
    ParseFn prefix, infix;
    Precedence precedence;
} ParseRule;

Parser p;
Chunk *compilingChunk;

static Chunk *currentChunk() {
    return compilingChunk;
}

static void errorAt(Token &token, const char *message) {
    if(p.panicMode) return;
    p.panicMode = true;
    fprintf(stderr, "[line %d] Error ", token.line);

    if(token.type == TokenType::T_EOF) {
        fprintf(stderr, "at end");
    } else if(token.type == TokenType::ERROR) {
        // nothing
    } else {
        fprintf(stderr, "at '%.*s'", token.length, token.start);
    }

    fprintf(stderr, ": %s\n", message);
    p.hadError = true;
}

static void errorAtCurrent(const char *message) {
    errorAt(p.current, message);
}

static void error(const char *message) {
    errorAt(p.previous, message);
}

static void advance() {
    p.previous = p.current;

    for(;;) {
        p.current = p.scanner->scanToken();
        if(p.current.type != TokenType::ERROR) break;

        errorAtCurrent(p.current.start);
    }
}

static void consume(TokenType type, const char *message) {
    if(p.current.type == type) {
        advance();
        return;
    }

    errorAtCurrent(message);
}

static void emitByte(uint8_t byte) {
    currentChunk()->write(byte, p.previous.line);
}

static void emitBytes(uint8_t byte1, uint8_t byte2) {
    emitByte(byte1);
    emitByte(byte2);
}

static void emitReturn() {
    emitByte(OpCodes::RETURN);
}

static uint8_t makeConstant(Value value) {
    int constantIndex = currentChunk()->addConstant(value);
    // TODO: make limit larger
    if(constantIndex > UINT8_MAX) {
        error("Too many constants in one chunk!");
        return 0;
    }
    return (uint8_t)constantIndex;
}

static void emitConstant(Value value) {
    emitBytes(OpCodes::CONSTANT, makeConstant(value));
}

static void endCompiler() {
    emitReturn();
#ifdef DEBUG_PRINT_CODE
    if(!p.hadError) {
        currentChunk()->disassemble("code");
    }
#endif
}

/*** forward declarations ***/
static void expression();
static ParseRule *getRule(TokenType type);
static void parsePrecedence(Precedence precedence);


// assumes the operator has already been consumed.
static void binary() {
    TokenType operatorType = p.previous.type;
    ParseRule *rule = getRule(operatorType);
    parsePrecedence((Precedence)(rule->precedence + 1));

    switch(operatorType) {
        case TokenType::PLUS: emitByte(OpCodes::ADD); break;
        case TokenType::MINUS: emitByte(OpCodes::SUBTRACT); break;
        case TokenType::STAR: emitByte(OpCodes::MULTIPLY); break;
        case TokenType::SLASH: emitByte(OpCodes::DIVIDE); break;
        default: return; // unreachable
    }
}

// assumes '(' (TokenType::LEFT_PAREN) has already been consumed
static void grouping() {
    expression();
    consume(TokenType::RIGHT_PAREN, "Expect ')' after expression!");
}

// assumes the number token has already been consumed
static void number() {
    double value = strtod(p.previous.start, NULL);
    emitConstant(value);
}

static void unary() {
    TokenType operatorType = p.previous.type;

    // Compile the operand
    parsePrecedence(Precedences::UNARY);

    // emit the operator instruction
    switch(operatorType) {
        case TokenType::BANG: emitByte(OpCodes::NEGATE); break;
        default: break; // unreachable
    }
}

// C++ doesn't allow the C99 designated initializers
// so I added them as a comment just so it's clear what I mean.
ParseRule rules[] = {
    /*[TokenType::LEFT_PAREN]    = */{grouping, NULL, Precedences::NONE},
    /*[TokenType::RIGHT_PAREN]   = */{NULL, NULL, Precedences::NONE},
    /*[TokenType::LEFT_BRACE]    = */{NULL, NULL, Precedences::NONE},
    /*[TokenType::RIGHT_BRACE]   = */{NULL, NULL, Precedences::NONE},
    /*[TokenType::COMMA]         = */{NULL, NULL, Precedences::NONE},
    /*[TokenType::DOT]           = */{NULL, NULL, Precedences::NONE},
    /*[TokenType::MINUS]         = */{unary, binary, Precedences::TERM},
    /*[TokenType::PLUS]          = */{NULL, binary, Precedences::TERM},
    /*[TokenType::SEMICOLON]     = */{NULL, NULL, Precedences::NONE},
    /*[TokenType::SLASH]         = */{NULL, binary, Precedences::FACTOR},
    /*[TokenType::STAR]          = */{NULL, binary, Precedences::FACTOR},
    /*[TokenType::BANG]          = */{NULL, NULL, Precedences::NONE},
    /*[TokenType::BANG_EQUAL]    = */{NULL, NULL, Precedences::NONE},
    /*[TokenType::EQUAL]         = */{NULL, NULL, Precedences::NONE},
    /*[TokenType::EQUAL_EQUAL]   = */{NULL, NULL, Precedences::NONE},
    /*[TokenType::GREATER]       = */{NULL, NULL, Precedences::NONE},
    /*[TokenType::GREATER_EQUAL] = */{NULL, NULL, Precedences::NONE},
    /*[TokenType::LESS]          = */{NULL, NULL, Precedences::NONE},
    /*[TokenType::LESS_EQUAL]    = */{NULL, NULL, Precedences::NONE},
    /*[TokenType::IDENTIFIER]    = */{NULL, NULL, Precedences::NONE},
    /*[TokenType::STRING]        = */{NULL, NULL, Precedences::NONE},
    /*[TokenType::NUMBER]        = */{number, NULL, Precedences::NONE},
    /*[TokenType::AND]           = */{NULL, NULL, Precedences::NONE},
    /*[TokenType::CLASS]         = */{NULL, NULL, Precedences::NONE},
    /*[TokenType::ELSE]          = */{NULL, NULL, Precedences::NONE},
    /*[TokenType::FALSE]         = */{NULL, NULL, Precedences::NONE},
    /*[TokenType::FOR]           = */{NULL, NULL, Precedences::NONE},
    /*[TokenType::FUN]           = */{NULL, NULL, Precedences::NONE},
    /*[TokenType::IF]            = */{NULL, NULL, Precedences::NONE},
    /*[TokenType::NIL]           = */{NULL, NULL, Precedences::NONE},
    /*[TokenType::OR]            = */{NULL, NULL, Precedences::NONE},
    /*[TokenType::PRINT]         = */{NULL, NULL, Precedences::NONE},
    /*[TokenType::RETURN]        = */{NULL, NULL, Precedences::NONE},
    /*[TokenType::SUPER]         = */{NULL, NULL, Precedences::NONE},
    /*[TokenType::THIS]          = */{NULL, NULL, Precedences::NONE},
    /*[TokenType::TRUE]          = */{NULL, NULL, Precedences::NONE},
    /*[TokenType::VAR]           = */{NULL, NULL, Precedences::NONE},
    /*[TokenType::WHILE]         = */{NULL, NULL, Precedences::NONE},
    /*[TokenType::ERROR]         = */{NULL, NULL, Precedences::NONE},
    /*[TokenType::T_EOF]         = */{NULL, NULL, Precedences::NONE}
};

static void parsePrecedence(Precedence precedence) {
    advance();
    ParseFn prefixRule = getRule(p.previous.type)->prefix;
    if(prefixRule == NULL) {
        error("Expect expression!");
        return;
    }
    prefixRule();

    while(precedence <= getRule(p.current.type)->precedence) {
        advance();
        ParseFn infixRule = getRule(p.previous.type)->infix;
        infixRule();
    }

}

static ParseRule *getRule(TokenType type) {
    // cast is a workaround for c++ being annoying.
    return &rules[(int)type];
}

static void expression() {
    // parse the lowest precedence, this includes the higher ones as well.
    parsePrecedence(Precedences::ASSIGNMENT);
}

bool compile(const char *source, Chunk &chunk) {
    Scanner s(source);
    compilingChunk = &chunk;
    p.scanner = &s;
    p.hadError = false;
    p.panicMode = false;

    advance();
    expression();
    consume(TokenType::T_EOF, "Expect end of expression!");
    endCompiler();

    return !p.hadError;
}

/*
 * int line = 1;
 * for(;;) {
 *     Token token = s.scanToken();
 *     if(token.line != line) {
 *         printf("%4d ", line);
 *         line = token.line;
 *     } else {
 *         printf("  | ");
 *     }
 *     printf("%2d '%.*s'\n", (int)token.type, token.length, token.start);
 *     if(token.type == TokenType::T_EOF) break;
 * }
 */

