#ifndef LOBSTERAI_HPP
#define LOBSTERAI_HPP

#include "GameEvents.h"
#include "PlayerController.h"
#include "Pathfinding\PathFindingApp.h"

class LobsterAI
	: public CharacterController
{
public:
	LobsterAI(yam2d::GameObject* owner, GameController* gameController, BotType botType)
		: CharacterController(owner, gameController, botType)
		, m_gameObjectToGo(0)
		, m_reachTolerance(0.0f)
		, m_distanceToDestination(0.0f)
		, m_collisionToHomeBase(false)
		, m_startPos(0.0f, 0.0f)
		, AIObject(owner)
	{
		m_startPos = owner->getPosition();
	}
	virtual~LobsterAI(){}

	yam2d::vec2 getStartPosition(){ return m_startPos; }

	virtual void onMessage(const std::string& msgName, yam2d::Object* eventObject)
	{
		CollisionEvent* collisionEvent = dynamic_cast<CollisionEvent*>(eventObject);
		assert(collisionEvent != 0);
		assert(collisionEvent->getMyGameObject() == getGameObject());
		yam2d::GameObject* otherGo = collisionEvent->getOtherGameObject();
		std::string otherType = otherGo->getType();
		if (otherType == "HomeBase")
		{
			if (hasItem())
				dropItem1();
		}
	}

	void setMyHomeBase(GameEnvironmentInfoProvider* environmentInfo, PlayerController* player)
	{
		homeBase = environmentInfo->getMyHomeBase(player);
	}

	const yam2d::GameObject* getMyHomeBase()
	{
		return homeBase;
	}

	void clearTargets()
	{
		targets.clear();
	}

	void findPath()
	{
		targets = pApp->doPathfinding(AIObject->getPosition().x, AIObject->getPosition().y,
			m_gameObjectToGo->getPosition().x, m_gameObjectToGo->getPosition().y);
	}

	void setMoveTargetObject(const yam2d::GameObject* gameObjectToGo, float reachTolerance)
	{
		if (gameObjectToGo == 0)
		{
			resetMoveTargetObject();
			return;
		}

		m_gameObjectToGo = gameObjectToGo;
		m_reachTolerance = reachTolerance;
		findPath();
		m_distanceToDestination = slm::length(m_gameObjectToGo->getPosition() - getGameObject()->getPosition());
		preferPickItem();
	}

	void resetMoveTargetObject()
	{
		m_gameObjectToGo = 0;
		m_reachTolerance = 0.0f;
		m_distanceToDestination = 0.0f;
		stop();
	}

	// This virtual method is automatically called by map/layer, when update is called from main.cpp
	virtual void update(float deltaTime)
	{
		CharacterController::update(deltaTime);

		if (m_gameObjectToGo != 0 && !targets.empty())
		{
			slm::vec2 position(targets.back().x, targets.back().y);
			m_distanceToDestination = moveDirectToPosition(position, m_reachTolerance);
			
			// If has collided with home base, drop bomb
			if (m_collisionToHomeBase)
			{
				// Only if I has flag
				if (hasItem())
					dropItem1();

				m_collisionToHomeBase = false;
			}
		}
		if (m_distanceToDestination <= m_reachTolerance && !targets.empty())
			targets.pop_back();
	}

	float getDistanceToDestination() const
	{
		return m_distanceToDestination;
	}

	void setApp(PathFindingApp* pathApp)
	{
		pApp = pathApp;
	}

private:
	const yam2d::GameObject* m_gameObjectToGo;
	float m_reachTolerance;
	float m_distanceToDestination;
	bool m_collisionToHomeBase;
	yam2d::vec2 m_startPos;
	std::vector<slm::vec2> targets;
	PathFindingApp * pApp;
	const yam2d::GameObject* homeBase;
	const yam2d::GameObject* AIObject;

protected:
};

#endif