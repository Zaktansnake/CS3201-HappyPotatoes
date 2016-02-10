#pragma once
#include <string>
using namespace std;

typedef string ClauseType;
typedef string Parameter1;
typedef string Parameter2;

class Clause {
public:
	ClauseType getClauseOperation();
	Parameter1 getFirstParameter(); 
	Parameter2 getSecondParameter();

	Clause();
	Clause(Parameter1 parameter1_, Parameter2 parameter2_);

private:
	ClauseType clauseOp_;
	Parameter1 parameter1_;
	Parameter2 parameter2_;
};