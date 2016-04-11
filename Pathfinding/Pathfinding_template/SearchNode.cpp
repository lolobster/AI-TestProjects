#include "SearchNode.h"


SearchNode::~SearchNode()
{
}

void SearchNode::resetPrev(SearchNode* prev, float deltaG)
{
	prevNode = prev;
	if (prev == 0)
		G = 0.0f;
	else
		G = deltaG + prev->G;

	F=H+G;
}
