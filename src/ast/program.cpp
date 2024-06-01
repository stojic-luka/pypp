#include "program.h"

#include <iostream>

Program::Program() { kind = NodeType::Program; }
Program::Program(std::vector<Stmt*> body) : body(body) { kind = NodeType::Program; }

std::vector<Stmt*> Program::getBody() const { return body; }
void Program::bodyPush(Stmt* p) {
	body.push_back(p);
}

void Program::print(std::ostream& os, int indentation) const {
	os << "Program(\n";
	os << std::string(indentation + 1, '\t') << "Kind: " << this->getKind() << ",\n";
	if (this->getBody().size() == 0) {
		os << std::string(indentation + 1, '\t') << "Body: empty ]\n";
		return;
	}
	os << std::string(indentation + 1, '\t') << "Body: [\n";
	for (auto& item : this->getBody()) {
		os << std::string(indentation + 2, '\t');
		item->print(os, indentation + 2);
		os << std::endl;
	}
	os << std::string(indentation + 1, '\t') << "]\n";
}

Program::~Program() {
	//std::cout << this->body.size();
	//delete this->body.at(0);

	//std::cout << "Program destructor";

	for (Stmt* stmt : body)
		delete stmt;
	body.clear();
}