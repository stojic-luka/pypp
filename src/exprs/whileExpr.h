#pragma once

#include <vector>

#include "../ast/expr.h"

class WhileExpr : public Expr {
private:
    Expr* condition;
    std::vector<Stmt*> body;

public:
    WhileExpr();
    WhileExpr(Expr* condition, std::vector<Stmt*> body);

    Expr* getCondition() const;
    std::vector<Stmt*> getBody() const;

    void print(std::ostream& os, int indentation = 0) const override;

    ~WhileExpr();
};