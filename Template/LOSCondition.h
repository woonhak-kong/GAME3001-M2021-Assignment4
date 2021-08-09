#pragma once
#include "ConditionNode.h"
class LOSCondition : public ConditionNode
{
public:
	LOSCondition(Character* character);
	~LOSCondition();
	bool Condition() override;
};

