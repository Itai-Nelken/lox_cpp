#pragma once

#include "common.h"
#include "scanner.h"

enum class TokenType {
    // one character tokens
    LEFT_PAREN, RIGHT_PAREN,
    LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS,
    SEMICOLON, SLASH, STAR,

    // one or two character tokens
    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    // literals
    IDENTIFIER, STRING, NUMBER,

    // keywords
    AND, CLASS, ELSE, FALSE,
    FOR, FUN, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS,
    TRUE, VAR, WHILE,

    // other
    ERROR, T_EOF
};

struct Token {
    TokenType type;
    const char *start;
    int length;
    int line;
};

class Scanner {
private:
    const char *start = nullptr, *current = nullptr;
    int line = 0;

    bool isAtEnd();
    Token makeToken(TokenType type);
    // call ONLY with string literals or behaviour is undefined
    Token errorToken(const char *message);
    char advance();
    char peek();
    char peekNext();
    bool match(char expected);
    void skipWhiteSpace();
    bool isDigit(char c);
    bool isAlpha(char c);
    Token string();
    Token number();
    Token identifier();
    TokenType identifierType();
    TokenType checkKeyword(int start, const char *rest, TokenType type);
    TokenType checkNil();
public:
    Scanner(const char *source);
    Token scanToken();
};
