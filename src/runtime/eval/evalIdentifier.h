#pragma once

#include "../environment.h"

#include "../../ast/identifier.h"
#include "../../types/valueTypes.h"

RuntimeVal* evaluateIdentifier(Identifier* ident, Environment* env);