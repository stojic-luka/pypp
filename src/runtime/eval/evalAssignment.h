#pragma once

#include "../environment.h"

#include "../../exprs/assignmentExpr.h"
#include "../../types/valueTypes.h"

RuntimeVal* evaluateAssignment(AssignmentExpr* node, Environment* env);