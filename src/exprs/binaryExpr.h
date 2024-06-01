#pragma once

#include "../ast/expr.h"

class BinaryExpr : public Expr {
private:
    Expr* left;
    Expr* right;
    std::string op;

public:
    BinaryExpr();
    BinaryExpr(std::string op, Expr* left, Expr* right);

    Expr* getLeft() const;
    Expr* getRight() const;
    std::string getOp() const;

    void print(std::ostream& os, int indentation = 0) const override;

    ~BinaryExpr();
};
