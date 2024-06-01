#pragma once

#include <unordered_map>

#include "stmt.h"
#include "../types/tokenTypes.h"


class FunctionDeclaration : public Stmt {
private:
    TokenType returnType;
    std::string name;
    std::unordered_map<TokenType, std::string> parameters;
    std::vector<Stmt*> body;
    bool isConst, isLambda;

public:
    FunctionDeclaration();
    FunctionDeclaration(TokenType returnType, std::string name, std::unordered_map<TokenType, std::string> parameters, std::vector<Stmt*> body, bool isConst = false, bool isLambda = false);

    TokenType getReturnType() const;
    std::string getName() const;
    std::unordered_map<TokenType, std::string> getParameters() const;
    std::vector<Stmt*> getBody() const;
    bool getIsConst() const;
    bool getIsLambda() const;

    void print(std::ostream& os, int indentation = 0) const override;

    ~FunctionDeclaration();
};