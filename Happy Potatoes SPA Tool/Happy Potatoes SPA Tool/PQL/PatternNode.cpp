#include "./Header/PatternNode.h"

PatternNode PatternNode::getLeftChild() { return *left_; }
PatternNode PatternNode::getRightChild() { return *right_; }
PatternNode PatternNode::getParent() { return *parent_; }
string PatternNode::getContent() { return content_; }

void PatternNode::setParent(PatternNode *node) { parent_ = node; }
void PatternNode::setLeftChild(PatternNode *node) { left_ = node; }
void PatternNode::setRightChild(PatternNode *node) { right_ = node; }
void PatternNode::setContent(string content) { content_ = content; }

PatternNode::PatternNode() {}

PatternNode::PatternNode(string content) {
	content_ = content;
	parent_ = nullptr;
	left_ = nullptr;
	right_ = nullptr;
}