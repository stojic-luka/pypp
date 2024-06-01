#pragma once

#include <vector>

#include "../ast/expr.h"
#include "../types/tokenTypes.h"
#include "binaryExpr.h"

class ForVariables {
private:
    TokenType type;
    std::string name;
    int value;

public:
    ForVariables() : type(TokenType::None), name(""), value(0) {}
    ForVariables(TokenType type, std::string name, int value, int step) : type(type), name(name), value(value) {}

    TokenType getType() const { return type; }
    std::string getName() const { return name; }
    int getValue() const { return value; }
};

class ForExpr : public Expr {
private:
    std::vector<ForVariables> variables;
    Expr* condition;
    std::vector<BinaryExpr*> iterExprs;
    std::vector<Stmt*> body;
    bool isForEach;

public:
    ForExpr();
    ForExpr(std::vector<ForVariables> variables, Expr* condition, std::vector<BinaryExpr*> iterExprs, std::vector<Stmt*> body, bool isForEach = false);

    std::vector<ForVariables> getVariables() const;
    Expr* getCondition() const;
    std::vector<BinaryExpr*> getIterExprs() const;
    std::vector<Stmt*> getBody() const;
    bool getIsForEach() const;

    void print(std::ostream& os, int indentation = 0) const override;

    ~ForExpr();
};
