#include "Pattern.h"
#include "PatternNode.h"

PatternNode Pattern::getRoot() { return root_; }

Pattern::Pattern() {}

Pattern::Pattern(string content) {
	root_ = (PatternNode) nullptr;
	root_.setContent(content);
}