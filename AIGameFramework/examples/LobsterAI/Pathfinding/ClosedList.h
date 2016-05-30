#ifndef CLOSEDLIST_H
#define CLOSEDLIST_H
#include "SearchNode.h"
#include "vec2.h"
#include <map>
namespace LobsterAI
{
	class ClosedList
	{
	public:
		ClosedList();
		~ClosedList();

		void AddToClosedList(SearchNode* node);
		bool isInClosedList(const Position& pos);
		void clear();

	private:
		typedef std::map<Position, SearchNode*> ClosedListType;
		ClosedListType closedList;
	};
}
#endif