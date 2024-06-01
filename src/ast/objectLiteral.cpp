#include "ObjectLiteral.h"

ObjectLiteral::ObjectLiteral() { kind = NodeType::ObjectLiteral; }
ObjectLiteral::ObjectLiteral(std::vector<Property*> properties) : properties(properties) { kind = NodeType::ObjectLiteral; }

std::vector<Property*> ObjectLiteral::getProperties() const { return properties; }

void ObjectLiteral::print(std::ostream& os, int indentation) const {
    os << "ObjectLiteral(\n";
    os << std::string(indentation + 1, '\t') << "Kind: " << this->getKind() << ",\n";

    os << std::string(indentation + 1, '\t') << "Properties: [\n";
    for (auto& item : this->getProperties()) {
        os << std::string(indentation + 2, '\t');
        item->print(os, indentation + 1);
    }

    os << std::string(indentation + 1, '\t') << "] )";
}

ObjectLiteral::~ObjectLiteral() {
    for (Property* prop : properties)
        delete prop;
    properties.clear();
}