#include "ast.h"

#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "exprs.h"
#include "tokenTypes.h"

std::ostream &operator<<(std::ostream &os, const NodeType type) {
    switch (type) {
        case NodeType::Program:
            return os << "NodeType::Program";
        case NodeType::VariableDeclaration:
            return os << "NodeType::VariableDeclaration";
        case NodeType::FunctionDeclaration:
            return os << "NodeType::FunctionDeclaration";

        case NodeType::AssignmentExpr:
            return os << "NodeType::AssignmentExpr";
        case NodeType::CallExpr:
            return os << "NodeType::CallExpr";
        case NodeType::MemberExpr:
            return os << "NodeType::MemberExpr";

        case NodeType::IfExpr:
            return os << "NodeType::IfExpr";
        case NodeType::ForExpr:
            return os << "NodeType::IfExpr";
        case NodeType::WhileExpr:
            return os << "NodeType::IfExpr";

        case NodeType::Property:
            return os << "NodeType::Property";
        case NodeType::ObjectLiteral:
            return os << "NodeType::ObjectLiteral";
        case NodeType::NumericLiteral:
            return os << "NodeType::NumericLiteral";
        case NodeType::CharactersLiteral:
            return os << "NodeType::CharactersLiteral";
        case NodeType::Identifier:
            return os << "NodeType::Identifier";
        case NodeType::BinaryExpr:
            return os << "NodeType::BinaryExpr";
        case NodeType::BooleanExpr:
            return os << "NodeType::BooleanExpr";

        default:
            return os << "!!! NodeType Unknown !!!";
    }
}

////////////////////////////////

NodeType Stmt::getKind() const { return kind; };
std::ostream &operator<<(std::ostream &os, const Stmt &node) {
    node.print(os);
    return os;
}

void Expr::print(std::ostream &os, int indentation) const {
    switch (this->getKind()) {
        case NodeType::AssignmentExpr: {
            static_cast<const AssignmentExpr *>(this)->print(os, indentation);
            break;
        }
        case NodeType::BinaryExpr: {
            static_cast<const BinaryExpr *>(this)->print(os, indentation);
            break;
        }
        case NodeType::CallExpr: {
            static_cast<const CallExpr *>(this)->print(os, indentation);
            break;
        }
        case NodeType::MemberExpr: {
            static_cast<const MemberExpr *>(this)->print(os, indentation);
            break;
        }
        case NodeType::IfExpr: {
            static_cast<const IfExpr *>(this)->print(os, indentation);
            break;
        }
        case NodeType::ForExpr: {
            static_cast<const ForExpr *>(this)->print(os, indentation);
            break;
        }
        case NodeType::WhileExpr: {
            static_cast<const WhileExpr *>(this)->print(os, indentation);
            break;
        }
        case NodeType::Identifier: {
            static_cast<const Identifier *>(this)->print(os, indentation);
            break;
        }
        case NodeType::NumericLiteral: {
            static_cast<const NumericLiteral *>(this)->print(os, indentation);
            break;
        }
        case NodeType::CharactersLiteral: {
            static_cast<const CharactersLiteral *>(this)->print(os, indentation);
            break;
        }
        case NodeType::Property: {
            static_cast<const Property *>(this)->print(os, indentation);
            break;
        }
        case NodeType::ObjectLiteral: {
            static_cast<const ObjectLiteral *>(this)->print(os, indentation);
            break;
        }
    }
    os << ",\n";
}

Expr::~Expr() {
}

////////////////////////////////

Program::Program() { kind = NodeType::Program; }
Program::Program(std::vector<Stmt *> body) : body(body) { kind = NodeType::Program; }

std::vector<Stmt *> Program::getBody() const { return body; }
void Program::bodyPush(Stmt *p) { body.push_back(p); }

void Program::print(std::ostream &os, int indentation) const {
    os << "Program(\n";
    os << std::string(indentation + 1, '\t') << "Kind: " << this->getKind() << ",\n";
    if (this->getBody().size() > 0) {
        os << std::string(indentation + 1, '\t') << "Body: [\n";
        for (auto &item : this->getBody()) {
            os << std::string(indentation + 2, '\t');
            item->print(os, indentation + 2);
            os << std::endl;
        }
        os << std::string(indentation + 1, '\t') << "]\n";
    } else
        os << std::string(indentation + 1, '\t') << "Body: empty )\n";
}

