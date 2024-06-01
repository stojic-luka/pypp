#pragma once

#include <ostream>

enum class NodeType {
    Program = 0,
    VariableDeclaration = 1,
    FunctionDeclaration = 2,

    AssignmentExpr = 3,
    MemberExpr = 4,
    CallExpr = 5,

    IfExpr = 6,
    ForExpr = 7,
    WhileExpr = 8,

    Property = 9,
    ObjectLiteral = 10,
    NumericLiteral = 11,
    CharactersLiteral = 12,
    Identifier = 13,
    BinaryExpr = 14,
    LogicalExpr = 15,
    BooleanExpr = 16
};

std::ostream& operator<<(std::ostream& os, const NodeType type);