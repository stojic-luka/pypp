#include "charactersLiteral.h"

CharactersLiteral::CharactersLiteral() : isString(nullptr) { kind = NodeType::CharactersLiteral; }
CharactersLiteral::CharactersLiteral(std::string value) : value(value), isString(true) { kind = NodeType::CharactersLiteral; }
CharactersLiteral::CharactersLiteral(std::string value, bool isString) : value(value), isString(isString) { kind = NodeType::CharactersLiteral; }

std::string CharactersLiteral::getValue() const { return value; }
bool CharactersLiteral::getIsString() const { return isString; }

void CharactersLiteral::print(std::ostream& os, int indentation) const {
    os << "CharactersLiteral(\n";
    os << std::string(indentation + 1, '\t') << "Kind: " << this->getKind() << ",\n";
    os << std::string(indentation + 1, '\t') << "Value: " << this->getValue() << ",\n";
    os << std::string(indentation + 1, '\t') << "IsString?: " << this->getIsString() << " )";
}