# Lox++
Lox++ is a compiler and bytecode VM for the toy language Lox (described in the great book [Crafting interpreters](https://craftinginterpreters.com/)).<br>
Lox++ is an implementation of Clox as described in the book but written in C++ using only the C standard library.<br>
The only C++ features used are:
- classes
- enum classes
- custom namespaces
- templates (generics)
- references

Lox++ is currently at chapter 18: Types of Values

## Extra features
- `nil` or `null`.
- `fun` or `fn`.

## Optimizations
- Use same constants: when adding a constant if it already exists in the chunk's constant pool, use the exisiting one. this saves memory and makes the 255 constants per chunk limit slightly less annoying.

# TODO
- [ ] more than 256 constants per chunk (`OP_CONSTANT_LONG` or `OP_CONSTANT_16` (2 byte operand)).
- [ ] string interpolation (one of: `$"{var}"`, `"${var}"`, `f"{var}"`).
- [x] optimization: if constant is already in constant pool, use it instead of adding a new one.

