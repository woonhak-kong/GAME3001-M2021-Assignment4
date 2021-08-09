#pragma once
#ifndef __LOS_CONDITION__
#define __LOS_CONDITION__
#include "ConditionNode.h"
class LOSCondition : public ConditionNode
{
public:
	LOSCondition(Character* character);
	~LOSCondition();
	bool Condition() override;
};

#endif // __LOS_CONDITION__