#pragma once

#include <memory>
#include <ostream>
#include <unordered_map>
#include <vector>

#include "../ast/stmt.h"
#include "../runtime/environment.h"

enum class ValueType {
    Number,
    Character,
    Characters,
    Bool,
    None,
    Object,
    NativeFn,
    Function
};
std::ostream &operator<<(std::ostream &os, const ValueType type);

////////////////////////////////

class RuntimeVal {
   protected:
    ValueType type;

   public:
    ValueType getType() const;

    void print(std::ostream &os, int indentation = 0) const;
};

std::ostream &operator<<(std::ostream &os, const RuntimeVal &node);

////////////////////////////////

class CharactersVal : public RuntimeVal {
   private:
    std::string value;

   public:
    CharactersVal();
    CharactersVal(std::string value);
    CharactersVal(ValueType type, std::string value);

    std::string getValue() const;
    void setValue(std::string value);

    void print(std::ostream &os, int indentation = 0) const;
};

////////////////////////////////

class NumberVal : public RuntimeVal {
   private:
    double value;

   public:
    NumberVal();
    NumberVal(double value);

    double getValue() const;
    void setValue(double value);

    void print(std::ostream &os, int indentation = 0) const;
};

////////////////////////////////

class BoolVal : public RuntimeVal {
   private:
    bool value;

   public:
    BoolVal();
    BoolVal(bool b);

    bool getValue() const;
    void setValue(bool value);

    void print(std::ostream &os, int indentation = 0) const;
};

////////////////////////////////

class NoneVal : public RuntimeVal {
   private:
    int *value;

   public:
    NoneVal();

    int *getValue() const;

    void print(std::ostream &os, int indentation = 0) const;

    ~NoneVal();
};

////////////////////////////////

class ObjectVal : public RuntimeVal {
   private:
    std::unordered_map<std::string, RuntimeVal *> properties;

   public:
    ObjectVal();
    ObjectVal(std::unordered_map<std::string, RuntimeVal *> properties);

    std::unordered_map<std::string, RuntimeVal *> getProperties() const;

    void print(std::ostream &os, int indentation = 0) const;

    ~ObjectVal();
};

////////////////////////////////

using FunctionCall = RuntimeVal *(*)(const std::vector<RuntimeVal *> &, Environment *);
class NativeFuncVal : public RuntimeVal {
   private:
    const FunctionCall call;

   public:
    NativeFuncVal(const FunctionCall call);

    const FunctionCall getCall() const;

    void print(std::ostream &os, int indentation = 0) const;
};

////////////////////////////////

class FunctionVal : public RuntimeVal {
   private:
    TokenType returnType;
    std::string name;
    std::unordered_map<TokenType, std::string> parameters;
    Environment *declarationEnvironment;
    std::vector<Stmt *> body;

   public:
    FunctionVal(TokenType returnType, std::string name, std::unordered_map<TokenType, std::string> parameters, Environment *declarationEnvironment, std::vector<Stmt *> body);

    TokenType getReturnType() const;
    std::string getName() const;
    std::unordered_map<TokenType, std::string> getParameters() const;
    Environment *getDeclarationEnvironment() const;
    std::vector<Stmt *> getBody() const;

    void print(std::ostream &os, int indentation = 0) const;

    ~FunctionVal();
};

std::ostream &operator<<(std::ostream &os, const FunctionVal &node);