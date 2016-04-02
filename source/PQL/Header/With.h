#pragma once
#include <string>
#include "Clause.h"

using namespace std;
typedef string LeftSide;
typedef string RightSide;

class With {
public:
	// getters
	LeftSide getLeftOfEqualSign();
	RightSide getRightOfEqualSign();

	// constructors
	With();
	With(LeftSide, RightSide);

private:
	LeftSide leftOfEqualSign_;
	RightSide rightOfEqualSign_;
};