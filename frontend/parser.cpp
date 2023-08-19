#include "parser.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "ast.h"
#include "exprs.h"
#include "lexer.h"
#include "tokenTypes.h"

bool Parser::not_eof() { return this->tokens[0].getType() != TokenType::Eof; }

Stmt *Parser::parseStmt() {
    switch (this->tokens[0].getType()) {
        case TokenType::Int:
        case TokenType::Float:
        case TokenType::Double:
        case TokenType::Bool:
        case TokenType::Char:
        case TokenType::String:
        case TokenType::Object:
        case TokenType::Func:
            return this->parseVariableDeclaration();
        case TokenType::FunctionDef:
            return this->parseFunctionDeclaration();
        default:
            return this->parseExpr();
    }
}

Token Parser::eat() {
    Token prev = this->tokens.front();
    this->tokens.erase(this->tokens.begin());
    return prev;
}

Token Parser::eat(TokenType type, std::string errMessage) {
    Token prev = tokens.front();
    if (prev.isEmpty() || prev.getType() != type)
        throw std::runtime_error(errMessage);
    tokens.erase(tokens.begin());
    return prev;
}
Token Parser::eat(const std::vector<TokenType> &types, std::string errMessage) {
    Token prev = tokens.front();
    bool isValid = false;
    for (auto const &type : types)
        if (prev.isEmpty() || prev.getType() != type)
            isValid = true;

    if (!isValid)
        throw std::runtime_error(errMessage);
    tokens.erase(tokens.begin());
    return prev;
}

Stmt *Parser::parseVariableDeclaration() {
    TokenType type = this->eat().getType();
    std::string identifier = this->eat(TokenType::Identifier, "Invalid identifier name!").getValue();

    bool isConst = true;
    for (char c : identifier)
        if (!std::isupper(c)) {
            isConst = false;
            break;
        }

    if (this->tokens[0].getType() == TokenType::LineEnd) {
        this->eat();
        if (isConst)
            throw std::runtime_error("Must assign value to const");
        return new VariableDeclaration(type, identifier, new Expr(), false);
    }
    this->eat(TokenType::Equals, "Expected equals token");

    VariableDeclaration *declaration = new VariableDeclaration(type, identifier, this->parseExpr(), isConst);
    this->eat(TokenType::LineEnd, "Every command must end with a new line!");
    return declaration;
}

Stmt *Parser::parseFunctionDeclaration() {
    this->eat();
    std::string name = this->eat(TokenType::Identifier, "Expected function name").getValue();

    std::unordered_map<TokenType, std::string> params;
    for (auto const &[type, param] : this->parseParams())
        params.insert({type, param});

    this->eat(TokenType::Arrow, "Expected arrow for declaring function return type");
    TokenType returnType = this->eat({TokenType::Int, TokenType::Float, TokenType::Double,
                                      TokenType::Bool, TokenType::Char, TokenType::String,
                                      TokenType::Object, TokenType::Func, TokenType::Void},
                                     "Expected a valid return type token")
                               .getType();

    this->eat(TokenType::OpenBrace, "Expected open brace");
    std::vector<Stmt *> body;
    while (this->tokens[0].getType() != TokenType::Eof && this->tokens[0].getType() != TokenType::CloseBrace)
        body.push_back(this->parseStmt());

    this->eat(TokenType::CloseBrace, "Expected close brace");
    return new FunctionDeclaration(returnType, name, params, body);
}

Expr *Parser::parseExpr() {
    return parseAssignmentExpr();
}

Expr *Parser::parseAssignmentExpr() {
    Expr *left = this->parseObjectExpr();
    if (this->tokens[0].getType() == TokenType::Equals) {
        this->eat();
        Expr *value = this->parseAssignmentExpr();
        return new AssignmentExpr(left, value);
    }
    return left;
}

Expr *Parser::parseObjectExpr() {
    if (this->tokens[0].getType() != TokenType::OpenBrace)
        return this->parseBooleanExpr();

    this->eat();
    std::vector<Property *> properties;

    while (this->not_eof() && this->tokens[0].getType() != TokenType::CloseBrace) {
        std::string key = this->eat(TokenType::Identifier, "Object literal key expected").getValue();
        this->eat(TokenType::Colon, "Missing colon following identifier in ObjectExpr");

        properties.push_back(new Property(key, this->parseExpr()));
        if (this->tokens[0].getType() != TokenType::CloseBrace)
            this->eat(TokenType::Comma, "Expected comma or closing bracket following property!");
    }

    this->eat(TokenType::CloseBrace, "Object literal missing closing brace!");
    return new ObjectLiteral(properties);
}

