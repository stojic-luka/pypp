#include "evalMemberExpr.h"

#include "../../ast/identifier.h"
#include "../interpreter.h"

RuntimeVal* evaluateMemberExpr(MemberExpr* expr, Environment* env) {
    RuntimeVal* objectVal = evaluate(expr->getObject(), env);

    if (objectVal->getType() == ValueType::Object) {
        auto props = static_cast<ObjectVal*>(objectVal)->getProperties();
        std::string symbol = static_cast<Identifier*>(expr->getProperty())->getSymbol();
        if (props.count(symbol))
            return props.at(symbol);

        throw std::runtime_error("Object child does not exist");
    }
    throw std::runtime_error("Member expression invalid");
}