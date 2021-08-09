#include "EnemyHumanAI.h"
#include <iostream>

#include "Character.h"
#include "CollisionManager.h"
#include "Scene.h"
#include "SoundID.h"
#include "SoundManager.h"
#include "Util.h"

EnemyHumanAI::EnemyHumanAI(Character* character) :
	GameAI(character),
	m_previousPostion({ 0,0 })
{
}

void EnemyHumanAI::update()
{
	auto player = m_self->getParent()->getPlayer();
	glm::vec2 playerPosition = m_self->getParent()->getPlayer()->getCenterPosition();
	glm::vec2 selfPosition = m_self->getCenterPosition();
	glm::vec2 direction = playerPosition - selfPosition;

	direction = Util::normalize(direction);
	m_self->setCurrentDirection(direction);

	bool losDistanceCheck = CollisionManager::lineRectCheck(selfPosition, selfPosition + m_self->getCurrentDirection() * m_self->getLOSDistance(),
		{ player->getRealCollisionRect().x, player->getRealCollisionRect().y }, player->getRealCollisionRect().w, player->getRealCollisionRect().h);

	// if target is in range
	if(losDistanceCheck)
	{
		m_self->setDetectionRadius(true);
		// check if there is obstacle bewtween them.
		bool losCheck = CollisionManager::LOSCheckWithNode(m_self, player);
		if (losCheck)
		{
			//std::cout << "true "<< std::endl;
			m_self->setHasLOS(false);
		}
		else
		{
			m_self->setHasLOS(true);
		}

	}
	else
	{
		m_self->setHasLOS(false);
		m_self->setDetectionRadius(false);
	}

	//int distanceY = abs(playerPosition.y - selfPosition.y);
	//float distance = sqrt(distanceX * distanceX + distanceY * distanceY);
	//int direction = 0;
	////std::cout << "distance : " << distance << std::endl;

	//if (playerPosition.y > selfPosition.y - 100 && playerPosition.y < selfPosition.y + 100)
	//{

	if (m_isGoingRight)
	{
		m_self->moveToRight();
		if (selfPosition.x > 1000)
			m_isGoingRight = false;
	}
	else
	{
		m_self->moveToLeft();
		if (selfPosition.x < 500)
			m_isGoingRight = true;
	}

	//	if (distance > 500)
	//	{
	//		m_self->idle();
	//	}
	//	else
	//	{
	//		direction = playerPosition.x - selfPosition.x;
	//		if (distance > 50)
	//		{

	//			if (m_previousPostion.x == selfPosition.x && m_self->getCurrentState() == CharacterState::RUN)
	//			{
	//				m_self->jump();
	//			}
	//			if (direction < 0)
	//			{
	//				m_self->moveToLeft();
	//			}
	//			else if (direction > 0)
	//			{
	//				m_self->moveToRight();
	//			}
	//			m_previousPostion = selfPosition;
	//		}
	//		else
	//		{

	//			m_self->attack();

	//		}

	//	}
	//}
	//else
	//{
	//	m_self->idle();
	//}


}
