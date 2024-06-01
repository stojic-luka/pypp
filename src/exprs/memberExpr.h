#pragma once

#include <ostream>

#include "../ast/expr.h"

class MemberExpr : public Expr {
private:
    Expr* object;
    Expr* property;
    bool computed;

public:
    MemberExpr();
    MemberExpr(Expr* object, Expr* property, bool computed);

    Expr* getObject() const;
    Expr* getProperty() const;
    bool getComputed() const;

    void print(std::ostream& os, int indentation = 0) const override;

    ~MemberExpr();
};