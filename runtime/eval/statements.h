#ifndef STATEMENTS_H
#define STATEMENTS_H

#include <memory>

class RuntimeVal;
class Program;
class Environment;
class VariableDeclaration;
class FunctionDeclaration;

RuntimeVal *evaluateProgram(Program *program, Environment *env);
RuntimeVal *evaluateVariableDeclaration(VariableDeclaration *declaration, Environment *env);
RuntimeVal *evaluateFunctionDeclaration(FunctionDeclaration *declaration, Environment *env);

#endif  // STATEMENTS_H
