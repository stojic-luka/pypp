#pragma once

#include "expr.h"

class NumericLiteral : public Expr {
private:
    double value;

public:
    NumericLiteral();
    NumericLiteral(double value);

    double getValue() const;

    void print(std::ostream& os, int indentation = 0) const override;
};