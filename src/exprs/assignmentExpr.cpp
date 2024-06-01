#include "assignmentExpr.h"

AssignmentExpr::AssignmentExpr() : assignee(nullptr), value(nullptr) { kind = NodeType::AssignmentExpr; }
AssignmentExpr::AssignmentExpr(Expr* assignee, Expr* value) : assignee(assignee), value(value) {
    kind = NodeType::AssignmentExpr;
}

Expr* AssignmentExpr::getAssignee() const { return assignee; };
Expr* AssignmentExpr::getValue() const { return value; };

void AssignmentExpr::print(std::ostream& os, int indentation) const {
    os << "AssignmentExpression(\n";
    os << std::string(indentation + 1, '\t') << "Kind: " << this->getKind() << ",\n";
    os << std::string(indentation + 1, '\t') << "Assignee: ";
    this->getAssignee()->print(os, indentation + 1);
    os << ",\n";
    os << std::string(indentation + 1, '\t') << "Value: ";
    this->getValue()->print(os, indentation + 1);
    os << " )";
}

AssignmentExpr::~AssignmentExpr() {
    delete assignee;
    delete value;
}