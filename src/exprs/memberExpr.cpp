#include "memberExpr.h"

MemberExpr::MemberExpr() : object(nullptr), property(nullptr), computed(nullptr) { kind = NodeType::MemberExpr; }
MemberExpr::MemberExpr(Expr* object, Expr* property, bool computed) : object(object), property(property), computed(computed) {
    kind = NodeType::MemberExpr;
}

Expr* MemberExpr::getObject() const { return object; }
Expr* MemberExpr::getProperty() const { return property; };
bool MemberExpr::getComputed() const { return computed; };

void MemberExpr::print(std::ostream& os, int indentation) const {
    os << "MemberExpression(\n";
    os << std::string(indentation + 1, '\t') << "Kind: " << this->getKind() << ",\n";
    os << std::string(indentation + 1, '\t') << "Object: ";
    this->getObject()->print(os, indentation + 1);
    os << ",\n";
    os << std::string(indentation + 1, '\t') << "Property: ";
    this->getProperty()->print(os, indentation + 1);
    os << ",\n";
    os << std::string(indentation + 1, '\t') << "Computed?: " << (this->getComputed() ? "True" : "False") << " )";
}

MemberExpr::~MemberExpr() {
    delete object;
    delete property;
}
