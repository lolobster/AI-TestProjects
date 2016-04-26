#ifndef LOBSTERAI_HPP
#define LOBSTERAI_HPP

#include "GameEvents.h"
#include "PlayerController.h"

class LobsterAI
	: public CharacterController
{
public:
	LobsterAI(yam2d::GameObject* owner, GameController* gameController, BotType botType)
		: CharacterController(owner, gameController, botType)
		, m_distanceToDestination(0.0f)
		, m_collisionToHomeBase(false)
	{}
	virtual~LobsterAI(){}

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

	// This virtual method is automatically called by map/layer, when update is called from main.cpp
	virtual void update(float deltaTime)
	{


		// If has collided to with home base, drop bomb
		if (m_collisionToHomeBase)
		{
			// Only if I has flag
			if (hasItem())
				dropItem1();

			m_collisionToHomeBase = false;
		}
	}

	float getDistanceToDestination() const
	{
		return m_distanceToDestination;
	}

private:
	float m_distanceToDestination;
	bool m_collisionToHomeBase;
protected:
};

#endif