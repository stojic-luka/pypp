#pragma once

#include <ostream>
#include <string>

enum class TokenType {
    Identifier = 0,
    Number = 1,
    Character = 2,
    Characters = 3,
    BinaryOperator = 4,
    BooleanOperator = 5,
    Equals = 6,

    Increment = 7,
    Decrement = 8,

    OpenParam = 9,      // (
    CloseParam = 10,    // )
    OpenBrace = 11,     // {
    CloseBrace = 12,    // }
    OpenBracket = 13,   // [
    CloseBracket = 14,  // ]

    None = 15,
    Int = 16,
    Float = 17,
    Double = 18,
    Bool = 19,
    Char = 20,
    String = 21,
    Object = 22,
    Func = 23,
    Void = 24,

    NOT = 25,
    AND = 26,
    NAND = 27,
    OR = 28,
    NOR = 29,
    XOR = 30,
    XNOR = 31,

    FuncDef = 32,

    If = 33,
    Elif = 34,
    Else = 35,
    For = 36,
    While = 37,

    Colon = 38,
    Dot = 39,
    Comma = 40,
    Arrow = 41,
    Comment = 42,
    LineEnd = 43,
    Return = 44,
    Eof = 45,
};

class Token {
private:
    TokenType type;
    std::string value;

public:
    bool isEmpty() const;

    Token();
    Token(TokenType type, std::string value);
    TokenType getType() const;
    std::string getValue() const;
};

std::ostream& operator<<(std::ostream& os, const TokenType type);
std::ostream& operator<<(std::ostream& os, const Token obj);