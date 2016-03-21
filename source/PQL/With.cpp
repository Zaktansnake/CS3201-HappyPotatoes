#include "./Header/With.h"

Clause With::getNormalClause() {
	return normalClause_;
}
LeftSide With::getLeftOfEqualSign() {
	return leftOfEqualSign_;
}
RightSide With::getRightOfEqualSign() {
	return rightOfEqualSign_;
}

With::With() {
}

With::With(Clause normalClause, LeftSide leftOfEqualSign, RightSide rightOfEqualSign) {
	normalClause_ = normalClause;
	leftOfEqualSign_ = leftOfEqualSign;
	rightOfEqualSign_ = rightOfEqualSign;
}