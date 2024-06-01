#include <iostream>
#include <fstream>
#include <sstream>

#include "src/parser/parser.h"
#include "src/utils/ArgsParser.h"
#include "src/ast/program.h"

#include "src/globalVals.h"
#include "src/runtime/environment.h"
#include "src/runtime/interpreter.h"
#include "src/types/valueTypes.h"

//size_t allocatedMemory = 0;

//void* operator new(std::size_t size) {
//    std::cout << "add " << size << std::endl;
//    return std::malloc(size);
//}
//void operator delete(void* memory, size_t size) {
//    std::cout << "free " << size << std::endl;
//    std::free(memory);
//}

std::string loadSource(std::string fileName) {
	std::ifstream file;
	file.open(fileName);
	if (fileName.empty()) {
		std::cerr << "No provided file name." << std::endl;
		return "";
	}
	if (!file.is_open()) {
		std::cerr << "Error opening file: " << fileName << std::endl;
		return "";
	}
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	return buffer.str();
}

int main(int argc, char* argv[]) {
	ArgsParser input(argc, argv);

	if (input.cmdOptionExists("--debug"))
		isDebug = true;
	
	const std::string& fileName = input.getCmdOption("-f");
	if (!fileName.empty()) {
		std::cerr << "" << fileName << std::endl;
		return -1;
	}

	std::string sourceCode = loadSource("main.pypp");
	//std::string sourceCode = loadSource(fileName);
	if (sourceCode.empty())
		return 0;

	Parser parser = Parser();
	Environment* env = Environment::createGlobalEnv();

	Program* program = parser.produceAST(sourceCode);
	evaluate(program, env);

	std::cout << *program;
	std::cout << *env;
	//std::cout << env->getVariables().size();

	delete program;
	delete env;

	return 0;
}