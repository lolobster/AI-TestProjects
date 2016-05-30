#ifndef OPENLIST_H
#define OPENLIST_H
#include "vec2.h"
#include "SearchNode.h"
#include <vector>
namespace LobsterAI
{
	class OpenList
	{
	public:
		OpenList();
		~OpenList();

		SearchNode* findFromOpenList(const Position& pos);
		void insertToOpenList(SearchNode* n);
		void SortOpenList();
		SearchNode* RemoveSmallestFFromOpenList();
		bool isEmpty();
		void clear();

	private:
		typedef std::vector<SearchNode*>OpenListType;
		OpenListType openList;
	};
}
#endif