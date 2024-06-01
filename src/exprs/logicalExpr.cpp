#include "logicalExpr.h"

LogicalExpr::LogicalExpr() : left(nullptr), right(nullptr) { kind = NodeType::LogicalExpr; }
LogicalExpr::LogicalExpr(std::string op, Expr* left, Expr* right) : op(op), left(left), right(right) {
    kind = NodeType::LogicalExpr;
}

Expr* LogicalExpr::getLeft() const { return left; }
Expr* LogicalExpr::getRight() const { return right; };
std::string LogicalExpr::getOp() const { return op; };

void LogicalExpr::print(std::ostream& os, int indentation) const {
    os << "BooleanExpression(\n";
    os << std::string(indentation + 1, '\t') << "Kind: " << this->getKind() << ",\n";
    os << std::string(indentation + 1, '\t') << "Left: ";
    this->getLeft()->print(os, indentation + 1);
    os << ",\n";
    os << std::string(indentation + 1, '\t') << "Right: ";
    this->getRight()->print(os, indentation + 1);
    os << ",\n";
    os << std::string(indentation + 1, '\t') << "Operator: '" << this->getOp() << "')";
}

LogicalExpr::~LogicalExpr() {
    delete left;
    delete right;
}
