#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include <memory>
#include <string>

class RuntimeVal;
class NumberVal;
class BoolVal;
class Environment;
class BinaryExpr;
class LogicalExpr;
class BooleanExpr;
class Identifier;
class AssignmentExpr;
class ObjectLiteral;
class CallExpr;
class MemberExpr;
class IfExpr;
class ForExpr;
class WhileExpr;

// std::unique_ptr<NumberVal> evaluateNumericBinaryExpr(NumberVal *leftHandSide, NumberVal *rightHandSide, std::string op);
NumberVal *evaluateBinaryExpr(BinaryExpr *binop, Environment *env);
// std::unique_ptr<BoolVal> evaluateNumericBooleanExpr(NumberVal *leftHandSide, NumberVal *rightHandSide, std::string op);
BoolVal *evaluateLogicalExpr(LogicalExpr *boolop, Environment *env);
// RuntimeVal *evaluateBooleanExpr(BooleanExpr *boolop, Environment *env);
RuntimeVal *evaluateIdentifier(Identifier *ident, Environment *env);
RuntimeVal *evaluateAssignment(AssignmentExpr *node, Environment *env);
RuntimeVal *evaluateObjectExpr(ObjectLiteral *obj, Environment *env);
RuntimeVal *evaluateCallExpr(CallExpr *expr, Environment *env);
RuntimeVal *evaluateMemberExpr(MemberExpr *expr, Environment *env);
RuntimeVal *evaluateIfExpr(IfExpr *expr, Environment *env);
RuntimeVal *evaluateForExpr(ForExpr *expr, Environment *env);
RuntimeVal *evaluateWhileExpr(WhileExpr *expr, Environment *env);

#endif  // EXPRESSIONS_H
