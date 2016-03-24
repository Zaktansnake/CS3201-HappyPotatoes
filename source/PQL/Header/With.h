#pragma once
#include <string>
#include "Clause.h"

using namespace std;
typedef string LeftSide;
typedef string RightSide;

class With {
public:
	// getters
	Clause getNormalClause();
	LeftSide getLeftOfEqualSign();
	RightSide getRightOfEqualSign();

	// constructors
	With();
	With(Clause, LeftSide, RightSide);

private:
	Clause normalClause_;
	LeftSide leftOfEqualSign_;
	RightSide rightOfEqualSign_;
};