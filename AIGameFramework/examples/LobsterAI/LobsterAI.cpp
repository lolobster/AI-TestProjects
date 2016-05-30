#include "CharacterController.h"
#include "PlayerController.h"
#include "GameEvents.h"
#include "Pathfinding\PathFindingApp.h"

namespace LobsterAI
{
	class LobsterAIController : public CharacterController
	{
	public:
		LobsterAIController(yam2d::GameObject* owner, GameController* gameController, BotType botType)
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
			, isDefending(false)
		{
			m_startPos = owner->getPosition();
		}

		virtual ~LobsterAIController(void)
		{
		}

		yam2d::vec2 getStartPosition(){ return m_startPos; }

		virtual void onMessage(const std::string& msgName, yam2d::Object* eventObject)
		{
			CharacterController::onMessage(msgName, eventObject);

			setMyHomeBase();
			setEnemyBase();
			if (msgName == "Collision")
			{
				CollisionEvent* collisionEvent = dynamic_cast<CollisionEvent*>(eventObject);
				assert(collisionEvent != 0);
				assert(collisionEvent->getMyGameObject() == getGameObject());
				yam2d::GameObject* otherGo = collisionEvent->getOtherGameObject();
				std::string otherType = otherGo->getType();

				if (otherType == "HomeBase")
				{
					if (!isDefending)
					{
						stop();
						resetMoveTargetObject();
						isDefending = true;
					}

					if (hasItem())
					{
						dropItem1();
					}
				}
				else if (otherType == "Dynamite")
				{
					// set new target to Enemy Base 
					printf("Reached Dynamite!\n\n");
					preferPickItem();
					//resetMoveTargetObject();
					setMoveTargetObject(getEnemyBase(), 1.0f);
				}
			}
			else if (msgName == "TakingDamage")
			{
				// Shoot back
				printf("Taking damage!\n\n");
				//setShootTarget();
			}
			else if (msgName == "ZeroHealth")
			{
				printf("A soldier died!\n\n");
			}
			else if (msgName == "ItemPicked")
				setMoveTargetObject(getEnemyBase(), 1.0f);

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

		void findPath()
		{
			if (newTarget)
			{
				targets = pApp->doPathfinding(AIObject->getPosition().x, AIObject->getPosition().y,
					m_gameObjectToGo->getPosition().x, m_gameObjectToGo->getPosition().y);
			}
			newTarget = false;
			printf_s("Path found!\n");
		}

		void setMoveTargetObject(const yam2d::GameObject* gameObjectToGo, float reachTolerance)
		{
			//preferPickItem();
			if (gameObjectToGo == 0)
			{
				resetMoveTargetObject();
				return;
			}
			else
			{
				newTarget = true;
				m_gameObjectToGo = gameObjectToGo;
				m_reachTolerance = reachTolerance;
				findPath();
				m_distanceToDestination = slm::length(m_gameObjectToGo->getPosition() - getGameObject()->getPosition());
				preferPickItem();

				if (m_distanceToDestination <= m_reachTolerance)
				{
					stop();
					resetMoveTargetObject();	
				}
			}
		}

		void resetMoveTargetObject()
		{
			newTarget = false;
			m_gameObjectToGo = 0;
			m_reachTolerance = 0.0f;
			m_distanceToDestination = 0.0f;
			stop();
			targets.clear();
		}

		// This virtual method is automatically called by map/layer, when update is called from main.cpp
		virtual void update(float deltaTime)
		{
			CharacterController::update(deltaTime);

			if (m_gameObjectToGo != 0 && !targets.empty())
			{
				slm::vec2 position(targets.back().x, targets.back().y);
				m_distanceToDestination = moveDirectToPosition(position, m_reachTolerance);
			}

			if (shootTarget != 0)
			{
				float rotation = shootTarget->getRotation();
				yam2d::vec2 enemyDir;
				enemyDir.x = cosf(rotation);
				enemyDir.y = sinf(rotation);
				autoUsePrimaryWeapon(shootTarget->getPosition() + m_predictionDistance * enemyDir, m_aimTolerance);
			}

			if (m_distanceToDestination <= m_reachTolerance && !targets.empty())
			{
				targets.pop_back();
			}
		}

		void setShootTarget(const yam2d::GameObject* targetToShoot, float predictionDistance, float aimTolerance)
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
		bool isDefending;
	};


	class LobsterAIPlayer : public PlayerController
	{
	private:
		std::string m_myTeamName;
		std::vector< yam2d::Ref<LobsterAIController> > m_controllers;
		PathFindingApp* app;

	public:
		LobsterAIPlayer()
			: PlayerController()
		{
			app = new PathFindingApp();
		}

		virtual ~LobsterAIPlayer()
		{
			delete app;
		}


		virtual void setMyTeamName(std::string& teamName)
		{
			m_myTeamName = teamName;
		}

		// Called, when bots are spawn. Shall return correct player character controller for bot if given name.
		virtual CharacterController* createPlayerCharacterController(GameController* gameController, yam2d::GameObject* ownerGameObject, const std::string& playerName, BotType type)
		{
			if (playerName == "LobsterAI")
			{
				LobsterAIController* myAI = new LobsterAIController(ownerGameObject, gameController, type);
				myAI->setApp(app);
				myAI->setPlayerController(this);
				m_controllers.push_back(myAI);

				return myAI;
			}

			return 0;
		}

