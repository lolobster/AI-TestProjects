#ifndef SEARCHLEVEL_H
#define SEARCHLEVEL_H
#include "Searchnode.h"
#include <vector>
#include "vec2.h"

class SearchLevel
{
public:
	SearchLevel();
	~SearchLevel();

	float GetG(SearchNode* fromPos, SearchNode* toPos);
	float GetH(SearchNode* fromPos, SearchNode* toPos);
	bool isWalkable(int x, int y);
	
	std::vector<slm::vec2> GetAdjacentNodes(int posX, int posY);
};

#endif