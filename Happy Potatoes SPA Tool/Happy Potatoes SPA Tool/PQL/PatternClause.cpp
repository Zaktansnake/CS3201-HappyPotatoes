#include "./Header/PatternClause.h"

PatternType PatternClause::getPatternOperation() { return patternType_; }
Parameter1 PatternClause::getFirstParameter() { return parameter1_; }
Parameter2 PatternClause::getSecondParameter() { return parameter2_; }
Parameter3 PatternClause::getThirdParameter() { return parameter3_; }

PatternClause::PatternClause() {};
PatternClause::PatternClause(Parameter1 p1, Parameter2 p2, Parameter3 p3) {
	parameter1_ = p1;
	parameter2_ = p2;
	parameter3_ = p3;
};