Expr *Parser::parseBooleanExpr() {
    Expr *left = parseLogicalExpr();
    return left;
}

Expr *Parser::parseLogicalExpr() {
    Expr *left = parseAdditiveExpr();
    while (this->tokens[0].getType() == TokenType::BooleanOperator)
        left = new LogicalExpr(eat().getValue(), left, parseAdditiveExpr());
    return left;
}

Expr *Parser::parseAdditiveExpr() {
    Expr *left = new NumericLiteral(0);
    if (this->tokens[0].getValue() != "-")
        left = parseMultiplicitaveExpr();
    while (this->tokens[0].getValue() == "+" || this->tokens[0].getValue() == "-")
        left = new BinaryExpr(eat().getValue(), left, parseMultiplicitaveExpr());
    return left;
}

Expr *Parser::parseMultiplicitaveExpr() {
    Expr *left = parseExponentionalExpr();
    while (this->tokens[0].getValue() == "/" || this->tokens[0].getValue() == "*" || this->tokens[0].getValue() == "%")
        left = new BinaryExpr(eat().getValue(), left, parseExponentionalExpr());
    return left;
}

Expr *Parser::parseExponentionalExpr() {
    Expr *left = parseCallMemberExpr();
    while (this->tokens[0].getValue() == "^")
        left = new BinaryExpr(eat().getValue(), left, parseCallMemberExpr());
    return left;
}

Expr *Parser::parseCallMemberExpr() {
    Expr *member = this->parseMemberExpr();
    if (this->tokens[0].getType() == TokenType::OpenParam)
        return this->parseCallExpr(member);
    return member;
}

Expr *Parser::parseCallExpr(Expr *caller) {
    Expr *callExpr = new CallExpr(caller, this->parseArgs());
    if (this->tokens[0].getType() == TokenType::OpenParam)
        callExpr = this->parseCallExpr(callExpr);
    return callExpr;
}

std::vector<Expr *> Parser::parseArgs() {
    this->eat(TokenType::OpenParam, "Expected open parenthesis!");
    std::vector<Expr *> args;
    if (this->tokens[0].getType() == TokenType::CloseParam)
        return args;

    args = this->parseArgList();
    this->eat(TokenType::CloseParam, "Missing closing parenthesis inside args list!");
    return args;
}

std::vector<Expr *> Parser::parseArgList() {
    std::vector<Expr *> args;
    args.push_back(this->parseExpr());
    while (this->not_eof() && this->tokens[0].getType() == TokenType::Comma)
        args.push_back(this->parseExpr());
    return args;
}

std::unordered_map<TokenType, std::string> Parser::parseParams() {
    this->eat(TokenType::OpenParam, "Expected open parenthesis!");
    std::unordered_map<TokenType, std::string> args;
    if (this->tokens[0].getType() == TokenType::CloseParam)
        return args;

    args = this->parseParamList();
    this->eat(TokenType::CloseParam, "Missing closing parenthesis inside args list!");
    return args;
}

std::unordered_map<TokenType, std::string> Parser::parseParamList() {
    std::unordered_map<TokenType, std::string> args;
    do {
        if (this->tokens[0].getType() == TokenType::Comma)
            this->eat();

        args.insert({this->eat({TokenType::Int, TokenType::Float, TokenType::Double,
                                TokenType::Bool, TokenType::Char, TokenType::String,
                                TokenType::Object, TokenType::Func},
                               "Invalid function param type")
                         .getType(),
                     this->eat(TokenType::Identifier, "Expected identifier after param type").getValue()});
    } while (this->not_eof() && this->tokens[0].getType() == TokenType::Comma);
    return args;
}

Expr *Parser::parseMemberExpr() {
    Expr *object = this->parseIfExpr();
    while (this->tokens[0].getType() == TokenType::Dot || this->tokens[0].getType() == TokenType::OpenBracket) {
        Token const op = this->eat();
        Expr *property;
        bool computed;

        if (op.getType() == TokenType::Dot) {
            computed = false;
            property = this->parseIfExpr();
            if (property->getKind() != NodeType::Identifier)
                throw std::runtime_error("Cannot use dot operator without right hand side being an identifier");
        } else {
            computed = true;
            property = this->parseExpr();
            this->eat(TokenType::CloseBracket, "Missing closing bracket in computed value");
        }

        object = new MemberExpr(object, property, computed);
    }
    return object;
}

