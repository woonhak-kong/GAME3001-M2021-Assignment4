#pragma once
#ifndef __PATROL_ACTION__
#define __PATROL_ACTION__
#include "ActionNode.h"
class PatrolAction : public ActionNode
{
public:
	PatrolAction(Character* character);
	~PatrolAction();
	void Action() override;

	std::vector<glm::vec2> m_patrolPlaces;
	int m_curPatrolGoalIDX;
};

#endif // __PATROL_ACTION__