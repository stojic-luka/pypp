#ifndef AST_H
#define AST_H

#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "tokenTypes.h"

enum class NodeType {
    Program,
    VariableDeclaration,
    FunctionDeclaration,

    AssignmentExpr,
    MemberExpr,
    CallExpr,

    IfExpr,
    ForExpr,
    WhileExpr,

    Property,
    ObjectLiteral,
    NumericLiteral,
    CharactersLiteral,
    Identifier,
    BinaryExpr,
    LogicalExpr,
    BooleanExpr
};
std::ostream &operator<<(std::ostream &os, const NodeType type);

class Stmt {
   protected:
    NodeType kind;

   public:
    NodeType getKind() const;

    virtual void print(std::ostream &os, int indentation = 0) const = 0;
};
std::ostream &operator<<(std::ostream &os, const Stmt &node);

class Expr : public Stmt {
   public:
    void print(std::ostream &os, int indentation = 0) const override;

    Expr::~Expr();
};

class Program : public Stmt {
   private:
    std::vector<Stmt *> body;

   public:
    Program();
    Program(std::vector<Stmt *> body);

    std::vector<Stmt *> getBody() const;
    void bodyPush(Stmt *p);

    void print(std::ostream &os, int indentation = 0) const override;

    ~Program();
};

class VariableDeclaration : public Stmt {
   private:
    bool isConst = false;
    TokenType type;
    std::string identifier;
    Expr *value;

   public:
    VariableDeclaration();
    VariableDeclaration(TokenType type, std::string ident, Expr *value);
    VariableDeclaration(TokenType type, std::string ident, Expr *value, bool isConst);

    TokenType getType() const;
    std::string getIdentifier() const;
    Expr *getValue() const;
    bool getIsConst() const;

    void print(std::ostream &os, int indentation = 0) const override;

    ~VariableDeclaration();
};

class FunctionDeclaration : public Stmt {
   private:
    TokenType returnType;
    std::string name;
    std::unordered_map<TokenType, std::string> parameters;
    std::vector<Stmt *> body;
    bool isConst, isLambda;

   public:
    FunctionDeclaration();
    FunctionDeclaration(TokenType returnType, std::string name, std::unordered_map<TokenType, std::string> parameters, std::vector<Stmt *> body,
                        bool isConst = false, bool isLambda = false);

    TokenType getReturnType() const;
    std::string getName() const;
    std::unordered_map<TokenType, std::string> getParameters() const;
    std::vector<Stmt *> getBody() const;
    bool getIsConst() const;
    bool getIsLambda() const;

    void print(std::ostream &os, int indentation = 0) const override;

    ~FunctionDeclaration();
};

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

    void print(std::ostream &os, int indentation = 0) const;
};

class Identifier : public Expr {
   private:
    std::string symbol;

   public:
    Identifier();
    Identifier(std::string symbol);

    std::string getSymbol() const;

    void print(std::ostream &os, int indentation = 0) const;
};

class Property : public Expr {
   private:
    std::string key;
    Expr *value;

   public:
    Property();
    Property(std::string key);
    Property(std::string key, Expr *value);

    std::string getKey() const;
    Expr *getValue() const;

    void print(std::ostream &os, int indentation = 0) const;

    ~Property();
};

class NumericLiteral : public Expr {
   private:
    double value;

   public:
    NumericLiteral();
    NumericLiteral(double value);

    double getValue() const;

    void print(std::ostream &os, int indentation = 0) const;
};

class ObjectLiteral : public Expr {
   private:
    std::vector<Property *> properties;

   public:
    ObjectLiteral();
    ObjectLiteral(std::vector<Property *> properties);

    std::vector<Property *> getProperties() const;

    void print(std::ostream &os, int indentation = 0) const;

    ~ObjectLiteral();
};

#endif  // AST_H