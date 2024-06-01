#include "evalVariableDeclaration.h"

#include "../../ast/identifier.h"
#include "../interpreter.h"

RuntimeVal* evaluateVariableDeclaration(VariableDeclaration* declaration, Environment* env) {
    RuntimeVal* value = declaration->getValue() ? evaluate(declaration->getValue(), env) : new NoneVal();
    return env->declareVar(declaration->getType(), declaration->getIdentifier(), value, declaration->getIsConst());
}