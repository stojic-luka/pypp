#include "evalIfExpr.h"

#include "../interpreter.h"

RuntimeVal* evaluateIfExpr(IfExpr* expr, Environment* env) {
    Environment* scope = new Environment(env);

    bool executed = false;
    for (auto const& [condition, stmts] : expr->getCases())
        if (static_cast<BoolVal*>(evaluate(condition, scope))->getValue()) {
            executed = true;
            for (auto const& stmt : stmts)
                evaluate(stmt, scope);
        }

    if (expr->getHasElse() && !executed) {
        for (auto const& stmt : expr->getElseCase())
            evaluate(stmt, scope);
    }
    return new NoneVal();
}