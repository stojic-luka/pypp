#pragma once

#include "../environment.h"

#include "../../exprs/memberExpr.h"
#include "../../types/valueTypes.h"

RuntimeVal* evaluateMemberExpr(MemberExpr* expr, Environment* env);