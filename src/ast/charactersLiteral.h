#pragma once

#include "expr.h"

class CharactersLiteral : public Expr {
private:
    std::string value;
    bool isString;

public:
    CharactersLiteral();
    CharactersLiteral(std::string value);
    CharactersLiteral(std::string value, bool isString);

    std::string getValue() const;
    bool getIsString() const;

    void print(std::ostream& os, int indentation = 0) const override;
};