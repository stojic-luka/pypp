#include "evalCallExpr.h"

#include <iostream>

#include "../interpreter.h"

RuntimeVal* evaluateCallExpr(CallExpr* expr, Environment* env) {
    std::vector<RuntimeVal*> args;
    for (auto const& arg : expr->getArgs())
        args.push_back(evaluate(arg, env));

    RuntimeVal* fn = evaluate(expr->getCaller(), env);
    if (fn->getType() == ValueType::NativeFn) {
        NativeFuncVal* result = static_cast<NativeFuncVal*>(fn);
        return (result->getCall())(args, env);
    }

    if (fn->getType() == ValueType::Function) {
        FunctionVal* func = static_cast<FunctionVal*>(fn);
        Environment* scope = new Environment(func->getDeclarationEnvironment());

        auto params = func->getParameters();
        auto paramIt = params.begin();
        auto argIt = args.begin();
        for (; paramIt != params.end() && argIt != args.end(); ++paramIt, ++argIt) {
            auto const& [tokenType, varName] = *paramIt;
            scope->declareVar(tokenType, varName, *argIt, false);
        }

        RuntimeVal* result = new NoneVal();
        for (auto const& stmt : func->getBody())
            result = evaluate(stmt, scope);

        delete scope;
        return result;
    }

    std::cout << fn << std::endl;
    throw std::runtime_error("Cannot call a value that is not a function!");
}