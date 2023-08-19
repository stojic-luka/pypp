#include "expressions.h"

#include <math.h>

#include <memory>

#include "../../frontend/ast.h"
#include "../../frontend/exprs.h"
#include "../environment.h"
#include "../interpreter.h"
#include "../values.h"

NumberVal *evaluateNumericBinaryExpr(NumberVal *leftHandSide, NumberVal *rightHandSide, std::string op) {
    NumberVal *numberVal = new NumberVal();
    if (op == "+")
        numberVal->setValue(leftHandSide->getValue() + rightHandSide->getValue());
    else if (op == "-")
        numberVal->setValue(leftHandSide->getValue() - rightHandSide->getValue());
    else if (op == "*")
        numberVal->setValue(leftHandSide->getValue() * rightHandSide->getValue());
    else if (op == "/") {
        if (rightHandSide->getValue() == 0)
            throw std::runtime_error("Division by zero");

        numberVal->setValue(leftHandSide->getValue() / rightHandSide->getValue());
    } else if (op == "%")
        numberVal->setValue(std::fmod(leftHandSide->getValue(), rightHandSide->getValue()));
    else if (op == "^")
        numberVal->setValue(std::pow(leftHandSide->getValue(), rightHandSide->getValue()));
    else
        throw std::runtime_error("Invalid binary operator! Operator: " + op);

    return numberVal;
}

NumberVal *evaluateBinaryExpr(BinaryExpr *binop, Environment *env) {
    RuntimeVal *leftHandSide = evaluate(binop->getLeft(), env);
    RuntimeVal *rightHandSide = evaluate(binop->getRight(), env);

    if (leftHandSide->getType() == ValueType::Number && rightHandSide->getType() == ValueType::Number) {
        NumberVal *leftHandSideNumVal = static_cast<NumberVal *>(leftHandSide);
        NumberVal *rightHandSideNumVal = static_cast<NumberVal *>(rightHandSide);

        return evaluateNumericBinaryExpr(leftHandSideNumVal, rightHandSideNumVal, binop->getOp());
    }

    throw std::runtime_error("Both sides of the binary operation must be numbers");
}

BoolVal *evaluateNumericBooleanExpr(NumberVal *leftHandSide, NumberVal *rightHandSide, std::string op) {
    BoolVal *boolVal = new BoolVal();
    if (op == "==")
        boolVal->setValue(leftHandSide->getValue() == rightHandSide->getValue());
    else if (op == "<")
        boolVal->setValue(leftHandSide->getValue() < rightHandSide->getValue());
    else if (op == ">")
        boolVal->setValue(leftHandSide->getValue() > rightHandSide->getValue());
    else if (op == "<=")
        boolVal->setValue(leftHandSide->getValue() <= rightHandSide->getValue());
    else if (op == ">=")
        boolVal->setValue(leftHandSide->getValue() >= rightHandSide->getValue());
    else if (op == "!=")
        boolVal->setValue(leftHandSide->getValue() != rightHandSide->getValue());
    else
        throw std::runtime_error("Invalid boolean operator! Operator: " + op);

    return boolVal;
}

// RuntimeVal *evaluateBooleanExpr(BooleanExpr *boolop, Environment *env) {
//     // return evaluateBooleanExpr(boolop, env);
//     return new NoneVal();
// }

BoolVal *evaluateLogicalExpr(LogicalExpr *boolop, Environment *env) {
    RuntimeVal *leftHandSide = evaluate(boolop->getLeft(), env);
    RuntimeVal *rightHandSide = evaluate(boolop->getRight(), env);

    if (leftHandSide->getType() == ValueType::Number && rightHandSide->getType() == ValueType::Number) {
        NumberVal *leftHandSideNumVal = static_cast<NumberVal *>(leftHandSide);
        NumberVal *rightHandSideNumVal = static_cast<NumberVal *>(rightHandSide);

        return evaluateNumericBooleanExpr(leftHandSideNumVal, rightHandSideNumVal, boolop->getOp());
    }

    throw std::runtime_error("Both sides of the boolean operation must be numbers");
}

RuntimeVal *evaluateIdentifier(Identifier *ident, Environment *env) {
    return env->lookup(ident->getSymbol())->getValue();
}

RuntimeVal *evaluateAssignment(AssignmentExpr *node, Environment *env) {
    if (node->getAssignee()->getKind() != NodeType::Identifier)
        throw std::runtime_error("Invalid LMS inside assignment expr");

    std::string varName = (static_cast<Identifier *>(node->getAssignee()))->getSymbol();
    return env->assignVar(varName, evaluate(node->getValue(), env));
}

