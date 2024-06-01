#pragma once

#include "../ast/expr.h"

class AssignmentExpr : public Expr {
private:
    Expr* assignee;
    Expr* value;

public:
    AssignmentExpr();
    AssignmentExpr(Expr* assignee, Expr* value);
    Expr* getAssignee() const;
    Expr* getValue() const;

    void print(std::ostream& os, int indentation = 0) const override;

    ~AssignmentExpr();
};
