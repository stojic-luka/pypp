#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "frontend/ast.h"
#include "frontend/parser.h"
#include "globalVars.h"
#include "runtime/environment.h"
#include "runtime/interpreter.h"
#include "runtime/values.h"

std::string loadSourceCode(std::string fileName) {
    std::ifstream file(fileName);
    if (!file.is_open())
        std::runtime_error("Could not open file: " + fileName + "\n");
    file.seekg(-1, std::ios_base::end);
    char lastChar;
    file.get(lastChar);
    file.close();
    if (lastChar != '\n') {
        std::ofstream outFile(fileName, std::ios_base::app);
        outFile << '\n';
        outFile.close();
    }
    std::ifstream inputFile(fileName);
    std::string fileContent((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    return fileContent;
}

bool isDebug;

size_t allocatedMemory = 0;
void *operator new(std::size_t size) {
    std::cout << "allocating " << size << "bytes" << std::endl;
    allocatedMemory += size;
    return std::malloc(size);
}
void operator delete(void *memory, size_t size) {
    std::cout << "freeing " << size << "bytes" << std::endl;
    allocatedMemory -= size;
    std::free(memory);
}

int main(int argc, char *argv[]) {
    std::string fileName;
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--debug")
            isDebug = true;
        else
            fileName = std::string(argv[i]);
    }

    // std::cout << std::setprecision(20);

    Parser parser = Parser();
    Program *program = parser.produceAST(loadSourceCode(fileName));
    Environment *env = Environment::createGlobalEnv();
    evaluate(program, env);

    // std::cout << *program << std::endl;
    // std::cout << *env << std::endl;

    delete program;
    delete env;

    std::cout << "memory: " << allocatedMemory << std::endl;

    return 0;
}
