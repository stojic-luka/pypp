#pragma once

#include <ostream>

#include "../ast/expr.h"

class BooleanExpr : public Expr {
private:
public:
    BooleanExpr();

    void print(std::ostream& os, int indentation = 0) const override;

    ~BooleanExpr();
};
