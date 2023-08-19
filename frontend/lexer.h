#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

class Token;

std::vector<Token> tokenize(std::string sourceCode);

#endif  // LEXER_H