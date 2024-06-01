#include "variableDeclaration.h"

#include <iostream>

VariableDeclaration::VariableDeclaration() : type(TokenType::None), value(nullptr) { kind = NodeType::VariableDeclaration; }
VariableDeclaration::VariableDeclaration(TokenType type, std::string ident, Expr* value) : type(type), identifier(identifier), value(value) {
    kind = NodeType::VariableDeclaration;
    for (char c : this->identifier)
        if (!std::isupper(c)) {
            isConst = false;
            break;
        }
}
VariableDeclaration::VariableDeclaration(TokenType type, std::string ident, Expr* value, bool isConst) {
    kind = NodeType::VariableDeclaration;
    this->type = type;
    this->identifier = ident;
    this->value = value;
    this->isConst = isConst;
}

TokenType VariableDeclaration::getType() const { return type; }
std::string VariableDeclaration::getIdentifier() const { return identifier; }
Expr* VariableDeclaration::getValue() const { return value; }
bool VariableDeclaration::getIsConst() const { return isConst; }

void VariableDeclaration::print(std::ostream& os, int indentation) const {
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
    std::cout << "Variable declaration destructor";
}