#ifndef TOKENTYPES_H
#define TOKENTYPES_H

#include <ostream>
#include <string>

enum class TokenType {
    Identifier,
    Number,
    Character,
    Characters,
    BinaryOperator,
    BooleanOperator,
    Equals,

    Increment,
    Decrement,

    OpenParam,     // (
    CloseParam,    // )
    OpenBrace,     // {
    CloseBrace,    // }
    OpenBracket,   // [
    CloseBracket,  // ]

    None,
    Int,
    Float,
    Double,
    Bool,
    Char,
    String,
    Object,
    Func,
    Void,

    NOT,
    AND,
    NAND,
    OR,
    NOR,
    XOR,
    XNOR,

    FunctionDef,

    If,
    Elif,
    Else,
    For,
    While,

    Colon,
    Dot,
    Comma,
    Arrow,
    Comment,
    LineEnd,
    Return,
    Eof,
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

#endif  // TOKENTYPES_H
