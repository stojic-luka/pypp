#pragma once

#include "../environment.h"

#include "../../exprs/whileExpr.h"
#include "../../types/valueTypes.h"

RuntimeVal* evaluateWhileExpr(WhileExpr* expr, Environment* env);