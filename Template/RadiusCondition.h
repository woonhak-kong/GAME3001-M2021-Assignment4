#pragma once
#include "ConditionNode.h"
class RadiusCondition : public ConditionNode
{
public:
	RadiusCondition(Character* character);
	~RadiusCondition();
	bool Condition() override;
};

