#pragma once

namespace TokenType {
    typedef enum TokenType {
        // Single character
        LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
        COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

        // One or two character tokens
        BANG, BANG_EQUAL, EQUAL, EQUAL_EQUAL,
        GREATER, GREATER_EQUAL, LESS, LESS_EQUAL,

        // Literals
        IDENTIFIER, STRING, NUMBER,

        // Keywords
        AND, OR, CLASS, SUPER, THIS, FUNC, T_NULL, TRUE, FALSE,
        IF, ELSE, FOR, WHILE, VAR, PRINT, RETURN,

        T_EOF
    } TokenType;
    const char *t2s(TokenType type);
}
