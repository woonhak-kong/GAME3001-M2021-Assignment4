#pragma once
#include "ActionNode.h"
class MoveToPlayerAction : public ActionNode
{
public:
	MoveToPlayerAction(Character* character);
	~MoveToPlayerAction();
	void Action() override;
};

