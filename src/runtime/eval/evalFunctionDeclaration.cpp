#include "evalFunctionDeclaration.h"

#include "../../ast/identifier.h"

RuntimeVal* evaluateFunctionDeclaration(FunctionDeclaration* declaration, Environment* env) {
    FunctionVal* function = new FunctionVal(
        declaration->getReturnType(),
        declaration->getName(),
        declaration->getParameters(),
        env,
        declaration->getBody());

    return env->declareVar(TokenType::Func, declaration->getName(), function, true);
}