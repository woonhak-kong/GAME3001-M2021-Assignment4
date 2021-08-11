#include "RangeCombatCondition.h"

#include "Util.h"
#include "Scene.h"

RangeCombatCondition::RangeCombatCondition(Character* character) :
	ConditionNode(character)
{
}

RangeCombatCondition::~RangeCombatCondition()
{
}

bool RangeCombatCondition::Condition()
{
	glm::vec2 playerPosition = m_pCharacter->getParent()->getPlayer()->getCenterPosition();
	glm::vec2 selfPosition = m_pCharacter->getCenterPosition();
	//glm::vec2 direction = playerPosition - selfPosition;
	float distance = Util::distance(selfPosition, playerPosition);

	if (distance <= 300.f)
	{
		return true;
	}
	return false;
}
