#pragma once
#include <string>
using namespace std;

class PatternNode {
public:
	// getters
	PatternNode getLeftChild();
	PatternNode getRightChild();
	PatternNode getParent();
	string getContent();

	// setters
	void setParent(PatternNode *node);
	void setLeftChild(PatternNode *node);
	void setRightChild(PatternNode *node);
	void setContent(string content);

	// constructors
	PatternNode();
	PatternNode(string content);

private:
	PatternNode *parent_, *left_, *right_;
	string content_;
};
