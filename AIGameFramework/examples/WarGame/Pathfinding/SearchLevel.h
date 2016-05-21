#ifndef SEARCHLEVEL_H
#define SEARCHLEVEL_H
#include "Searchnode.h"
#include <vector>
#include "AIMapLayer.h"
#include "Layer.h"

class SearchLevel
{
public:
	SearchLevel(AIMapLayer *layer) : AIlayer(layer){};
	~SearchLevel(){};

	float GetG(SearchNode* fromNode, const Position& toPos);
	float GetH(const Position& fromPos, const Position& toPos);
	bool isWalkable(int x, int y);
	
	std::vector<Position> GetAdjacentNodes(int posX, int posY);

private:
	AIMapLayer *AIlayer;
};

#endif