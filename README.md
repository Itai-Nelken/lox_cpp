# Lox++
Lox++ is a compiler and bytecode VM for the toy language Lox (described in the great book [Crafting interpreters](https://craftinginterpreters.com/).
Lox++ is an implementation of Clox as described in the book but written in C++ using only the C standard library.<br>
The only C++ features used are:
- classes
- enum classes
- custom namespaces
- generics (templates)
- references

Lox++ is currently at chapter 17: Parsing expressions of the book.

## Features not in vanilla Lox
- `nil` or `null`.
- `fun` or `fn`.

# TODO
- [ ] more than 256 constants per chunk (`OP_CONSTANT_LONG` or `OP_CONSTANT_16` (2 byte operand)).
- [ ] string interpolation (one of: `$"{var}"`, `"${var}"`, `f"{var}"`).
