#pragma once
#include "ActionNode.h"
class MoveToLOSAction : public ActionNode
{
public:
	MoveToLOSAction(Character* character);
	~MoveToLOSAction();
	void Action() override;

	std::vector<glm::vec2> m_patrolPlaces;
	int m_curPatrolGoalIDX;
	int m_preShortestIDX;
};

