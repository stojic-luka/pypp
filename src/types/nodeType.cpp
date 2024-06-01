#include "nodeType.h"

#include <iostream>

std::ostream& operator<<(std::ostream& os, const NodeType type) {
    switch (type) {
    case NodeType::Program:
        return os << "NodeType::Program";
    case NodeType::VariableDeclaration:
        return os << "NodeType::VariableDeclaration";
    case NodeType::FunctionDeclaration:
        return os << "NodeType::FunctionDeclaration";

    case NodeType::AssignmentExpr:
        return os << "NodeType::AssignmentExpr";
    case NodeType::CallExpr:
        return os << "NodeType::CallExpr";
    case NodeType::MemberExpr:
        return os << "NodeType::MemberExpr";

    case NodeType::IfExpr:
        return os << "NodeType::IfExpr";
    case NodeType::ForExpr:
        return os << "NodeType::ForExpr";
    case NodeType::WhileExpr:
        return os << "NodeType::WhileExpr";

    case NodeType::Property:
        return os << "NodeType::Property";
    case NodeType::ObjectLiteral:
        return os << "NodeType::ObjectLiteral";
    case NodeType::NumericLiteral:
        return os << "NodeType::NumericLiteral";
    case NodeType::CharactersLiteral:
        return os << "NodeType::CharactersLiteral";
    case NodeType::Identifier:
        return os << "NodeType::Identifier";
    case NodeType::BinaryExpr:
        return os << "NodeType::BinaryExpr";
    case NodeType::BooleanExpr:
        return os << "NodeType::BooleanExpr";

    default:
        return os << "!!! NodeType Unknown !!!";
    }
}