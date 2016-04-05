#ifndef SEARCHNODE_H
#define SEARCHNODE_H
#include "vec2.h"
#include <algorithm>

typedef std::pair<int, int>Position;

class SearchNode
{
public:
	SearchNode(slm::vec2 curPos, float h, float deltaG, SearchNode* prev)
		: prevNode(0), pos(currentPosition), G(0), H(_H)
	{
		resetPrev(prev, deltaG);
	}
	~SearchNode();

	float getDistance() const;
	void resetPrev(SearchNode* prev, float deltaG);

	SearchNode* prevNode;
	Position pos;
	float G;
	float H;
	float F;

	float distance() const 
	{
		return F;
	}
	static bool lessThan(SearchNode* n1, SearchNode* n2)
	{
		return n1->distance() > n2->distance();
	}
};

#endif