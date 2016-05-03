#ifndef PATHFINDING_APP_H_
#define PATHFINDING_APP_H_
#include <Object.h>
#include <es_util.h>
#include "OpenList.h"
#include "ClosedList.h"
#include "SearchLevel.h"

class LobsterAI;

class PathFindingApp : public yam2d::Object
{
// Public typedefs and methods:
public:
	PathFindingApp();
	virtual ~PathFindingApp();

	// Updates the app
	void update(float deltaTime, const yam2d::GameObject* target);

	// Draws the app
	void render(yam2d::ESContext *ctx);

// Private member variables and methods:
private:
	LobsterAI *lobAI;
	
	bool m_searchCompleted;
	float m_searchTimer;

	bool doPathfinding(float startX, float startY, float endX, float endY);

	// Hidden copy constructor and assignment operator.
	PathFindingApp(const PathFindingApp&);
	PathFindingApp& operator=(const PathFindingApp&);
};

#endif

