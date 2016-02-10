//http://www.bogotobogo.com/cplusplus/linkedlist.php

#include "./Header/TNode.h"

#include <iostream>
#include <cstddef>

using std::cout;
using std::endl;

class TNode
{
	friend class LinkedList;
private:
	int _value; /* data, can be any data type, but use integer for easiness */
	TNode *_pNext; /* pointer to the next node */

public:
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

/* definition of the linked list class */
class LinkedList
{
private:
	/* pointer of head node */
	TNode *_pHead;
	/* pointer of tail node */
	TNode *_pTail;

public:
	/* Constructors with No Arguments */
	LinkedList(void);
	/* Constructors with a given value of a list node */
	LinkedList(int val);
	/* Destructor */
	~LinkedList(void);

	/* Traversing the list and printing the value of each node */
	void traverse_and_print();
};

LinkedList::LinkedList()
{
	/* Initialize the head and tail node */
	_pHead = _pTail = NULL;
}

LinkedList::LinkedList(int val)
{
	/* Create a new node, acting as both the head and tail node */
	_pHead = new TNode(val);
	_pTail = _pHead;
}

LinkedList::~LinkedList()
{
	/*
	* Leave it empty temporarily.
	* It will be described in detail in the example "How to delete a linkedlist".
	*/
}




