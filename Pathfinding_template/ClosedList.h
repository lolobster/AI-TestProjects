#ifndef CLOSEDLIST_H
#define CLOSEDLIST_H
#include "SearchNode.h"
#include "vec2.h"

class ClosedList
{
public:
	ClosedList();
	~ClosedList();

	void AddToClosedList(SearchNode* n);
	bool isInClosedList(slm::vec2 pos);
	void clear();
};

#endif