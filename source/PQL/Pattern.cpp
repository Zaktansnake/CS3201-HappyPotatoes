#include "./Header/Pattern.h"

PatternType Pattern::getPatternOperation() { 
	return patternType_; 
}
Parameter1 Pattern::getFirstParameter() { 
	return parameter1_; 
}
Parameter2 Pattern::getSecondParameter() { 
	return parameter2_; 
}
Parameter3 Pattern::getThirdParameter() { 
	return parameter3_; 
}

Pattern::Pattern() {
}

Pattern::Pattern(PatternType type, Parameter1 p1, Parameter2 p2) {
	patternType_ = type;
	parameter1_ = p1;
	parameter2_ = p2;
};

Pattern::Pattern(PatternType type, Parameter1 p1, Parameter2 p2, Parameter3 p3) {
	patternType_ = type;
	parameter1_ = p1;
	parameter2_ = p2;
	parameter3_ = p3;
}