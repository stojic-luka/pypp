#include "booleanExpr.h"

BooleanExpr::BooleanExpr() { kind = NodeType::BooleanExpr; }

void BooleanExpr::print(std::ostream& os, int indentation) const {
    os << "BooleanExpression(\n";
}

BooleanExpr::~BooleanExpr() {
}