Expr *Parser::parseIfExpr() {
    if (this->tokens[0].getType() != TokenType::If)
        return this->parseForExpr();

    this->eat();
    Expr *ifCondition = this->parseBooleanExpr();
    this->eat(TokenType::OpenBrace, "exected open brace on if");

    std::vector<Stmt *> ifStmts;
    std::vector<std::string> condCheck;

    while (this->tokens[0].getType() != TokenType::Eof &&
           this->tokens[0].getType() != TokenType::CloseBrace &&
           this->tokens[0].getType() != TokenType::Elif &&
           this->tokens[0].getType() != TokenType::Else)
        ifStmts.push_back(this->parseStmt());
    this->eat(TokenType::CloseBrace, "exected close brace on in");

    std::unordered_map<Expr *, std::vector<Stmt *>> cases;

    cases.insert({ifCondition, ifStmts});

    while (this->tokens[0].getType() != TokenType::Eof &&
           this->tokens[0].getType() == TokenType::Elif &&
           this->tokens[0].getType() != TokenType::Else) {
        this->eat();
        Expr *elifCondition = this->parseBooleanExpr();

        this->eat(TokenType::OpenBrace, "exected open brace on elif");
        std::vector<Stmt *> elifStmts;

        while (this->tokens[0].getType() != TokenType::Eof &&
               this->tokens[0].getType() != TokenType::CloseBrace)
            elifStmts.push_back(this->parseStmt());

        this->eat(TokenType::CloseBrace, "exected close brace on elif");

        cases.insert({elifCondition, elifStmts});
    }

    if (this->tokens[0].getType() == TokenType::Else) {
        this->eat();
        this->eat(TokenType::OpenBrace, "exected open brace on else");

        std::vector<Stmt *> elseCase;
        while (this->tokens[0].getType() != TokenType::Eof &&
               this->tokens[0].getType() != TokenType::CloseBrace)
            elseCase.push_back(this->parseStmt());
        this->eat(TokenType::CloseBrace, "exected close brace on else");

        return new IfExpr(cases, elseCase);
    }

    return new IfExpr(cases);
}

Expr *Parser::parseForExpr() {
    if (this->tokens[0].getType() != TokenType::For)
        return this->parseWhileExpr();

    std::unordered_map<std::string, ForVariablesInfo> variables;
    this->eat();
    std::vector<Stmt *> variableNames;
    do {
        TokenType type = this->eat().getType();
        std::string identifier = this->eat(TokenType::Identifier, "Invalid identifier name in for loop!").getValue();
        this->eat(TokenType::Equals, "Expected equals token when initializing variables in for loop");
        this->parseExpr();
    } while (this->tokens[0].getType() != TokenType::Comma);

    std::vector<Stmt *> body;
    while (this->tokens[0].getType() != TokenType::Eof &&
           this->tokens[0].getType() != TokenType::CloseBrace)
        body.push_back(this->parseStmt());

    return new ForExpr();
}

Expr *Parser::parseWhileExpr() {
    if (this->tokens[0].getType() != TokenType::While)
        return this->parsePrimaryExpr();

    this->eat();
    this->eat(TokenType::OpenParam, "Exected open param on while expr");
    Expr *condition = this->parseExpr();
    this->eat(TokenType::CloseParam, "Exected close param on while expr");
    this->eat(TokenType::OpenBrace, "Exected open brace on while expr");

    std::vector<Stmt *> body;
    while (this->tokens[0].getType() != TokenType::Eof &&
           this->tokens[0].getType() != TokenType::CloseBrace)
        body.push_back(this->parseStmt());

    this->eat(TokenType::CloseBrace, "Exected close brace on while expr");

    return new WhileExpr(condition, body);
}

Expr *Parser::parsePrimaryExpr() {
    TokenType tk = this->tokens[0].getType();
    switch (tk) {
        case TokenType::Identifier:
            return new Identifier(this->eat().getValue());
        case TokenType::Number:
            return new NumericLiteral(std::stod(this->eat().getValue()));
        case TokenType::Character:
        case TokenType::Characters:
            return new CharactersLiteral(this->eat().getValue(), tk == TokenType::Characters);
        case TokenType::OpenParam: {
            this->eat();
            Expr *value = this->parseExpr();
            this->eat(TokenType::CloseParam, "Not all open params are closed!");
            return value;
        }
        default: {
            std::cout << std::endl;
            std::cout << this->tokens[0];
            throw std::runtime_error("Unexpected token found during parsing!");
        }
    }
}

Program *Parser::produceAST(std::string sourceCode) {
    this->tokens = tokenize(sourceCode);
    Program *program = new Program();

    // for (auto const &token : this->tokens)
    //     std::cout << token;

    while (this->not_eof())
        program->bodyPush(this->parseStmt());
    return program;
}