#pragma once

#include "../environment.h"

#include "../../exprs/ifExpr.h"
#include "../../types/valueTypes.h"

RuntimeVal* evaluateIfExpr(IfExpr* expr, Environment* env);