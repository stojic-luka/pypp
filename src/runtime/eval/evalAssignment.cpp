#include "evalAssignment.h"

#include "../../ast/identifier.h"
#include "../interpreter.h"

RuntimeVal* evaluateAssignment(AssignmentExpr* node, Environment* env) {
    if (node->getAssignee()->getKind() != NodeType::Identifier)
        throw std::runtime_error("Invalid LMS inside assignment expr");

    std::string varName = (static_cast<Identifier*>(node->getAssignee()))->getSymbol();
    return env->assignVar(varName, evaluate(node->getValue(), env));
}