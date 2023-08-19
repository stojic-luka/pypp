#include "tokentypes.h"

#include <ostream>
#include <string>

Token::Token() {}
Token::Token(TokenType type, std::string value) : type(type), value(value) {}

TokenType Token::getType() const { return type; }
std::string Token::getValue() const { return value; }

bool Token::isEmpty() const { return value == ""; }

std::ostream& operator<<(std::ostream& os, const TokenType type) {
    switch (type) {
        case TokenType::Identifier:
            return os << "TokenType::Identifier";
        case TokenType::Number:
            return os << "TokenType::Number";
        case TokenType::Character:
            return os << "TokenType::Character";
        case TokenType::Characters:
            return os << "TokenType::Characters";
        case TokenType::BinaryOperator:
            return os << "TokenType::BinaryOperator";
        case TokenType::BooleanOperator:
            return os << "TokenType::BooleanOperator";
        case TokenType::Equals:
            return os << "TokenType::Equals";

        case TokenType::OpenParam:
            return os << "TokenType::OpenParam";
        case TokenType::CloseParam:
            return os << "TokenType::CloseParam";
        case TokenType::OpenBrace:
            return os << "TokenType::OpenBrace";
        case TokenType::CloseBrace:
            return os << "TokenType::CloseBrace";
        case TokenType::OpenBracket:
            return os << "TokenType::OpenBracket";
        case TokenType::CloseBracket:
            return os << "TokenType::CloseBracket";

        case TokenType::Int:
            return os << "TokenType::Int";
        case TokenType::Float:
            return os << "TokenType::Float";
        case TokenType::Double:
            return os << "TokenType::Double";
        case TokenType::Char:
            return os << "TokenType::Char";
        case TokenType::Bool:
            return os << "TokenType::Bool";
        case TokenType::String:
            return os << "TokenType::String";
        case TokenType::Object:
            return os << "TokenType::Object";
        case TokenType::Func:
            return os << "TokenType::Func";
        case TokenType::Void:
            return os << "TokenType::Void";

        case TokenType::NOT:
            return os << "TokenType::NOT";
        case TokenType::AND:
            return os << "TokenType::AND";
        case TokenType::NAND:
            return os << "TokenType::NAND";
        case TokenType::OR:
            return os << "TokenType::OR";
        case TokenType::NOR:
            return os << "TokenType::NOR";
        case TokenType::XOR:
            return os << "TokenType::XOR";
        case TokenType::XNOR:
            return os << "TokenType::XNOR";

        case TokenType::FunctionDef:
            return os << "TokenType::FunctionDef";

        case TokenType::If:
            return os << "TokenType::If";
        case TokenType::Elif:
            return os << "TokenType::Elif";
        case TokenType::Else:
            return os << "TokenType::Else";
        case TokenType::While:
            return os << "TokenType::While";

        case TokenType::Colon:
            return os << "TokenType::Colon";
        case TokenType::Dot:
            return os << "TokenType::Dot";
        case TokenType::Comma:
            return os << "TokenType::Comma";
        case TokenType::Arrow:
            return os << "TokenType::Arrow";
        case TokenType::LineEnd:
            return os << "TokenType::LineEnd";
        case TokenType::Comment:
            return os << "TokenType::Comment";
        case TokenType::Eof:
            return os << "TokenType::Eof";

        default:
            return os << "!!! TokenType Unknown !!!";
    }
}

std::ostream& operator<<(std::ostream& os, const Token obj) {
    os << "Token(";
    os << "Type: " << obj.getType() << ", ";
    os << "Value: '" << obj.getValue() << "')\n";
    return os;
}
