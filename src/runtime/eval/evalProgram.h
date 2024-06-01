#pragma once

#include "../environment.h"

#include "../../ast/program.h"
#include "../../types/valueTypes.h"

RuntimeVal* evaluateProgram(Program* program, Environment* env);