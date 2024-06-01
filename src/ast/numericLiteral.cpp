#include "NumericLiteral.h"

NumericLiteral::NumericLiteral() : value(0) { kind = NodeType::NumericLiteral; }
NumericLiteral::NumericLiteral(double value) : value(value) { kind = NodeType::NumericLiteral; }

double NumericLiteral::getValue() const { return value; }

void NumericLiteral::print(std::ostream& os, int indentation) const {
    os << "NumericLiteral(\n";
    os << std::string(indentation + 1, '\t') << "Kind: " << this->getKind() << ",\n";
    os << std::string(indentation + 1, '\t') << "Value: " << this->getValue() << " )";
}
