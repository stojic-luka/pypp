#include "statements.h"

#include "../../frontend/ast.h"
#include "../../frontend/tokenTypes.h"
#include "../environment.h"
#include "../interpreter.h"
#include "../values.h"

RuntimeVal *evaluateProgram(Program *program, Environment *env) {
    RuntimeVal *lastEvaluated = new NoneVal();
    for (const auto &statement : program->getBody())
        lastEvaluated = evaluate(statement, env);
    return lastEvaluated;
}

RuntimeVal *evaluateVariableDeclaration(VariableDeclaration *declaration, Environment *env) {
    RuntimeVal *value = declaration->getValue() ? evaluate(declaration->getValue(), env) : new NoneVal();
    return env->declareVar(declaration->getType(), declaration->getIdentifier(), value, declaration->getIsConst());
}

RuntimeVal *evaluateFunctionDeclaration(FunctionDeclaration *declaration, Environment *env) {
    FunctionVal *function = new FunctionVal(
        declaration->getReturnType(),
        declaration->getName(),
        declaration->getParameters(),
        env,
        declaration->getBody());

    return env->declareVar(TokenType::Func, declaration->getName(), function, true);
}
