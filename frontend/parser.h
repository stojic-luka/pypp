#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

enum class TokenType;
class Stmt;
class Token;
class Expr;
class Program;

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
    std::unordered_map<TokenType, std::string> parseParams();
    std::unordered_map<TokenType, std::string> parseParamList();
    std::vector<Expr*> parseArgs();
    std::vector<Expr*> parseArgList();
    Expr* parseMemberExpr();
    Expr* parsePrimaryExpr();
    Expr* parseIfExpr();
    Expr* parseForExpr();
    Expr* parseWhileExpr();

   public:
    Program* produceAST(std::string sourceCode);
};

#endif  // PARSER_H