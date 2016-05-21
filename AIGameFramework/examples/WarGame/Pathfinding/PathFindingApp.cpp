#include "PathFindingApp.h"
#include <ElapsedTimer.h>


PathFindingApp::PathFindingApp()
{
	m_searchCompleted = false;
	m_searchTimer = 0.0f;
}

PathFindingApp::~PathFindingApp()
{
}

//void PathFindingApp::update(float deltaTime, const yam2d::vec2 startPos, const yam2d::GameObject* target)
//{
//	if (deltaTime > 0.1f)
//		deltaTime = 0.1f;
//
//	printf_s("Start finding path to target: %s\n", target->getName().c_str());
//
//	m_searchTimer = 0.0f;
//
//	m_searchCompleted = false;
//
//	if (!m_searchCompleted)
//	{
//		// Find start and end
//		
//		float startX, startY, endX, endY;
//		startX = startPos.x;
//		startY = startPos.y;
//		endX = target->getPosition().x;
//		endY = target->getPosition().y;
//
//		// Update path find!! Set m_searchCompleted to true, when path found, so the texture data is updated.
//		if (startX >= 0 && startY >= 0 && endX >= 0 && endY >= 0)
//		{
//			yam2d::ElapsedTimer timer;
//			timer.reset();
//			m_searchCompleted = doPathfinding(startX, startY, endX, endY);
//			m_searchTimer += timer.getTime();
//		}
//		else
//		{
//			assert(0);
//		}
//
//		if (m_searchCompleted)
//		{
//			printf_s("Pathfinding  done. Time spent %.3f seconds\n\n");
//		}
//	} // if (!m_searchCompleted)
//
//}

std::vector<slm::vec2> PathFindingApp::doPathfinding(float startX, float startY, float endX, float endY)
{
	bool done = true;
	std::vector<slm::vec2> targets;
	// Some variables for path finding
	OpenList openList;
	ClosedList closedList;
	SearchLevel searchLevel(mapLayer);
	SearchNode* result = 0;

	// Start A* search:
	// Add start node to open list
	Position startPosition = Position(startX, startY);
	Position endPosition = Position(endX, endY);
	SearchNode* newNode = new SearchNode(startPosition, searchLevel.GetH(startPosition, endPosition), 0, 0);
	openList.insertToOpenList(newNode);

	// 1. Get the square on the open list which has the lowest score. Let's call this square S (or prev).
	while (!openList.isEmpty())
	{
		SearchNode* prev = openList.RemoveSmallestFFromOpenList();
		if (prev->pos == endPosition)
		{
			// Goal found!
			printf("Goal found!\n\n");
			result = prev;
			break;
		}
		else
		{
			// 2.  Remove S from the open list and add S to the closed list.
			closedList.AddToClosedList(prev);

			// 3. for each square T in S's walkable adjacent tiles:
			std::vector<Position>adjacentNodes = searchLevel.GetAdjacentNodes(prev->pos.first, prev->pos.second);
			for (size_t i = 0; i < adjacentNodes.size(); ++i)
			{
				// If T is in the closed list, ignore it
				if (closedList.isInClosedList(adjacentNodes[i]))
					continue;

				SearchNode* n = openList.findFromOpenList(adjacentNodes[i]);
				if (n == 0)
				{
					// If T is not in the open list, add it and compute its score
					SearchNode* newNode = new SearchNode(adjacentNodes[i],
						searchLevel.GetH(adjacentNodes[i], endPosition),
						searchLevel.GetG(prev, adjacentNodes[i]), prev);
					openList.insertToOpenList(newNode);
				}
				else
				{
					// If T is already in the open list, check if the F score is lower
					// when we use the current generated path to get there. If it is,
					// update its score and update its parent as well.
					SearchNode* newNode = new SearchNode(adjacentNodes[i],
						searchLevel.GetH(adjacentNodes[i], endPosition),
						searchLevel.GetG(prev, adjacentNodes[i]), prev);
					if (n->distance() < newNode->distance())
					{
						n->resetPrev(newNode->prevNode, searchLevel.GetG(newNode->prevNode, n->pos));
					}
				}
			}
		}
	}

	if (result == 0)
	{
		printf_s("Path not found!!!\n");
		return targets;
	}
	while (result != 0)
	{
		printf_s("Path found!\n");
		result = result->prevNode;

		if (result != nullptr)
		{
			slm::vec2 target;

			target.x = result->pos.first;
			target.y = result->pos.second;
			targets.push_back(target);
		}
	}
	return  targets;
}

