#pragma once
#ifndef __LOW_HEALTH_CONDITION__
#define __LOW_HEALTH_CONDITION__
#include "ConditionNode.h"

class LowHealthCondition : public ConditionNode
{
public:
	LowHealthCondition(Character* character);
	~LowHealthCondition();
	bool Condition() override;
};

#endif // __LOW_HEALTH_CONDITION__