		// Called, when bots have spawn. Can be used some custom initialization after spawn.
		virtual void onGameStarted(GameEnvironmentInfoProvider* environmentInfo)
		{
			yam2d::esLogMessage("onGameStarted");

			uint8_t RED_PIXEL[4] = { 0xff, 0x00, 0x00, 0xff };
			uint8_t GREEN_PIXEL[4] = { 0x00, 0xff, 0x00, 0xff };
			uint8_t BLUE_PIXEL[4] = { 0x00, 0x00, 0xff, 0xff };
			uint8_t TP_PIXEL[4] = { 0x00, 0x00, 0x00, 0x00 };  // TransParent

			AIMapLayer *AIMap = environmentInfo->getAILayer("GroundMoveSpeed");
			app->setMapLayer(AIMap);
			app->setEnvironmentInfo(environmentInfo);

			// Move bots
			const yam2d::GameObject* dynamite = environmentInfo->getDynamite();
			for (size_t i = 0; i < m_controllers.size(); ++i)
			{
				if (m_controllers[i]->isSoldier())
				{
					m_controllers[i]->preferPickItem();
					m_controllers[i]->setMoveTargetObject(dynamite, 0.2f);
				}
				else if (m_controllers[i]->isRobot())
					m_controllers[i]->setMoveTargetObject(environmentInfo->getMyHomeBase(this), 1.2f);
			}
		}


		// Called when game has ended. Can be used some cuystom deinitialization after game.
		virtual void onGameOver(GameEnvironmentInfoProvider* environmentInfo, const std::string& gameResultString)
		{
			yam2d::esLogMessage("onGameOver: %s wins!", gameResultString.c_str());
			for (size_t i = 0; i < m_controllers.size(); ++i)
			{
				m_controllers[i]->resetMoveTargetObject();
				m_controllers[i]->resetShootTarget();
			}
		}

		virtual void onUpdate(GameEnvironmentInfoProvider* environmentInfo, float deltaTime)
		{
		}

		virtual void onGameEvent(GameEnvironmentInfoProvider* environmentInfo, const std::string& eventName, yam2d::Object* eventObject)
		{
			if (eventName == "ItemPicked")
			{
				ItemEvent* itemEvent = dynamic_cast<ItemEvent*>(eventObject);
				assert(itemEvent != 0);
				yam2d::GameObject* item = itemEvent->getItemGameObject();
				int teamIndex = itemEvent->getCharacterGameObject()->getProperties()["teamIndex"].get<int>();

				if (teamIndex == getMyTeamIndex())
				{
					yam2d::esLogMessage("My team picked item. Chase enemy HomeBase.");
					const yam2d::GameObject* homeBase = environmentInfo->getEnemyHomeBase(this);
					for (size_t i = 0; i < m_controllers.size(); ++i)
					{
						m_controllers[i]->resetMoveTargetObject();
						m_controllers[i]->setMoveTargetObject(homeBase, 1.0f);
					}
				}
				else
				{
					yam2d::esLogMessage("Other team picked item. Stop Moving and Shoot enemy.");

					// Stop and Shoot enemy
					for (size_t i = 0; i < m_controllers.size(); ++i)
					{
						//m_controllers[i]->resetMoveTargetObject();
						m_controllers[i]->setShootTarget(itemEvent->getCharacterController()->getGameObject(), 1.0f, 0.05f);
					}
				}
			}
			else if (eventName == "ItemDropped")
			{
				ItemEvent* itemEvent = dynamic_cast<ItemEvent*>(eventObject);
				assert(itemEvent != 0);
				yam2d::esLogMessage("Item dropped. Stop Shooting and Chase Dynamite.");

				// Start going straight to dynamite
				const yam2d::GameObject* dynamite = environmentInfo->getDynamite();
				for (size_t i = 0; i < m_controllers.size(); ++i)
				{
					m_controllers[i]->resetShootTarget();
					m_controllers[i]->setMoveTargetObject(dynamite, 1.0f);
					m_controllers[i]->preferPickItem();
				}
			}
			else
			{
				// Ignore rest message ids.
			}
		}

		virtual void onGameObjectEvent(GameEnvironmentInfoProvider* environmentInfo, yam2d::GameObject* gameObject, const std::string& eventName, yam2d::Object* eventObject)
		{
			if (eventName == "Collision")
			{
				CollisionEvent* collisionEvent = dynamic_cast<CollisionEvent*>(eventObject);
				assert(collisionEvent != 0);
				if (!collisionEvent->isValid()) return;
				yam2d::GameObject* otherGo = collisionEvent->getOtherGameObject();
				std::string otherType = otherGo->getType();
				yam2d::vec2 localNormal = collisionEvent->getLocalNormal();
			}
			else if (eventName == "TakingDamage")
			{
				int teamIndex = gameObject->getProperties()["teamIndex"].get<int>();

				TakingDamageEvent* damageEvent = dynamic_cast<TakingDamageEvent*>(eventObject);
				yam2d::GameObject* damageFromObject = damageEvent->getFromObject();
				float newHealth = damageEvent->getNewHealth();
				//	yam2d::esLogMessage("%s(team=%d) %s: fromObject=%s. New health: %3.1f", gameObject->getType().c_str(), teamIndex, eventName.c_str(), damageFromObject->getType().c_str(), newHealth);
			}
			else if (eventName == "ZeroHealth")
			{
				int teamIndex = gameObject->getProperties()["teamIndex"].get<int>();
				yam2d::esLogMessage("%s(team=%d) %s.", gameObject->getType().c_str(), teamIndex, eventName.c_str());
			}
			else
			{
				assert(0); // Should be impossible, because unknown message id.
			}
		}

	};


	PlayerController* createNewPlayer()
	{
		return new LobsterAIPlayer();
	}
}



