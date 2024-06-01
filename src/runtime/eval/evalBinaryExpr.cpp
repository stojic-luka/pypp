#include "evalBinaryExpr.h"

#include "../interpreter.h"

NumberVal* evaluateBinaryExpr(BinaryExpr* binop, Environment* env) {
    RuntimeVal* leftHandSide = evaluate(binop->getLeft(), env);
    RuntimeVal* rightHandSide = evaluate(binop->getRight(), env);

    if (leftHandSide->getType() == ValueType::Number && rightHandSide->getType() == ValueType::Number) {
        NumberVal* leftHandSideNumVal = static_cast<NumberVal*>(leftHandSide);
        NumberVal* rightHandSideNumVal = static_cast<NumberVal*>(rightHandSide);

        return evaluateNumericBinaryExpr(leftHandSideNumVal, rightHandSideNumVal, binop->getOp());
    }

    throw std::runtime_error("Both sides of the binary operation must be numbers");
}

NumberVal* evaluateNumericBinaryExpr(NumberVal* leftHandSide, NumberVal* rightHandSide, std::string op) {
    NumberVal* numberVal = new NumberVal();
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
    }
    else if (op == "%")
        numberVal->setValue(std::fmod(leftHandSide->getValue(), rightHandSide->getValue()));
    else if (op == "^")
        numberVal->setValue(std::pow(leftHandSide->getValue(), rightHandSide->getValue()));
    else
        throw std::runtime_error("Invalid binary operator! Operator: " + op);

    return numberVal;
}

BoolVal* evaluateLogicalExpr(LogicalExpr* boolop, Environment* env) {
    RuntimeVal* leftHandSide = evaluate(boolop->getLeft(), env);
    RuntimeVal* rightHandSide = evaluate(boolop->getRight(), env);

    if (leftHandSide->getType() == ValueType::Number && rightHandSide->getType() == ValueType::Number) {
        NumberVal* leftHandSideNumVal = static_cast<NumberVal*>(leftHandSide);
        NumberVal* rightHandSideNumVal = static_cast<NumberVal*>(rightHandSide);

        return evaluateNumericBooleanExpr(leftHandSideNumVal, rightHandSideNumVal, boolop->getOp());
    }

    throw std::runtime_error("Both sides of the boolean operation must be numbers");
}

BoolVal* evaluateNumericBooleanExpr(NumberVal* leftHandSide, NumberVal* rightHandSide, std::string op) {
    BoolVal* boolVal = new BoolVal();
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