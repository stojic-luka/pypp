#include "forExpr.h"

ForExpr::ForExpr() : condition(nullptr), isForEach(nullptr) { kind = NodeType::ForExpr; }
ForExpr::ForExpr(std::vector<ForVariables> variables, Expr* condition, std::vector<BinaryExpr*> iterExprs, std::vector<Stmt*> body, bool isForEach) {
    kind = NodeType::ForExpr;
    this->variables = variables;
    this->condition = condition;
    this->iterExprs = iterExprs;
    this->body = body;
    this->isForEach = isForEach;
}

std::vector<ForVariables> ForExpr::getVariables() const { return variables; }
Expr* ForExpr::getCondition() const { return condition; }
std::vector<BinaryExpr*> ForExpr::getIterExprs() const { return iterExprs; }
std::vector<Stmt*> ForExpr::getBody() const { return body; }
bool ForExpr::getIsForEach() const { return isForEach; }

void ForExpr::print(std::ostream& os, int indentation) const {
    os << "ForExpression(\n";
}

ForExpr::~ForExpr() {
    if (condition != nullptr)
        delete condition;
    for (BinaryExpr* expr : iterExprs)
        delete expr;
    iterExprs.clear();
    for (Stmt* stmt : body)
        delete stmt;
    body.clear();
}