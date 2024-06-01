#pragma once

#include "../environment.h"

#include "../../ast/functionDeclaration.h"
#include "../../types/valueTypes.h"

RuntimeVal* evaluateFunctionDeclaration(FunctionDeclaration* declaration, Environment* env);