#pragma once

#include "../environment.h"

#include "../../exprs/callExpr.h"
#include "../../types/valueTypes.h"

RuntimeVal* evaluateCallExpr(CallExpr* expr, Environment* env);