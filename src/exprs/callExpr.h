#pragma once

#include <ostream>
#include <vector>

#include "../ast/expr.h"

class CallExpr : public Expr {
private:
    std::vector<Expr*> args;
    Expr* caller;

public:
    CallExpr();
    CallExpr(Expr* caller, std::vector<Expr*> args);

    std::vector<Expr*> getArgs() const;
    Expr* getCaller() const;

    void print(std::ostream& os, int indentation = 0) const override;

    ~CallExpr();
};
