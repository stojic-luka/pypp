#include "valueTypes.h"

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "tokenTypes.h"
#include "../runtime/environment.h"

#include "../globalVals.h"

std::ostream &operator<<(std::ostream &os, const ValueType type) {
    switch (type) {
        case ValueType::Number:
            return os << "ValueType::Number";
        case ValueType::Character:
            return os << "ValueType::Character";
        case ValueType::Characters:
            return os << "ValueType::Characters";
        case ValueType::Bool:
            return os << "ValueType::Bool";
        case ValueType::None:
            return os << "ValueType::None";
        case ValueType::Object:
            return os << "ValueType::MemberExpr";
        case ValueType::NativeFn:
            return os << "ValueType::NativeFn";
        case ValueType::Function:
            return os << "ValueType::Function";

        default:
            return os << "!!! ValueType Unknown !!! operator<<";
    }
}

////////////////////////////////

ValueType RuntimeVal::getType() const { return type; }

////////////////////////////////

CharactersVal::CharactersVal() { type = ValueType::Characters; }
CharactersVal::CharactersVal(std::string value) : value(value) { type = ValueType::Characters; }
CharactersVal::CharactersVal(ValueType type, std::string value) : value(value) { this->type = type; }

std::string CharactersVal::getValue() const { return value; }
void CharactersVal::setValue(std::string value) { this->value = value; }

void CharactersVal::print(std::ostream &os, int indentation) const {
    if (isDebug) {
        os << "CharactersValue( ";
        os << "Type: " << this->getType() << ", ";
        os << "Value: '" << this->getValue() << "' )";
    } else {
        os << this->getValue();
    }
}

////////////////////////////////

NumberVal::NumberVal() : value(0) { type = ValueType::Number; }
NumberVal::NumberVal(double value) : value(value) { type = ValueType::Number; }

double NumberVal::getValue() const { return value; }
void NumberVal::setValue(double value) { this->value = value; }

void NumberVal::print(std::ostream &os, int indentation) const {
    if (isDebug) {
        os << "NumberValue( ";
        os << "Type: " << this->getType() << ", ";
        os << "Value: '" << this->getValue() << "' )";
    } else {
        os << this->getValue();
    }
}

////////////////////////////////

BoolVal::BoolVal() : value(true) { type = ValueType::Bool; }
BoolVal::BoolVal(bool b) : value(b) { type = ValueType::Bool; }

bool BoolVal::getValue() const { return value; }
void BoolVal::setValue(bool value) { this->value = value; }

void BoolVal::print(std::ostream &os, int indentation) const {
    if (isDebug) {
        os << "BoolValue( ";
        os << "Type: " << this->getType() << ", ";
        os << "Value: '" << this->getValue() << "' )";
    } else {
        os << (this->getValue() ? "True" : "False");
    }
}

////////////////////////////////

NoneVal::NoneVal() : value(nullptr) { type = ValueType::None; }

int *NoneVal::getValue() const { return value; }

void NoneVal::print(std::ostream &os, int indentation) const {
    if (isDebug) {
        os << "NoneValue( ";
        os << "Type: " << this->getType() << ", ";
        os << "Value: '" << this->getValue() << "' )";
    } else {
        os << "None";
    }
}

////////////////////////////////

ObjectVal::ObjectVal() { type = ValueType::Object; }
ObjectVal::ObjectVal(std::unordered_map<std::string, RuntimeVal *> properties) : properties(properties) { type = ValueType::Object; }

std::unordered_map<std::string, RuntimeVal *> ObjectVal::getProperties() const { return properties; }

void ObjectVal::print(std::ostream &os, int indentation) const {
    if (isDebug) {
        os << "ObjectValue(\n";
        os << std::string(indentation + 1, '\t') << "Type: " << this->getType() << ",\n";
        if (this->getProperties().size() > 0) {
            os << std::string(indentation + 1, '\t') << "Value: [\n";
            for (const auto &item : this->getProperties()) {
                os << std::string(indentation + 2, '\t') << "{ " << item.first << ": ";
                item.second->print(os, indentation + 2);
                os << " }\n";
            }
            os << std::string(indentation + 1, '\t') << "] )";
        } else
            os << std::string(indentation + 1, '\t') << "Value: Empty )";
    } else {
        os << "{\n";
        for (const auto &item : this->getProperties()) {
            os << std::string(indentation + 1, '\t') << "'" << item.first << "': ";
            item.second->print(os, indentation + 1);
            os << "\n";
        }
        os << std::string(indentation, '\t') << "}";
    }
}

////////////////////////////////

NativeFuncVal::NativeFuncVal(const FunctionCall call) : call(call) { type = ValueType::NativeFn; }

const FunctionCall NativeFuncVal::getCall() const { return call; }

void NativeFuncVal::print(std::ostream &os, int indentation) const {
    os << "NativeFunctionValue(Kind: " << this->getType() << ",)";
}

////////////////////////////////

FunctionVal::FunctionVal(TokenType returnType, std::string name, std::unordered_map<TokenType, std::string> parameters, Environment *declarationEnvironment, std::vector<Stmt *> body) {
    type = ValueType::Function;
    this->returnType = returnType;
    this->name = name;
    this->parameters = parameters;
    this->declarationEnvironment = declarationEnvironment;
    this->body = body;
}

TokenType FunctionVal::getReturnType() const { return returnType; }
std::string FunctionVal::getName() const { return name; }
std::unordered_map<TokenType, std::string> FunctionVal::getParameters() const { return parameters; }
Environment *FunctionVal::getDeclarationEnvironment() const { return declarationEnvironment; }
std::vector<Stmt *> FunctionVal::getBody() const { return body; }

void FunctionVal::print(std::ostream &os, int indentation) const {
    // TODO: implement print
    os << "FunctionValue(Kind: " << this->getType() << ",)";
}

FunctionVal::~FunctionVal() {
    delete declarationEnvironment;
    for (Stmt *stmt : body) {
        delete stmt;
    }
}

std::ostream &operator<<(std::ostream &os, const FunctionVal &node) {
    node.print(os);
    return os;
}

////////////////////////////////

void RuntimeVal::print(std::ostream &os, int indentation) const {
    switch (this->getType()) {
        case ValueType::Number: {
            static_cast<const NumberVal *>(this)->print(os, indentation);
            break;
        }
        case ValueType::Character:
        case ValueType::Characters: {
            static_cast<const CharactersVal *>(this)->print(os, indentation);
            break;
        }
        case ValueType::Bool: {
            static_cast<const BoolVal *>(this)->print(os, indentation);
            break;
        }
        case ValueType::None: {
            static_cast<const NoneVal *>(this)->print(os, indentation);
            break;
        }
        case ValueType::Object: {
            static_cast<const ObjectVal *>(this)->print(os, indentation);
            break;
        }
        case ValueType::NativeFn: {
            static_cast<const NativeFuncVal *>(this)->print(os, indentation);
            break;
        }
        case ValueType::Function: {
            static_cast<const FunctionVal *>(this)->print(os, indentation);
            break;
        }

        default:
            os << "!!! ValueType Unknown !!! RuntimeVal::print";
    }
};

std::ostream &operator<<(std::ostream &os, const RuntimeVal &node) {
    node.print(os);
    return os;
}