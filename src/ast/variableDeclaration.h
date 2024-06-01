#pragma once

#include "stmt.h"
#include "expr.h"
#include "../types/tokenTypes.h"

class VariableDeclaration : public Stmt {
private:
    bool isConst = false;
    TokenType type;
    std::string identifier;
    Expr* value;

public:
    VariableDeclaration();
    VariableDeclaration(TokenType type, std::string ident, Expr* value);
    VariableDeclaration(TokenType type, std::string ident, Expr* value, bool isConst);

    TokenType getType() const;
    std::string getIdentifier() const;
    Expr* getValue() const;
    bool getIsConst() const;

    void print(std::ostream& os, int indentation = 0) const override;

    ~VariableDeclaration();
};