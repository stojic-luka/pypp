#pragma once

#include <unordered_map>

#include "../ast/expr.h"

class IfExpr : public Expr {
private:
    std::unordered_map<Expr*, std::vector<Stmt*>> cases;
    std::vector<Stmt*> elseCase;
    bool hasElse;

public:
    IfExpr();
    IfExpr(std::unordered_map<Expr*, std::vector<Stmt*>> cases);
    IfExpr(std::unordered_map<Expr*, std::vector<Stmt*>> cases, std::vector<Stmt*> elseCase);

    std::unordered_map<Expr*, std::vector<Stmt*>> getCases() const;
    std::vector<Stmt*> getElseCase() const;
    bool getHasElse() const;

    void print(std::ostream& os, int indentation = 0) const override;

    ~IfExpr();
};