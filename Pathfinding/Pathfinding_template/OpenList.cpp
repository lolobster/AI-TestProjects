#include "OpenList.h"


OpenList::OpenList()
{
}


OpenList::~OpenList()
{
}
// Returns search node from given position, if it exists. Else return 0;
SearchNode* OpenList::findFromOpenList(const Position &pos)
{
	for (size_t i = 0; i < openList.size(); i++)
	{
		if (openList[i]->pos == pos)
			return openList[i];
	}
	return 0;
}
//insert new SearchNode to open list and sort the list according to F.
void OpenList::insertToOpenList(SearchNode* n)
{
	openList.push_back(n);
	SortOpenList();
}

void OpenList::SortOpenList()
{
	std::sort(openList.begin(), openList.end(), &SearchNode::lessThan);
}

SearchNode* OpenList::RemoveSmallestFFromOpenList()
{
	SearchNode* result = *(openList.end() - 1); // Take last one
	openList.pop_back(); // Remove last element
	return result;
}

bool OpenList::isEmpty()
{
	return openList.empty();
}

void OpenList::clear()
{
	openList.clear();
}