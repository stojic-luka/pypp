#include "environment.h"

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "../types/tokenTypes.h"
#include "../types/valueTypes.h"
#include "nativeFuncs.h"

TokenType EnvVariableInfo::getType() const { return type; }
RuntimeVal* EnvVariableInfo::getValue() const { return value; }
bool EnvVariableInfo::getIsConst() const { return isConst; }
void EnvVariableInfo::setValue(RuntimeVal* value) { this->value = value; }
//EnvVariableInfo::~EnvVariableInfo() { delete value; }

bool isVariableValid(RuntimeVal* val, TokenType type) {
    switch (type) {
        case TokenType::Int:
            if (val->getType() == ValueType::Number) {
                double numVal = static_cast<NumberVal*>(val)->getValue();
                if (std::floor(numVal) == numVal)
                    return true;
            }
            return false;

        case TokenType::Float:
        case TokenType::Double:
            if (val->getType() == ValueType::Number) {
                double numVal = static_cast<NumberVal*>(val)->getValue();
                if (std::floor(numVal) != numVal)
                    return true;
            }
            return false;

        case TokenType::Char:
            if (val->getType() == ValueType::Character) {
                std::string strVal = static_cast<CharactersVal*>(val)->getValue();
                if (strVal.length() == 1)
                    return true;
            }
            return false;

        case TokenType::String:
            if (val->getType() == ValueType::Characters)
                return true;
            return false;

        case TokenType::Bool:
            if (val->getType() == ValueType::Bool)
                return true;
            return false;

        case TokenType::Void:
            if (val->getType() == ValueType::None)
                return true;
            return false;

        case TokenType::Func:
            if (val->getType() == ValueType::NativeFn || val->getType() == ValueType::Function)
                return true;
            return false;

        default:
            std::cout << std::endl;
            std::cout << type;
            throw std::runtime_error("Unknown value type in variable validation");
    }
}

Environment::Environment() : parent(nullptr) {}
Environment::Environment(Environment* parentEnv) : parent{parentEnv} {}

Environment* Environment::createGlobalEnv() {
    Environment* env = new Environment();

    env->declareVar(TokenType::Bool, "True", new BoolVal(true), 1); 	// MEMORY LEAK
    env->declareVar(TokenType::Bool, "False", new BoolVal(false), 1); 	// MEMORY LEAK
    env->declareVar(TokenType::Void, "None", new NoneVal(), 1); 	// MEMORY LEAK
    ////////////////////////////////

    env->declareVar(TokenType::Func, "print", new NativeFuncVal(printNativeFunc), 1); 	// MEMORY LEAK

    env->declareVar(TokenType::Func, "sqrt", new NativeFuncVal(sqrtNativeFunc), 1); 	// MEMORY LEAK
    env->declareVar(TokenType::Func, "cbrt", new NativeFuncVal(cbrtNativeFunc), 1); 	// MEMORY LEAK

    env->declareVar(TokenType::Func, "max", new NativeFuncVal(maxNativeFunc), 1); 	// MEMORY LEAK
    env->declareVar(TokenType::Func, "min", new NativeFuncVal(minNativeFunc), 1); 	// MEMORY LEAK

    //env->declareVar(TokenType::Func, "sleep", new NativeFuncVal(sleepNativeFunc), 1); 	// MEMORY LEAK
    //env->declareVar(TokenType::Func, "timerStart", new NativeFuncVal(timerStartNativeFunc), 1); 	// MEMORY LEAK
    //env->declareVar(TokenType::Func, "timerStop", new NativeFuncVal(timerStopNativeFunc), 1); 	// MEMORY LEAK
    //env->declareVar(TokenType::Func, "timerDuration", new NativeFuncVal(durationNativeFunc), 1); 	// MEMORY LEAK

    return env;
}

RuntimeVal* Environment::declareVar(TokenType type, std::string varName, RuntimeVal* value, bool isConst) {
    if (variables.count(varName))
        throw std::runtime_error("Variable " + varName + " already defined!");

    if (isVariableValid(value, type)) {
        variables.insert({varName, EnvVariableInfo(type, value, isConst)});
        return value;
    }
    throw std::runtime_error("Variable type does not match with its value type declareVar");
}

RuntimeVal* Environment::assignVar(std::string varName, RuntimeVal* value) {
    Environment* env = resolve(varName);

    if (env->variables.at(varName).getIsConst())
        throw std::runtime_error("Cannot change value of a constant variable");

    if (isVariableValid(value, env->variables.at(varName).getType())) {
        env->variables[varName].setValue(value);
        return value;
    }
    throw std::runtime_error("Variable type does not match with its value type assignVar");
}

EnvVariableInfo* Environment::lookup(std::string varName) {
    Environment* env = resolve(varName);

    if (env->variables.count(varName))
        return &(env->variables.at(varName));

    throw std::runtime_error("Variable " + varName + " not defined!");
}

Environment* Environment::resolve(std::string varName) {
    if (variables.count(varName) > 0)
        return this;

    if (parent == nullptr)
        throw std::runtime_error("Cannot resolve '" + varName + "' as it does not exist!");

    return parent->resolve(varName);
}

Environment* Environment::getParent() const { return parent; }
std::unordered_map<std::string, EnvVariableInfo> Environment::getVariables() const { return variables; }

void Environment::print(std::ostream& os, int indentation) const {
    os << "Environment(\n";
    os << std::string(indentation + 1, '\t') << "Parent: " << this->getParent() << ",\n";

    os << std::string(indentation + 1, '\t') << "Variables: [\n";
    for (const auto& [symbol, varInfo] : this->getVariables()) {
        os << std::string(indentation + 2, '\t') << "{ " << symbol << ": (";
        os << varInfo.getType() << ", " << *varInfo.getValue() << ", " << (varInfo.getIsConst() ? "const" : "not const");
        os << ") }" << std::endl;
    }
    os << std::string(indentation + 1, '\t') << "]\n";
}

Environment::~Environment() {
    delete parent;
}

std::ostream& operator<<(std::ostream& os, const Environment node) {
    node.print(os);
    return os;
}
std::ostream& operator<<(std::ostream& os, const EnvVariableInfo node) {
    os << "EnvVariableInfo(";
    os << node.getType() << ", ";
    os << *node.getValue() << ", ";
    os << node.getIsConst() << ")\n";
    return os;
}

// todo: popravi sve printove