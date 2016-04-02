#include "./Header/With.h"

LeftSide With::getLeftOfEqualSign() {
	return leftOfEqualSign_;
}
RightSide With::getRightOfEqualSign() {
	return rightOfEqualSign_;
}

With::With() {
}

With::With(LeftSide leftOfEqualSign, RightSide rightOfEqualSign) {
	leftOfEqualSign_ = leftOfEqualSign;
	rightOfEqualSign_ = rightOfEqualSign;
}