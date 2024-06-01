#include "whileExpr.h"

WhileExpr::WhileExpr() : condition(nullptr), body({}) { kind = NodeType::WhileExpr; }
WhileExpr::WhileExpr(Expr* condition, std::vector<Stmt*> body) : condition(condition), body(body) {
    kind = NodeType::WhileExpr;
}

Expr* WhileExpr::getCondition() const { return condition; }
std::vector<Stmt*> WhileExpr::getBody() const { return body; }

void WhileExpr::print(std::ostream& os, int indentation) const {
    os << "WhileExpression(\n";
}

WhileExpr::~WhileExpr() {
    delete condition;
    for (Stmt* stmt : body)
        delete stmt;
}