Program::~Program() {
    for (Stmt *stmt : body)
        delete stmt;
    body.clear();
}

////////////////////////////////

VariableDeclaration::VariableDeclaration() { kind = NodeType::VariableDeclaration; }
VariableDeclaration::VariableDeclaration(TokenType type, std::string ident, Expr *value) : type(type), identifier(identifier), value(value) {
    kind = NodeType::VariableDeclaration;
    for (char c : this->identifier)
        if (!std::isupper(c)) {
            isConst = false;
            break;
        }
}
VariableDeclaration::VariableDeclaration(TokenType type, std::string ident, Expr *value, bool isConst) {
    kind = NodeType::VariableDeclaration;
    this->type = type;
    this->identifier = ident;
    this->value = value;
    this->isConst = isConst;
}

TokenType VariableDeclaration::getType() const { return type; }
std::string VariableDeclaration::getIdentifier() const { return identifier; }
Expr *VariableDeclaration::getValue() const { return value; }
bool VariableDeclaration::getIsConst() const { return isConst; }

void VariableDeclaration::print(std::ostream &os, int indentation) const {
    os << "VariableDeclaration(\n";
    os << std::string(indentation + 1, '\t') << "Kind: " << this->getKind() << ",\n";
    os << std::string(indentation + 1, '\t') << "Type: " << this->getType() << ",\n";
    os << std::string(indentation + 1, '\t') << "Identifier: '" << this->getIdentifier() << "',\n";
    os << std::string(indentation + 1, '\t') << "Value: ";
    this->getValue()->print(os, indentation + 1);
    os << ",\n";
    os << std::string(indentation + 1, '\t') << "IsConst: " << (this->getIsConst() ? "True" : "False") << " )\n";
}

VariableDeclaration::~VariableDeclaration() {
    delete value;
}

////////////////////////////////

FunctionDeclaration::FunctionDeclaration() { kind = NodeType::FunctionDeclaration; }
FunctionDeclaration::FunctionDeclaration(TokenType returnType, std::string name, std::unordered_map<TokenType, std::string> parameters, std::vector<Stmt *> body, bool isConst, bool isLambda) {
    kind = NodeType::FunctionDeclaration;
    this->returnType = returnType;
    this->name = name;
    this->parameters = parameters;
    this->body = body;
    this->isConst = isConst;
    this->isLambda = isLambda;
}

TokenType FunctionDeclaration::getReturnType() const { return returnType; }
std::string FunctionDeclaration::getName() const { return name; }
std::unordered_map<TokenType, std::string> FunctionDeclaration::getParameters() const { return parameters; }
std::vector<Stmt *> FunctionDeclaration::getBody() const { return body; }
bool FunctionDeclaration::getIsConst() const { return isConst; }
bool FunctionDeclaration::getIsLambda() const { return isLambda; }

void FunctionDeclaration::print(std::ostream &os, int indentation) const {
    os << "FunctionDeclaration(\n";
    os << std::string(indentation + 1, '\t') << "Kind: " << this->getKind() << ",\n";
    os << std::string(indentation + 1, '\t') << "Type: " << this->getReturnType() << ",\n";
    os << std::string(indentation + 1, '\t') << "Name: '" << this->getName() << "',\n";

    os << std::string(indentation + 1, '\t') << "Parameters: [";
    // for (const auto &item : this->getParameters())
    //     os << std::string(indentation + 2, '\t') << "" << item << ",\n";
    os << "],\n";

    os << std::string(indentation + 1, '\t') << "Body: [";
    for (const auto &item : this->getBody())
        item->print(os, indentation + 2);
    os << "],\n";

    os << std::string(indentation + 1, '\t') << "IsConst: " << (this->getIsConst() ? "True" : "False") << " )\n";
    os << std::string(indentation + 1, '\t') << "IsLambda: " << (this->getIsLambda() ? "True" : "False") << " )\n";
}

