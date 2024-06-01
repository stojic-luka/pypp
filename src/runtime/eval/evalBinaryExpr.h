#pragma once

#include "../environment.h"

#include "../../exprs/binaryExpr.h"
#include "../../exprs/logicalExpr.h"
#include "../../types/valueTypes.h"

NumberVal* evaluateBinaryExpr(BinaryExpr* binop, Environment* env);
NumberVal* evaluateNumericBinaryExpr(NumberVal* leftHandSide, NumberVal* rightHandSide, std::string op);

BoolVal* evaluateLogicalExpr(LogicalExpr* boolop, Environment* env);
BoolVal* evaluateNumericBooleanExpr(NumberVal* leftHandSide, NumberVal* rightHandSide, std::string op);