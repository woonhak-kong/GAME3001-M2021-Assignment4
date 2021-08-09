#include "LowHealthCondition.h"

LowHealthCondition::LowHealthCondition(Character* character) :
	ConditionNode(character)
{
}

LowHealthCondition::~LowHealthCondition()
{
}

bool LowHealthCondition::Condition()
{
	int curHp = m_pCharacter->getPresentHp();
	int maxHp = m_pCharacter->getMaxHp();
	float percentage = static_cast<float>(curHp) / static_cast<float>(maxHp);
	if(percentage <= 0.25f)
	{
		return true;
	}
	return false;
}
