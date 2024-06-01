#include "evalWhileExpr.h"

#include "evalBinaryExpr.h"
#include "../interpreter.h"

RuntimeVal* evaluateWhileExpr(WhileExpr* expr, Environment* env) {
    Environment* scope = new Environment(env);

    // RuntimeVal *condition = evaluateBooleanExpr(static_cast<BooleanExpr *>(expr->getCondition()), scope);
    BoolVal* condition = evaluateLogicalExpr(static_cast<LogicalExpr*>(expr->getCondition()), scope);
    while (condition->getValue()) {
        for (auto const& stmt : expr->getBody())
            evaluate(stmt, scope);

        // condition = evaluateBooleanExpr(static_cast<BooleanExpr *>(expr->getCondition()), scope);
        condition = evaluateLogicalExpr(static_cast<LogicalExpr*>(expr->getCondition()), scope);
    }

    return new NoneVal();
}