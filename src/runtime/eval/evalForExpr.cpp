#include "evalForExpr.h"

#include "evalBinaryExpr.h"
#include "../interpreter.h"

RuntimeVal* evaluateForExpr(ForExpr* expr, Environment* env) {
    Environment* scope = new Environment(env);

    for (auto const& var : expr->getVariables())
        scope->declareVar(var.getType(), var.getName(), new NumberVal(var.getValue()), false);

    // RuntimeVal *condition = evaluateBooleanExpr(static_cast<BooleanExpr *>(expr->getCondition()), scope);
    BoolVal* condition = evaluateLogicalExpr(static_cast<LogicalExpr*>(expr->getCondition()), scope);
    while (condition->getValue()) {
        for (auto const& stmt : expr->getBody())
            evaluate(stmt, scope);

        for (auto const& iterExpr : expr->getIterExprs())
            evaluateBinaryExpr(iterExpr, scope);

        // condition = evaluateBooleanExpr(static_cast<BooleanExpr *>(expr->getCondition()), scope);
        condition = evaluateLogicalExpr(static_cast<LogicalExpr*>(expr->getCondition()), scope);
    }

    // todo: finish

    return new NoneVal();
}