#include "FleeAction.h"

#include "EnemyHuman1.h"
#include "EnemyHuman2.h"
#include "Game.h"
#include "Scene.h"
#include "Util.h"

FleeAction::FleeAction(Character* character) :
	ActionNode(character),
	m_isGiveBirth(false)
{
	//m_patrolPlaces.push_back({ 4,4 });
	m_patrolPlaces.push_back({ 5,30 });
	//m_patrolPlaces.push_back({ 5,42 });
	m_patrolPlaces.push_back({ 5,69 });
	//m_patrolPlaces.push_back({ 6,33 });
	//m_patrolPlaces.push_back({ 10,7 });
	m_patrolPlaces.push_back({ 13,64 });
	m_patrolPlaces.push_back({ 20,30 });
	m_patrolPlaces.push_back({ 20,67 });
	//m_patrolPlaces.push_back({ 25,42 });
	m_patrolPlaces.push_back({ 29,70 });
	//m_patrolPlaces.push_back({ 32,29 });
	m_patrolPlaces.push_back({ 33,6 });
	m_patrolPlaces.push_back({ 34,50 });
	m_patrolPlaces.push_back({ 37,72 });
	m_patrolPlaces.push_back({ 41,22 });


	m_curPatrolGoalIDX = 0;
	m_preShortestIDX = 99;
	m_waitingTime = 0;
}

FleeAction::~FleeAction()
{
}

void FleeAction::Action()
{
	if (m_isActionDone)
	{
		auto target = m_pCharacter->getParent()->getPlayer();
		int shortestDistance = INT_MIN;
		int shortestIDX = 0;
		for (int i = 0; i < m_patrolPlaces.size(); i++)
		{
			int distance = Util::distance(static_cast<Character*>(target)->getGridPosition(), m_patrolPlaces[i]);
			if (shortestDistance < distance)
			{
				if (m_preShortestIDX != i)
				{
					shortestDistance = distance;
					//std::cout << shortestDistance << std::endl;
					shortestIDX = i;
				}
			}
		}

		m_preShortestIDX = shortestIDX;

		m_pCharacter->calculateF(m_patrolPlaces[shortestIDX]);
		m_pCharacter->findAStarPath();
		m_isActionDone = false;
	}
	else
	{
		if (!m_pCharacter->moveToPath())
		{
			m_waitingTime += Game::Instance().getDeltaTime();
			m_pCharacter->idle();
			if(m_waitingTime > 2)
			{
				m_isActionDone = true;
				m_waitingTime = 0;
				if(!m_isGiveBirth)
				{
					glm::vec2 position = m_patrolPlaces[rand() % m_patrolPlaces.size()];
					if (rand() % 2 == 0)
					{
						LoaderParams loader = LoaderParams(position.y * Config::TILE_SIZE, position.x * Config::TILE_SIZE,
							32, 32, 32, 32, 300, 20, "zombie");
						EnemyHuman1* enemy = new EnemyHuman1(loader);
						enemy->setNodeList(m_pCharacter->getParent()->getNodeList());
						m_pCharacter->getParent()->addChild(enemy, 4);
					}
					else
					{
						LoaderParams loader = LoaderParams(position.y * Config::TILE_SIZE, position.x * Config::TILE_SIZE,
							32, 32, 32, 32, 300, 20, "zombie");
						EnemyHuman2* enemy = new EnemyHuman2(loader);
						enemy->setNodeList(m_pCharacter->getParent()->getNodeList());
						m_pCharacter->getParent()->addChild(enemy, 4);
					}
					m_isGiveBirth = true;
				}
			}

		}
	}
}
