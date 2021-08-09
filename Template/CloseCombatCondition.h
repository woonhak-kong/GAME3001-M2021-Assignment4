#pragma once
#ifndef __CLOSE_COMBAT_CONDITION__
#define __CLOSE_COMBAT_CONDITION__
#include "ConditionNode.h"
class CloseCombatCondition : public ConditionNode
{
public:
	CloseCombatCondition(Character* character);
	~CloseCombatCondition();
	bool Condition() override;
};

#endif // __CLOSE_COMBAT_CONDITION__