#include "functionDeclaration.h"

FunctionDeclaration::FunctionDeclaration() : isConst(nullptr), isLambda(nullptr), returnType(TokenType::None) { kind = NodeType::FunctionDeclaration; }
FunctionDeclaration::FunctionDeclaration(TokenType returnType, std::string name, std::unordered_map<TokenType, std::string> parameters, std::vector<Stmt*> body, bool isConst, bool isLambda) {
    kind = NodeType::FunctionDeclaration;
    this->returnType = returnType;
    this->name = name;
    this->parameters = parameters;
    this->body = body;
    this->isConst = isConst;
    this->isLambda = isLambda;
}

TokenType FunctionDeclaration::getReturnType() const { return returnType; }
std::string FunctionDeclaration::getName() const { return name; }
std::unordered_map<TokenType, std::string> FunctionDeclaration::getParameters() const { return parameters; }
std::vector<Stmt*> FunctionDeclaration::getBody() const { return body; }
bool FunctionDeclaration::getIsConst() const { return isConst; }
bool FunctionDeclaration::getIsLambda() const { return isLambda; }

void FunctionDeclaration::print(std::ostream& os, int indentation) const {
    os << "FunctionDeclaration(\n";
    os << std::string(indentation + 1, '\t') << "Kind: " << this->getKind() << ",\n";
    os << std::string(indentation + 1, '\t') << "Type: " << this->getReturnType() << ",\n";
    os << std::string(indentation + 1, '\t') << "Name: '" << this->getName() << "',\n";

    os << std::string(indentation + 1, '\t') << "Parameters: [";
    // for (const auto &item : this->getParameters())
    //     os << std::string(indentation + 2, '\t') << "" << item << ",\n";
    os << "],\n";

    os << std::string(indentation + 1, '\t') << "Body: [";
    for (const auto& item : this->getBody())
        item->print(os, indentation + 2);
    os << "],\n";

    os << std::string(indentation + 1, '\t') << "IsConst: " << (this->getIsConst() ? "True" : "False") << " )\n";
    os << std::string(indentation + 1, '\t') << "IsLambda: " << (this->getIsLambda() ? "True" : "False") << " )\n";
}

FunctionDeclaration::~FunctionDeclaration() {
    for (Stmt* stmt : body)
        delete stmt;
    body.clear();
}