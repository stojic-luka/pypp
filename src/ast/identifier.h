#pragma once

#include "expr.h"

class Identifier : public Expr {
private:
    std::string symbol;

public:
    Identifier();
    Identifier(std::string symbol);

    std::string getSymbol() const;

    void print(std::ostream& os, int indentation = 0) const override;
};