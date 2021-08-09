#pragma once
#ifndef __RADIUS_CONDITION__
#define __RADIUS_CONDITION__
#include "ConditionNode.h"
class RadiusCondition : public ConditionNode
{
public:
	RadiusCondition(Character* character);
	~RadiusCondition();
	bool Condition() override;
};

#endif // __RADIUS_CONDITION__