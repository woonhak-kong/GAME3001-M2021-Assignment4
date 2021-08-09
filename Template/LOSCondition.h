#pragma once
#include "ConditionNode.h"
class LOSCondition : public ConditionNode
{
public:
	LOSCondition();
	~LOSCondition();
	bool Condition() override;
};

