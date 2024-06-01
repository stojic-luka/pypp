#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <memory>
#include <ostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "../types/tokenTypes.h"

class RuntimeVal;

class EnvVariableInfo {
   private:
    TokenType type;
    RuntimeVal* value;
    bool isConst;

   public:
    EnvVariableInfo() {}
    EnvVariableInfo(TokenType type, RuntimeVal* value, bool isConst) : type(type), value(value), isConst(isConst) {}

    TokenType getType() const;
    RuntimeVal* getValue() const;
    bool getIsConst() const;

    void setValue(RuntimeVal* value);

    //~EnvVariableInfo();
};
std::ostream& operator<<(std::ostream& os, const EnvVariableInfo node);

class Environment {
   private:
    Environment* parent;
    std::unordered_map<std::string, EnvVariableInfo> variables;

   public:
    Environment();
    explicit Environment(Environment* parentEnv);

    static Environment* createGlobalEnv();

    RuntimeVal* declareVar(TokenType type, std::string varName, RuntimeVal* value, bool isConst);
    RuntimeVal* assignVar(std::string varName, RuntimeVal* value);
    EnvVariableInfo* lookup(std::string varName);
    Environment* resolve(std::string varName);

    Environment* getParent() const;
    std::unordered_map<std::string, EnvVariableInfo> getVariables() const;

    void print(std::ostream& os, int indentation = 0) const;

    ~Environment();
};
std::ostream& operator<<(std::ostream& os, const Environment node);

#endif  // ENVIRONMENT_H
