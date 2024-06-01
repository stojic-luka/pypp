#include "Property.h"

#include <string>

Property::Property() : value(nullptr) { kind = NodeType::Property; }
Property::Property(std::string key) : key(key), value(nullptr) { kind = NodeType::Property; }
Property::Property(std::string key, Expr* value) : key(key), value(value) { kind = NodeType::Property; }

std::string Property::getKey() const { return key; }
Expr* Property::getValue() const { return value; }

void Property::print(std::ostream& os, int indentation) const {
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
