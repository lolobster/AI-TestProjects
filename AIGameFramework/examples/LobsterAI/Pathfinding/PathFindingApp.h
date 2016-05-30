#ifndef PATHFINDING_APP_H_
#define PATHFINDING_APP_H_
#include <Object.h>
#include <GameObject.h>
#include <GameEnvironmentInfoProvider.h>
#include <es_util.h>
#include "OpenList.h"
#include "ClosedList.h"
#include "SearchLevel.h"
class GameEnvironmentInfoProvider;
namespace LobsterAI
{
	class PathFindingApp : public yam2d::Object
	{
		// Public typedefs and methods:
	public:
		PathFindingApp();
		virtual ~PathFindingApp();
		std::vector<slm::vec2> doPathfinding(float startX, float startY, float endX, float endY);
		// Updates the app
		//void update(float deltaTime, const yam2d::vec2 startPos, const yam2d::GameObject* target);
		void setMapLayer(AIMapLayer* layer)
		{
			mapLayer = layer;

		}
		void setEnvironmentInfo(GameEnvironmentInfoProvider* envInfo)
		{
			environmentInfo = envInfo;
		}
		GameEnvironmentInfoProvider* getEnvironmentInfo(){ return environmentInfo; }
		// Private member variables and methods:
	private:
		AIMapLayer* mapLayer;
		GameEnvironmentInfoProvider* environmentInfo;
		bool m_searchCompleted;
		float m_searchTimer;

		// Hidden copy constructor and assignment operator.
		PathFindingApp(const PathFindingApp&);
		PathFindingApp& operator=(const PathFindingApp&);
	};
}
#endif