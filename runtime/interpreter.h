#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <memory>

class RuntimeVal;
class Stmt;
class Environment;

RuntimeVal* evaluate(Stmt* astNode, Environment* env);

#endif  // INTERPRETER_H
