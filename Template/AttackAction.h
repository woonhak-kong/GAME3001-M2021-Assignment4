#pragma once
#ifndef __ATTACK_ACTION__
#define __ATTACK_ACTION__
#include "ActionNode.h"
class AttackAction : public ActionNode
{
public:
	AttackAction(Character* character);
	~AttackAction();
	void Action() override;
};

#endif // __ATTACK_ACTION__