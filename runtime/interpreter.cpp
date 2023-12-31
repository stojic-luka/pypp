#include "interpreter.h"

#include <cmath>
#include <exception>
#include <iostream>
#include <string>

#include "../frontend/ast.h"
#include "../frontend/exprs.h"
#include "environment.h"
#include "eval/expressions.h"
#include "eval/statements.h"
#include "values.h"

RuntimeVal *evaluate(Stmt *astNode, Environment *env) {
    switch (astNode->getKind()) {
        case NodeType::NumericLiteral:
            return new NumberVal(static_cast<NumericLiteral *>(astNode)->getValue());
        case NodeType::CharactersLiteral: {
            CharactersLiteral *obj = static_cast<CharactersLiteral *>(astNode);
            return new CharactersVal(obj->getIsString() ? ValueType::Characters : ValueType::Character, obj->getValue());
        }
        case NodeType::Identifier:
            return evaluateIdentifier(static_cast<Identifier *>(astNode), env);
        case NodeType::ObjectLiteral:
            return evaluateObjectExpr(static_cast<ObjectLiteral *>(astNode), env);
        case NodeType::CallExpr:
            return evaluateCallExpr(static_cast<CallExpr *>(astNode), env);
        case NodeType::AssignmentExpr:
            return evaluateAssignment(static_cast<AssignmentExpr *>(astNode), env);
        case NodeType::BinaryExpr:
            return evaluateBinaryExpr(static_cast<BinaryExpr *>(astNode), env);
        // case NodeType::BooleanExpr:
        //     return evaluateBooleanExpr(static_cast<BooleanExpr *>(astNode), env);
        case NodeType::LogicalExpr:
            return evaluateLogicalExpr(static_cast<LogicalExpr *>(astNode), env);
        case NodeType::Program:
            return evaluateProgram(static_cast<Program *>(astNode), env);
        case NodeType::VariableDeclaration:
            return evaluateVariableDeclaration(static_cast<VariableDeclaration *>(astNode), env);
        case NodeType::FunctionDeclaration:
            return evaluateFunctionDeclaration(static_cast<FunctionDeclaration *>(astNode), env);
        case NodeType::MemberExpr:
            return evaluateMemberExpr(static_cast<MemberExpr *>(astNode), env);
        case NodeType::IfExpr:
            return evaluateIfExpr(static_cast<IfExpr *>(astNode), env);
        case NodeType::ForExpr:
            return evaluateForExpr(static_cast<ForExpr *>(astNode), env);
        case NodeType::WhileExpr:
            return evaluateWhileExpr(static_cast<WhileExpr *>(astNode), env);
        default:
            std::cout << std::endl;
            std::cout << *astNode << std::endl;
            throw std::runtime_error("AST Node has not yet been setup for interpretation");
    }
}
