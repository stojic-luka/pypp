#include "lexer.h"

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "tokenTypes.h"

std::unordered_map<std::string, TokenType> KEYWORDS = {
    {"int", TokenType::Int},
    {"float", TokenType::Float},
    {"double", TokenType::Double},
    {"char", TokenType::Char},
    {"bool", TokenType::Bool},
    {"string", TokenType::String},
    {"object", TokenType::Object},
    {"func", TokenType::Func},
    {"void", TokenType::Void},

    {"NOT", TokenType::NOT},
    {"AND", TokenType::AND},
    {"NAND", TokenType::NAND},
    {"OR", TokenType::OR},
    {"NOR", TokenType::NOR},
    {"XOR", TokenType::XOR},
    {"XNOR", TokenType::XNOR},

    {"if", TokenType::If},
    {"elif", TokenType::Elif},
    {"else", TokenType::Else},
    {"for", TokenType::For},
    {"while", TokenType::While},

    {"return", TokenType::Return},
    {"def", TokenType::FunctionDef},
};

std::vector<Token> tokenize(std::string sourceCode) {
    std::string str = "";
    std::vector<Token> tokens;
    const char *src = sourceCode.c_str();

    while (*src != '\0') {
        if (*src == ' ' || *src == '\n' || *src == '\r' || *src == '\t') {
            *src++;
            continue;
        }

        switch (*src) {
            case '(':
                tokens.push_back(Token(TokenType::OpenParam, "("));
                src++;
                break;
            case ')':
                tokens.push_back(Token(TokenType::CloseParam, ")"));
                src++;
                break;
            case '{':
                tokens.push_back(Token(TokenType::OpenBrace, "{"));
                src++;
                break;
            case '}':
                tokens.push_back(Token(TokenType::CloseBrace, "}"));
                src++;
                break;
            case '[':
                tokens.push_back(Token(TokenType::OpenBracket, "["));
                src++;
                break;
            case ']':
                tokens.push_back(Token(TokenType::CloseBracket, "]"));
                src++;
                break;
            case '*':
            case '/':
            case '%':
            case '^':
                tokens.push_back(Token(TokenType::BinaryOperator, std::string(1, *src)));
                src++;
                break;
            case '+':
                src++;
                if (*src == '+') {
                    tokens.push_back(Token(TokenType::Increment, "++"));
                    src++;
                } else
                    tokens.push_back(Token(TokenType::BinaryOperator, "+"));
                break;
            case '-':
                src++;
                if (*src == '>') {
                    tokens.push_back(Token(TokenType::Arrow, "->"));
                    src++;
                } else if (*src == '-') {
                    tokens.push_back(Token(TokenType::Decrement, "--"));
                    src++;
                } else
                    tokens.push_back(Token(TokenType::BinaryOperator, "-"));
                break;
            case '=':
                src++;
                if (*src == '=') {
                    tokens.push_back(Token(TokenType::BooleanOperator, "=="));
                    src++;
                } else
                    tokens.push_back(Token(TokenType::Equals, "="));
                break;
            case '!':
            case '<':
            case '>':
                str = std::string(1, *src);
                src++;
                if (*src == '=') {
                    tokens.push_back(Token(TokenType::BooleanOperator, str + "="));
                    src++;
                } else
                    tokens.push_back(Token(TokenType::BooleanOperator, str));
                str = "";
                break;
            case ';':
                tokens.push_back(Token(TokenType::LineEnd, ";"));
                src++;
                break;
            case ':':
                tokens.push_back(Token(TokenType::Colon, ":"));
                src++;
                break;
            case ',':
                tokens.push_back(Token(TokenType::Comma, ","));
                src++;
                break;
            case '.':
                tokens.push_back(Token(TokenType::Dot, "."));
                src++;
                break;
            case '#':
                while (*src != '\n')
                    src++;
                break;
            case '\'':
                src++;
                str.push_back(*src);
                src++;
                if (*src != '\'')
                    throw std::runtime_error("Invalid char declaration");
                src++;
                tokens.push_back(Token(TokenType::Character, str));
                str = "";
                break;
            case '"':
                src++;
                while (*src != '\0' && *src != '"') {
                    str.push_back(*src);
                    src++;
                }
                if (*src == '"')
                    src++;
                else
                    throw std::runtime_error("Invalid string declaration");
                tokens.push_back(Token(TokenType::Characters, str));
                str = "";
                break;
            default:
                if (std::isdigit(static_cast<int>(*src))) {
                    std::string num = "";
                    bool underscorePassed = false;
                    while (*src != '\0' && (std::isdigit(static_cast<int>(*src)) || *src == '.' || *src == '_')) {
                        if (*src == '_') {
                            if (underscorePassed)
                                throw std::runtime_error("Syntax error");
                            src++;
                            underscorePassed = true;
                            continue;
                        }
                        underscorePassed = false;
                        num.push_back(*src);
                        src++;
                    }
                    tokens.push_back(Token(TokenType::Number, num));
                } else if (std::isalpha(static_cast<char>(*src)) || *src == '_') {
                    std::string ident = "";
                    while (*src != '\0' && (std::isalpha(static_cast<int>(*src)) || std::isdigit(static_cast<int>(*src))) || *src == '_') {
                        ident.push_back(*src);
                        src++;
                    }
                    if (KEYWORDS.count(ident))
                        tokens.push_back(Token(KEYWORDS[ident], ident));
                    else
                        tokens.push_back(Token(TokenType::Identifier, ident));
                } else {
                    throw std::runtime_error("Character not recognized!");
                }
                break;
        }
    }
    tokens.push_back(Token(TokenType::Eof, "Eof"));

    return tokens;
}