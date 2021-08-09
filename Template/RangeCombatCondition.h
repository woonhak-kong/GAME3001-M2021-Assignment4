#pragma once
#include "ConditionNode.h"
class RangeCombatCondition : public ConditionNode
{
public:
	RangeCombatCondition(Character* character);
	~RangeCombatCondition();
	bool Condition() override;
};

