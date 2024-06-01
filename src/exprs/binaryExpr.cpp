#include "binaryExpr.h"

BinaryExpr::BinaryExpr() : left(nullptr), right(nullptr) { kind = NodeType::BinaryExpr; }
BinaryExpr::BinaryExpr(std::string op, Expr* left, Expr* right) : op(op), left(left), right(right) {
    kind = NodeType::BinaryExpr;
}

Expr* BinaryExpr::getLeft() const { return left; }
Expr* BinaryExpr::getRight() const { return right; };
std::string BinaryExpr::getOp() const { return op; };

void BinaryExpr::print(std::ostream& os, int indentation) const {
    os << "BinaryExpression(\n";
    os << std::string(indentation + 1, '\t') << "Kind: " << this->getKind() << ",\n";
    os << std::string(indentation + 1, '\t') << "Left: ";
    this->getLeft()->print(os, indentation + 1);
    os << ",\n";
    os << std::string(indentation + 1, '\t') << "Right: ";
    this->getRight()->print(os, indentation + 1);
    os << ",\n";
    os << std::string(indentation + 1, '\t') << "Operator: '" << this->getOp() << "')";
}

BinaryExpr::~BinaryExpr() {
    delete left;
    delete right;
}