#include "Clause.h"

ClauseType Clause::getClauseOperation() { return clauseOp_; }
Parameter1 Clause::getFirstParameter() { return parameter1_; }
Parameter2 Clause::getSecondParameter() { return parameter2_; }

Clause::Clause() {}
Clause::Clause(Parameter1 p1, Parameter2 p2) {
	parameter1_ = p1;
	parameter2_ = p2;
}