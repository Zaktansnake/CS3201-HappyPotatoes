#include <iostream>

class TNode
{
	friend class LinkedList;
private:
	int _value; /* data, can be any data type, but use integer for easiness */
	TNode *_pNext; /* pointer to the next node */

public:
	//setFirstChild
	//setLeftChild
	//setRightChild
	//setRightSibiling

	/* Constructors with No Arguments */
	TNode(void)
		: _pNext(NULL)
	{ }

	/* Constructors with a given value */
	TNode(int val)
		: _value(val), _pNext(NULL)
	{ }

	/* Constructors with a given value and a link of the next node */
	TNode(int val, TNode* next)
		: _value(val), _pNext(next)
	{}

	/* Getters */
	int getValue(void)
	{
		return _value;
	}

	TNode* getNext(void)
	{
		return _pNext;
	}
};