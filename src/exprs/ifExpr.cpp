#include "ifExpr.h"

#include <vector>

IfExpr::IfExpr() : hasElse(false) { kind = NodeType::IfExpr; }
IfExpr::IfExpr(std::unordered_map<Expr*, std::vector<Stmt*>> cases) : cases(cases) {
    kind = NodeType::IfExpr;
    hasElse = false;
}
IfExpr::IfExpr(std::unordered_map<Expr*, std::vector<Stmt*>> cases, std::vector<Stmt*> elseCase) : cases(cases), elseCase(elseCase) {
    kind = NodeType::IfExpr;
    hasElse = true;
}

std::unordered_map<Expr*, std::vector<Stmt*>> IfExpr::getCases() const { return cases; };
std::vector<Stmt*> IfExpr::getElseCase() const { return elseCase; };
bool IfExpr::getHasElse() const { return hasElse; };

void IfExpr::print(std::ostream& os, int indentation) const {
    os << "IfExpression(\n";
}

IfExpr::~IfExpr() {
    for (auto const& caseEntry : cases) {
        delete caseEntry.first;
        for (Stmt* stmt : caseEntry.second)
            delete stmt;
    }
    for (Stmt* stmt : elseCase)
        delete stmt;
    cases.clear();
    elseCase.clear();
}