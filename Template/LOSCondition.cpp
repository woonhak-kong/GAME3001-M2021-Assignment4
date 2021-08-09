#include "LOSCondition.h"

#include "CollisionManager.h"
#include "Util.h"
#include "Scene.h"

LOSCondition::LOSCondition(Character* character) :
	ConditionNode(character)
{
}

LOSCondition::~LOSCondition()
{
}

bool LOSCondition::Condition()
{
	auto player = m_pCharacter->getParent()->getPlayer();
	glm::vec2 playerPosition = m_pCharacter->getParent()->getPlayer()->getCenterPosition();
	glm::vec2 selfPosition = m_pCharacter->getCenterPosition();
	glm::vec2 direction = playerPosition - selfPosition;

	direction = Util::normalize(direction);
	m_pCharacter->setCurrentDirection(direction);

	bool losDistanceCheck = CollisionManager::lineRectCheck(selfPosition, selfPosition + m_pCharacter->getCurrentDirection() * m_pCharacter->getLOSDistance(),
		{ player->getRealCollisionRect().x, player->getRealCollisionRect().y }, player->getRealCollisionRect().w, player->getRealCollisionRect().h);
	if (losDistanceCheck)
	{
		bool isObstacleThere = CollisionManager::LOSCheckWithNode(m_pCharacter, player);
		if (isObstacleThere)
		{
			//std::cout << "true "<< std::endl;
			m_pCharacter->setHasLOS(false);
			return false;
		}
		else
		{
			m_pCharacter->setHasLOS(true);
			return true;
		}
	}
	m_pCharacter->setHasLOS(false);
	return false;
}
