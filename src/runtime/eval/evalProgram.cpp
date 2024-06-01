#include "evalProgram.h"

#include "../../ast/identifier.h"
#include "../interpreter.h"

RuntimeVal* evaluateProgram(Program* program, Environment* env) {
    RuntimeVal* lastEvaluated = new NoneVal(); 	// MEMORY LEAK
    for (const auto& statement : program->getBody())
        lastEvaluated = evaluate(statement, env);
    return lastEvaluated;
}