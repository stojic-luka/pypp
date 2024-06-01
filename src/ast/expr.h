#pragma once

#include "stmt.h"

class Expr : public Stmt {
public:
    void print(std::ostream& os, int indentation = 0) const override;

    // Expr::~Expr();
};
