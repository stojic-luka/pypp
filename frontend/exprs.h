#ifndef EXPRS_H
#define EXPRS_H

#include <ostream>
#include <string>
#include <vector>

#include "ast.h"

class AssignmentExpr : public Expr {
   private:
    Expr *assignee;
    Expr *value;

   public:
    AssignmentExpr();
    AssignmentExpr(Expr *assignee, Expr *value);
    Expr *getAssignee() const;
    Expr *getValue() const;

    void print(std::ostream &os, int indentation = 0) const;

    ~AssignmentExpr();
};

class BinaryExpr : public Expr {
   private:
    Expr *left;
    Expr *right;
    std::string op;

   public:
    BinaryExpr();
    BinaryExpr(std::string op, Expr *left, Expr *right);

    Expr *getLeft() const;
    Expr *getRight() const;
    std::string getOp() const;

    void print(std::ostream &os, int indentation = 0) const;

    ~BinaryExpr();
};

class BooleanExpr : public Expr {
   private:
   public:
    BooleanExpr();

    void print(std::ostream &os, int indentation = 0) const;

    ~BooleanExpr();
};

class LogicalExpr : public Expr {
   private:
    Expr *left;
    Expr *right;
    std::string op;

   public:
    LogicalExpr();
    LogicalExpr(std::string op, Expr *left, Expr *right);

    Expr *getLeft() const;
    Expr *getRight() const;
    std::string getOp() const;

    void print(std::ostream &os, int indentation = 0) const;

    ~LogicalExpr();
};

class CallExpr : public Expr {
   private:
    std::vector<Expr *> args;
    Expr *caller;

   public:
    CallExpr();
    CallExpr(Expr *caller, std::vector<Expr *> args);

    std::vector<Expr *> getArgs() const;
    Expr *getCaller() const;

    void print(std::ostream &os, int indentation = 0) const;

    ~CallExpr();
};

class MemberExpr : public Expr {
   private:
    Expr *object;
    Expr *property;
    bool computed;

   public:
    MemberExpr();
    MemberExpr(Expr *object, Expr *property, bool computed);

    Expr *getObject() const;
    Expr *getProperty() const;
    bool getComputed() const;

    void print(std::ostream &os, int indentation = 0) const;

    ~MemberExpr();
};

class IfExpr : public Expr {
   private:
    std::unordered_map<Expr *, std::vector<Stmt *>> cases;
    std::vector<Stmt *> elseCase;
    bool hasElse;

   public:
    IfExpr();
    IfExpr(std::unordered_map<Expr *, std::vector<Stmt *>> cases);
    IfExpr(std::unordered_map<Expr *, std::vector<Stmt *>> cases, std::vector<Stmt *> elseCase);

    std::unordered_map<Expr *, std::vector<Stmt *>> getCases() const;
    std::vector<Stmt *> getElseCase() const;
    bool getHasElse() const;

    void print(std::ostream &os, int indentation = 0) const;

    ~IfExpr();
};

class ForVariablesInfo {
   private:
    TokenType type;
    int start;
    int step;

   public:
    ForVariablesInfo() {}
    ForVariablesInfo(TokenType type, int start, int step) : type(type), start(start), step(step) {}

    TokenType getType() const { return type; }
    int getStart() const { return start; }
    int getStep() const { return step; }
};
class ForExpr : public Expr {
   private:
    std::unordered_map<std::string, ForVariablesInfo> variables;
    Expr *condition;
    std::vector<BinaryExpr *> iterExprs;
    std::vector<Stmt *> body;
    bool isForEach;

   public:
    ForExpr();
    ForExpr(std::unordered_map<std::string, ForVariablesInfo> variables, Expr *condition, std::vector<BinaryExpr *> iterExprs, std::vector<Stmt *> body, bool isForEach = false);

    std::unordered_map<std::string, ForVariablesInfo> getVariables() const;
    Expr *getCondition() const;
    std::vector<BinaryExpr *> getIterExprs() const;
    std::vector<Stmt *> getBody() const;
    bool getIsForEach() const;

    void print(std::ostream &os, int indentation = 0) const;

    ~ForExpr();
};

class WhileExpr : public Expr {
   private:
    Expr *condition;
    std::vector<Stmt *> body;

   public:
    WhileExpr();
    WhileExpr(Expr *condition, std::vector<Stmt *> body);

    Expr *getCondition() const;
    std::vector<Stmt *> getBody() const;

    void print(std::ostream &os, int indentation = 0) const;

    ~WhileExpr();
};

#endif  // EXPRS_H
