#pragma once

#include "../environment.h"

#include "../../ast/variableDeclaration.h"
#include "../../types/valueTypes.h"

RuntimeVal* evaluateVariableDeclaration(VariableDeclaration* declaration, Environment* env);