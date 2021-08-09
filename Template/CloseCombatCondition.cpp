#include "CloseCombatCondition.h"

#include "Util.h"
#include "Scene.h"

CloseCombatCondition::CloseCombatCondition(Character* character) :
	ConditionNode(character)
{
}

CloseCombatCondition::~CloseCombatCondition()
{
}

bool CloseCombatCondition::Condition()
{
	glm::vec2 playerPosition = m_pCharacter->getParent()->getPlayer()->getCenterPosition();
	glm::vec2 selfPosition = m_pCharacter->getCenterPosition();
	//glm::vec2 direction = playerPosition - selfPosition;
	float distance = Util::distance(selfPosition, playerPosition);

	if (distance <= 60.f)
	{
		return true;
	}
	return false;
}
