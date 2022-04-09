//#include <cstdio>
//#include <cstdlib>
#include <cstring>
#include "common.h"
#include "scanner.h"

Scanner::Scanner(const char *source) {
    start = source;
    current = source;
    line = 1;
}

bool Scanner::isAtEnd() {
    return *current == '\0';
}

Token Scanner::makeToken(TokenType type) {
    Token token;
    token.type = type;
    token.start = start;
    token.length = (int)(current - start);
    token.line = line;

    return token;
}

Token Scanner::errorToken(const char *message) {
    Token token;
    token.type = TokenType::ERROR;
    token.start = message;
    token.length = (int)strlen(message);
    token.line = line;

    return token;
}

char Scanner::advance() {
    current++;
    return current[-1];
}

char Scanner::peek() {
    return *current;
}

char Scanner::peekNext() {
    if(isAtEnd()) return '\0';
    return current[1];
}

bool Scanner::match(char expected) {
    if(isAtEnd()) return false;
    if(*current != expected) return false;
    current++;
    return true;
}

void Scanner::skipWhiteSpace() {
    for(;;) {
        char c = peek();
        switch(c) {
            case ' ':
            case '\r':
            case '\t':
                advance();
                break;
            case '\n':
                line++;
                advance();
                break;
            case '/':
                if(peekNext() == '/') {
                    // a comment goes until end of line
                    while(peek() != '\n' && !isAtEnd()) advance();
                } else {
                    return;
                }
            default:
                return;
        }
    }
}

bool Scanner::isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool Scanner::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

Token Scanner::string() {
    while(peek() != '"' && !isAtEnd()) {
        if(peek() == '\n') line++;
        advance();
    }
    if(isAtEnd()) return errorToken("Unterminated string!");

    // the closing '"'
    advance();
    return makeToken(TokenType::STRING);
}

Token Scanner::number() {
    while(isDigit(peek())) advance();

    // look for fractional part.
    if(peek() == '.' && isDigit(peekNext())) {
        // consume the dot ('.').
        advance();
        while(isDigit(peek())) advance();
    }

    return makeToken(TokenType::NUMBER);
}

TokenType Scanner::checkNil() {
    // nil OR null
    if(checkKeyword(1, "il", TokenType::NIL) == TokenType::NIL || checkKeyword(1, "ull", TokenType::NIL) == TokenType::NIL) {
        return TokenType::NIL;
    }
    return TokenType::IDENTIFIER;
}

TokenType Scanner::checkKeyword(int start, const char *rest, TokenType type) {
    int length = strlen(rest);
    if(current - this->start == start + length && memcmp(this->start + start, rest, length) == 0) {
        return type;
    }
    return TokenType::IDENTIFIER;
}

TokenType Scanner::identifierType() {
    switch(start[0]) {
        case 'a': return checkKeyword(1, "nd", TokenType::AND);
        case 'c': return checkKeyword(1, "lass", TokenType::CLASS);
        case 'e': return checkKeyword(1, "lse", TokenType::ELSE);
        case 'f':
            if(current - start > 1) {
                switch(start[1]) {
                    case 'a': return checkKeyword(2, "lse", TokenType::FALSE);
                    case 'o': return checkKeyword(2, "r", TokenType::FOR);
                    // fun OR fn
                    case 'u': return checkKeyword(2, "n", TokenType::FUN);
                    case 'n': return TokenType::FUN;
                }
            }
            break;
        case 'i': return checkKeyword(1, "f", TokenType::IF);
        case 'n': return checkNil();
        case 'o': return checkKeyword(1, "r", TokenType::OR);
        case 'p': return checkKeyword(1, "rint", TokenType::PRINT);
        case 'r': return checkKeyword(1, "eturn", TokenType::RETURN);
        case 's': return checkKeyword(1, "uper", TokenType::SUPER);
        case 't':
            if(current - start > 1) {
                switch(start[1]) {
                    case 'h': return checkKeyword(2, "is", TokenType::THIS);
                    case 'r': return checkKeyword(2, "ue", TokenType::TRUE);
                }
            }
            break;
        case 'v': return checkKeyword(1, "ar", TokenType::VAR);
        case 'w': return checkKeyword(1, "hile", TokenType::WHILE);
        default:
            break;
    }
    return TokenType::IDENTIFIER;
}

Token Scanner::identifier() {
    while(isAlpha(peek())) advance();
    return makeToken(identifierType());
}

Token Scanner::scanToken() {
    skipWhiteSpace();
    start = current;
    if(isAtEnd()) return makeToken(TokenType::T_EOF);

    char c = advance();
    if(isAlpha(c)) return identifier();
    if(isDigit(c)) return number();
    switch(c) {
        case '(': return makeToken(TokenType::LEFT_PAREN);
        case ')': return makeToken(TokenType::RIGHT_PAREN);
        case '{': return makeToken(TokenType::LEFT_BRACE);
        case '}': return makeToken(TokenType::RIGHT_BRACE);
        case ';': return makeToken(TokenType::SEMICOLON);
        case ',': return makeToken(TokenType::COMMA);
        case '.': return makeToken(TokenType::DOT);
        case '-': return makeToken(TokenType::MINUS);
        case '+': return makeToken(TokenType::PLUS);
        case '/': return makeToken(TokenType::SLASH);
        case '*': return makeToken(TokenType::STAR);
        case '!': return makeToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
        case '=': return makeToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
        case '<': return makeToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
        case '>': return makeToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
        case '"':return string();
        default:
            break;
    }

    return errorToken("Unexpected character!");
}

