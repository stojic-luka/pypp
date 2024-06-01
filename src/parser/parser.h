#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "../lexer/lexer.h"
#include "../ast/stmt.h"
#include "../ast/expr.h"
#include "../ast/program.h"
#include "../types/tokenTypes.h"

class Parser {
private:
    std::vector<Token> tokens;

    bool not_eof();

    Stmt* parseStmt();
    Stmt* parseVariableDeclaration();
    Stmt* parseFunctionDeclaration();

    Token eat();
    Token eat(TokenType type, std::string errMessage);
    Token eat(const std::vector<TokenType>& types, std::string errMessage);

    Expr* parseExpr();
    Expr* parseAssignmentExpr();
    Expr* parseObjectExpr();
    Expr* parseBooleanExpr();
    Expr* parseLogicalExpr();
    Expr* parseAdditiveExpr();
    Expr* parseMultiplicitaveExpr();
    Expr* parseExponentionalExpr();
    Expr* parseCallMemberExpr();
    Expr* parseCallExpr(Expr* caller);
    std::vector<Expr*> parseArgs();
    std::unordered_map<TokenType, std::string> parseParams();
    //std::unordered_map<TokenType, std::string> parseParamList();
    Expr* parseMemberExpr();
    Expr* parseIfExpr();
    Expr* parseForExpr();
    Expr* parseWhileExpr();
    Expr* parsePrimaryExpr();

public:
    Program* produceAST(std::string sourceCode);
};