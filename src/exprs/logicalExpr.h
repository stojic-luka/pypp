#pragma once

#include "../ast/expr.h"

class LogicalExpr : public Expr {
private:
    Expr* left;
    Expr* right;
    std::string op;

public:
    LogicalExpr();
    LogicalExpr(std::string op, Expr* left, Expr* right);

    Expr* getLeft() const;
    Expr* getRight() const;
    std::string getOp() const;

    void print(std::ostream& os, int indentation = 0) const override;

    ~LogicalExpr();
};
