#include "identifier.h"

Identifier::Identifier() { kind = NodeType::Identifier; }
Identifier::Identifier(std::string symbol) : symbol(symbol) { kind = NodeType::Identifier; }

std::string Identifier::getSymbol() const { return symbol; }

void Identifier::print(std::ostream& os, int indentation) const {
    os << "Identifier(\n";
    os << std::string(indentation + 1, '\t') << "Kind: " << this->getKind() << ",\n";
    os << std::string(indentation + 1, '\t') << "Symbol: '" << this->getSymbol() << "' )";
}
