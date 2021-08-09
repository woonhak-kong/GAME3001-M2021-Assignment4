#include "RadiusCondition.h"
#include "Scene.h"
#include "Util.h"

RadiusCondition::RadiusCondition(Character* character):
	ConditionNode(character)
{
}

RadiusCondition::~RadiusCondition()
{
}

bool RadiusCondition::Condition()
{
	//auto player = m_pCharacter->getParent()->getPlayer();
	glm::vec2 playerPosition = m_pCharacter->getParent()->getPlayer()->getCenterPosition();
	glm::vec2 selfPosition = m_pCharacter->getCenterPosition();
	//glm::vec2 direction = playerPosition - selfPosition;
	float distance = Util::distance(selfPosition, playerPosition);

	if (distance <= m_pCharacter->getRadiusDistance())
	{
		return true;
	}
	return false;
}
