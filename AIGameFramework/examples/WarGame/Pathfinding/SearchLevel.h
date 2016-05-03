#ifndef SEARCHLEVEL_H
#define SEARCHLEVEL_H
#include "Searchnode.h"
#include <vector>
#include "Texture.h"
#include <StreamTexture.h>

class SearchLevel
{
public:
	SearchLevel(){}
	~SearchLevel(){};

	float GetG(SearchNode* fromNode, const Position& toPos);
	float GetH(const Position& fromPos, const Position& toPos);
	bool isWalkable(int x, int y);
	
	std::vector<Position> GetAdjacentNodes(int posX, int posY);

private:
};

#endif