RuntimeVal *evaluateObjectExpr(ObjectLiteral *obj, Environment *env) {
    std::unordered_map<std::string, RuntimeVal *> props;
    for (auto const &property : obj->getProperties()) {
        RuntimeVal *runtimeVal = property->getValue() == NULL ? env->lookup(property->getKey())->getValue() : evaluate(property->getValue(), env);
        props.insert(std::make_pair(property->getKey(), runtimeVal));
    }
    return new ObjectVal(props);
}

RuntimeVal *evaluateCallExpr(CallExpr *expr, Environment *env) {
    std::vector<RuntimeVal *> args;
    for (auto const &arg : expr->getArgs())
        args.push_back(evaluate(arg, env));

    RuntimeVal *fn = evaluate(expr->getCaller(), env);
    if (fn->getType() == ValueType::NativeFn) {
        NativeFuncVal *result = static_cast<NativeFuncVal *>(fn);
        return (result->getCall())(args, env);
    }

    if (fn->getType() == ValueType::Function) {
        FunctionVal *func = static_cast<FunctionVal *>(fn);
        Environment *scope = new Environment(func->getDeclarationEnvironment());

        auto params = func->getParameters();
        auto paramIt = params.begin();
        auto argIt = args.begin();
        for (; paramIt != params.end() && argIt != args.end(); ++paramIt, ++argIt) {
            auto const &[tokenType, varName] = *paramIt;
            scope->declareVar(tokenType, varName, *argIt, false);
        }

        RuntimeVal *result = new NoneVal();
        for (auto const &stmt : func->getBody())
            result = evaluate(stmt, scope);

        delete scope;
        return result;
    }

    std::cout << fn << std::endl;
    throw std::runtime_error("Cannot call a value that is not a function!");
}

RuntimeVal *evaluateMemberExpr(MemberExpr *expr, Environment *env) {
    RuntimeVal *objectVal = evaluate(expr->getObject(), env);

    if (objectVal->getType() == ValueType::Object) {
        auto props = static_cast<ObjectVal *>(objectVal)->getProperties();
        std::string symbol = static_cast<Identifier *>(expr->getProperty())->getSymbol();
        if (props.count(symbol))
            return props.at(symbol);

        throw std::runtime_error("Object child does not exist");
    }
    throw std::runtime_error("Member expression invalid");
}

RuntimeVal *evaluateIfExpr(IfExpr *expr, Environment *env) {
    Environment *scope = new Environment(env);

    bool executed = false;
    for (auto const &[condition, stmts] : expr->getCases())
        if (static_cast<BoolVal *>(evaluate(condition, scope))->getValue()) {
            executed = true;
            for (auto const &stmt : stmts)
                evaluate(stmt, scope);
        }

    if (expr->getHasElse() && !executed) {
        for (auto const &stmt : expr->getElseCase())
            evaluate(stmt, scope);
    }
    return new NoneVal();
}

RuntimeVal *evaluateForExpr(ForExpr *expr, Environment *env) {
    Environment *scope = new Environment(env);

    for (auto const &var : expr->getVariables())
        scope->declareVar(var.second.getType(), var.first, new NumberVal(var.second.getStart()), false);

    // RuntimeVal *condition = evaluateBooleanExpr(static_cast<BooleanExpr *>(expr->getCondition()), scope);
    BoolVal *condition = evaluateLogicalExpr(static_cast<LogicalExpr *>(expr->getCondition()), scope);
    while (condition->getValue()) {
        for (auto const &stmt : expr->getBody())
            evaluate(stmt, scope);

        for (auto const &iterExpr : expr->getIterExprs())
            evaluateBinaryExpr(iterExpr, scope);

        // condition = evaluateBooleanExpr(static_cast<BooleanExpr *>(expr->getCondition()), scope);
        condition = evaluateLogicalExpr(static_cast<LogicalExpr *>(expr->getCondition()), scope);
    }

    // todo: finish

    return new NoneVal();
}

RuntimeVal *evaluateWhileExpr(WhileExpr *expr, Environment *env) {
    Environment *scope = new Environment(env);

    // RuntimeVal *condition = evaluateBooleanExpr(static_cast<BooleanExpr *>(expr->getCondition()), scope);
    BoolVal *condition = evaluateLogicalExpr(static_cast<LogicalExpr *>(expr->getCondition()), scope);
    while (condition->getValue()) {
        for (auto const &stmt : expr->getBody())
            evaluate(stmt, scope);

        // condition = evaluateBooleanExpr(static_cast<BooleanExpr *>(expr->getCondition()), scope);
        condition = evaluateLogicalExpr(static_cast<LogicalExpr *>(expr->getCondition()), scope);
    }

    return new NoneVal();
}