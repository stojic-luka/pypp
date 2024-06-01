#pragma once

#include "../environment.h"

#include "../../exprs/forExpr.h"
#include "../../types/valueTypes.h"

RuntimeVal* evaluateForExpr(ForExpr* expr, Environment* env);