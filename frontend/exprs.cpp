#include "exprs.h"

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "ast.h"

AssignmentExpr::AssignmentExpr() { kind = NodeType::AssignmentExpr; }
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

////////////////////////////////

BinaryExpr::BinaryExpr() { kind = NodeType::BinaryExpr; }
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

////////////////////////////////

BooleanExpr::BooleanExpr() { kind = NodeType::BooleanExpr; }

void BooleanExpr::print(std::ostream& os, int indentation) const {
    os << "BooleanExpression(\n";
}

BooleanExpr::~BooleanExpr() {
}

////////////////////////////////

LogicalExpr::LogicalExpr() { kind = NodeType::LogicalExpr; }
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

////////////////////////////////

CallExpr::CallExpr() { kind = NodeType::CallExpr; }
CallExpr::CallExpr(Expr* caller, std::vector<Expr*> args) : caller(caller), args(args) {
    kind = NodeType::CallExpr;
}

std::vector<Expr*> CallExpr::getArgs() const { return args; }
Expr* CallExpr::getCaller() const { return caller; }

void CallExpr::print(std::ostream& os, int indentation) const {
    os << "CallExpression(\n";
    os << std::string(indentation + 1, '\t') << "Kind: " << this->getKind() << ",\n";

    os << std::string(indentation + 1, '\t') << "Caller: ";
    this->getCaller()->print(os, indentation + 1);
    os << ",\n";

    if (this->getArgs().size() > 0) {
        os << std::string(indentation + 1, '\t') << "Args: [\n";
        for (auto& item : this->getArgs()) {
            os << std::string(indentation + 2, '\t');
            item->print(os, indentation + 2);
            os << std::endl;
        }
        os << std::string(indentation + 1, '\t') << "] )";
    } else
        os << std::string(indentation + 1, '\t') << "Args: Empty )";
}

CallExpr::~CallExpr() {
    for (Expr* arg : args)
        delete arg;
    args.clear();
}

////////////////////////////////

MemberExpr::MemberExpr() { kind = NodeType::MemberExpr; }
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

////////////////////////////////

IfExpr::IfExpr() { kind = NodeType::IfExpr; }
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

////////////////////////////////

ForExpr::ForExpr() { kind = NodeType::ForExpr; }
ForExpr::ForExpr(std::unordered_map<std::string, ForVariablesInfo> variables, Expr* condition, std::vector<BinaryExpr*> iterExprs, std::vector<Stmt*> body, bool isForEach) {
    kind = NodeType::ForExpr;
    this->variables = variables;
    this->condition = condition;
    this->iterExprs = iterExprs;
    this->body = body;
    this->isForEach = isForEach;
}

std::unordered_map<std::string, ForVariablesInfo> ForExpr::getVariables() const { return variables; }
Expr* ForExpr::getCondition() const { return condition; }
std::vector<BinaryExpr*> ForExpr::getIterExprs() const { return iterExprs; }
std::vector<Stmt*> ForExpr::getBody() const { return body; }
bool ForExpr::getIsForEach() const { return isForEach; }

void ForExpr::print(std::ostream& os, int indentation) const {
    os << "ForExpression(\n";
}

ForExpr::~ForExpr() {
    variables.clear();
    delete condition;
    for (BinaryExpr* iterExpr : iterExprs)
        delete iterExpr;
    for (Stmt* stmt : body)
        delete stmt;
}

////////////////////////////////

WhileExpr::WhileExpr() { kind = NodeType::WhileExpr; }
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
