#pragma once

#include "../environment.h"

#include "../../ast/objectLiteral.h"
#include "../../types/valueTypes.h"

RuntimeVal* evaluateObjectExpr(ObjectLiteral* obj, Environment* env);