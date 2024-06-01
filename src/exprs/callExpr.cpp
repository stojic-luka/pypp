#include "callExpr.h"

CallExpr::CallExpr() : caller(nullptr) { kind = NodeType::CallExpr; }
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
    }
    else
        os << std::string(indentation + 1, '\t') << "Args: Empty )";
}

CallExpr::~CallExpr() {
    for (Expr* arg : args)
        delete arg;
    args.clear();
}
