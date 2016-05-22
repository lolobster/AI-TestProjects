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
		, homeBase(0)
		, enemyBase(0)
		, m_reachTolerance(0.0f)
		, m_distanceToDestination(0.0f)
		, m_collisionToHomeBase(false)
		, m_startPos(0.0f, 0.0f)
		, AIObject(owner)
		, shootTarget(0)
		, m_predictionDistance(0.0f)
		, m_aimTolerance(0.0f)
		, player(0)
		, newTarget(false)
	{
		m_startPos = owner->getPosition();
	}
	virtual~LobsterAI(){}

	yam2d::vec2 getStartPosition(){ return m_startPos; }

	virtual void onMessage(const std::string& msgName, yam2d::Object* eventObject)
	{
		setMyHomeBase();
		setEnemyBase();

		CollisionEvent* collisionEvent = dynamic_cast<CollisionEvent*>(eventObject);
		assert(collisionEvent != 0);
		assert(collisionEvent->getMyGameObject() == getGameObject());
		yam2d::GameObject* otherGo = collisionEvent->getOtherGameObject();
		std::string otherType = otherGo->getType();

		if (otherType == "HomeBase")
		{
			if (hasItem())
			{
				printf("Dropping bomb!\n\n");
				dropItem1();
				stop();
			}
		}
		if (otherType == "Dynamite")
		{
			// set new target to Enemy Base 
			printf("Reached Dynamite!\n\n");
			// also, actually PICK UP the bomb
			setMoveTargetObject(getEnemyBase(), 1.0f);
		}

		if (msgName == "TakingDamage")
		{
			// Shoot back
			printf("Taking damage!\n\n");
			//setShootTarget();
		}
		if (msgName == "ZeroHealth")
		{ 
			printf("A soldier died!\n\n");
		}

	}

	void setPlayerController(PlayerController* playerController)
	{
		player = playerController;
	}

	void setMyHomeBase()
	{
		homeBase = pApp->getEnvironmentInfo()->getMyHomeBase(player);
	}

	void setEnemyBase()
	{
		enemyBase = pApp->getEnvironmentInfo()->getEnemyHomeBase(player);
	}

	const yam2d::GameObject* getMyHomeBase()
	{
		return homeBase;
	}
	const yam2d::GameObject* getEnemyBase()
	{
		return enemyBase;
	}

	void clearTargets()
	{
		targets.clear();
	}

	void findPath()
	{
		if (newTarget)
		{
			targets = pApp->doPathfinding(AIObject->getPosition().x, AIObject->getPosition().y,
				m_gameObjectToGo->getPosition().x, m_gameObjectToGo->getPosition().y);
		}
		newTarget = false;
	}

	void setMoveTargetObject(const yam2d::GameObject* gameObjectToGo, float reachTolerance)
	{
		if (gameObjectToGo == 0)
		{
			resetMoveTargetObject();
			return;
		}
		if (m_gameObjectToGo != gameObjectToGo)
		{
			newTarget = true;
			m_gameObjectToGo = gameObjectToGo;
			m_reachTolerance = reachTolerance;
			findPath();
			m_distanceToDestination = slm::length(m_gameObjectToGo->getPosition() - getGameObject()->getPosition());
		}
		preferPickItem();

	}

	void resetMoveTargetObject()
	{
		newTarget = false;
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

			if (shootTarget != 0)
			{
				float rotation = shootTarget->getRotation();
				yam2d::vec2 enemyDir;
				enemyDir.x = cosf(rotation);
				enemyDir.y = sinf(rotation);
				autoUsePrimaryWeapon(shootTarget->getPosition() + m_predictionDistance * enemyDir, m_aimTolerance);
			}
		}
		if (m_distanceToDestination <= m_reachTolerance && !targets.empty())
			targets.pop_back();
	}

	void setShootTarget(yam2d::GameObject* targetToShoot, float predictionDistance, float aimTolerance)
	{
		shootTarget = targetToShoot;
		m_predictionDistance = predictionDistance;
		m_aimTolerance = aimTolerance;
	}

	void resetShootTarget()
	{
		shootTarget = 0;
		m_predictionDistance = 0.0f;
		m_aimTolerance = 0.0f;
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
	float m_predictionDistance;
	float m_aimTolerance;
	bool m_collisionToHomeBase;
	yam2d::vec2 m_startPos;
	std::vector<slm::vec2> targets;
	PathFindingApp * pApp;
	const yam2d::GameObject* homeBase;
	const yam2d::GameObject* enemyBase;
	const yam2d::GameObject* AIObject;
	const yam2d::GameObject* shootTarget;
	PlayerController* player;
	bool newTarget;
protected:
};

#endif