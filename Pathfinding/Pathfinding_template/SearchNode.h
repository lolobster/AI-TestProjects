#ifndef SEARCHNODE_H
#define SEARCHNODE_H
#include "vec2.h"
#include <algorithm>

typedef std::pair<int, int>Position;

class SearchNode
{
public:
	SearchNode(const Position& currentPosition, float _H, float deltaG, SearchNode* prev)
		: prevNode(0), pos(currentPosition), G(0), H(_H)
	{
		resetPrev(prev, deltaG);
	}
	~SearchNode();

	float getDistance() const;
	// Calculate total G for this node from previous node G value. Also calculates new F from new G and H.
	void resetPrev(SearchNode* prev, float deltaG);

	SearchNode* prevNode;  // Tells us the node, where we arrived to this node (previous/parent node)
	Position pos;		   // x and y position in the map
	float G;			   // Actual distance from the beginning point (A)
	float H;			   // Estimated heuristic distance to end point (B)
	float F;			   // G + H

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