FunctionDeclaration::~FunctionDeclaration() {
    for (Stmt *stmt : body)
        delete stmt;
    body.clear();
}

////////////////////////////////

CharactersLiteral::CharactersLiteral() { kind = NodeType::CharactersLiteral; }
CharactersLiteral::CharactersLiteral(std::string value) : value(value), isString(true) { kind = NodeType::CharactersLiteral; }
CharactersLiteral::CharactersLiteral(std::string value, bool isString) : value(value), isString(isString) { kind = NodeType::CharactersLiteral; }

std::string CharactersLiteral::getValue() const { return value; }
bool CharactersLiteral::getIsString() const { return isString; }

void CharactersLiteral::print(std::ostream &os, int indentation) const {
    os << "CharactersLiteral(\n";
    os << std::string(indentation + 1, '\t') << "Kind: " << this->getKind() << ",\n";
    os << std::string(indentation + 1, '\t') << "Value: " << this->getValue() << ",\n";
    os << std::string(indentation + 1, '\t') << "IsString?: " << this->getIsString() << " )";
}

////////////////////////////////

Identifier::Identifier() { kind = NodeType::Identifier; }
Identifier::Identifier(std::string symbol) : symbol(symbol) { kind = NodeType::Identifier; }

std::string Identifier::getSymbol() const { return symbol; }

void Identifier::print(std::ostream &os, int indentation) const {
    os << "Identifier(\n";
    os << std::string(indentation + 1, '\t') << "Kind: " << this->getKind() << ",\n";
    os << std::string(indentation + 1, '\t') << "Symbol: '" << this->getSymbol() << "' )";
}

////////////////////////////////

Property::Property() { kind = NodeType::Property; }
Property::Property(std::string key) : key(key) { kind = NodeType::Property; }
Property::Property(std::string key, Expr *value) : key(key), value(value) { kind = NodeType::Property; }

std::string Property::getKey() const { return key; }
Expr *Property::getValue() const { return value; }

void Property::print(std::ostream &os, int indentation) const {
    os << "Property(\n";
    os << std::string(indentation + 1, '\t') << "Kind: " << this->getKind() << ",\n";
    os << std::string(indentation + 1, '\t') << "Key: " << this->getKey() << ",\n";
    os << std::string(indentation + 1, '\t') << "Value: ";
    this->getValue()->print(os, indentation + 1);
    os << " )\n";
}

Property::~Property() {
    delete value;
}

////////////////////////////////

NumericLiteral::NumericLiteral() { kind = NodeType::NumericLiteral; }
NumericLiteral::NumericLiteral(double value) : value(value) { kind = NodeType::NumericLiteral; }

double NumericLiteral::getValue() const { return value; }

void NumericLiteral::print(std::ostream &os, int indentation) const {
    os << "NumericLiteral(\n";
    os << std::string(indentation + 1, '\t') << "Kind: " << this->getKind() << ",\n";
    os << std::string(indentation + 1, '\t') << "Value: " << this->getValue() << " )";
}

////////////////////////////////

ObjectLiteral::ObjectLiteral() { kind = NodeType::ObjectLiteral; }
ObjectLiteral::ObjectLiteral(std::vector<Property *> properties) : properties(properties) { kind = NodeType::ObjectLiteral; }

std::vector<Property *> ObjectLiteral::getProperties() const { return properties; }

void ObjectLiteral::print(std::ostream &os, int indentation) const {
    os << "ObjectLiteral(\n";
    os << std::string(indentation + 1, '\t') << "Kind: " << this->getKind() << ",\n";

    os << std::string(indentation + 1, '\t') << "Properties: [\n";
    for (auto &item : this->getProperties()) {
        os << std::string(indentation + 2, '\t');
        item->print(os, indentation + 1);
    }

    os << std::string(indentation + 1, '\t') << "] )";
}

ObjectLiteral::~ObjectLiteral() {
    for (Property *prop : properties)
        delete prop;
    properties.clear();
}