#pragma once
#ifndef __ACTION_NODE__
#define __ACTION_NODE__
#include "ActionNode.h"
class FleeAction : public ActionNode
{
public:
	FleeAction(Character* character);
	~FleeAction();
	void Action() override;

	std::vector<glm::vec2> m_patrolPlaces;
	int m_curPatrolGoalIDX;
	int m_preShortestIDX;

	float m_waitingTime;
	bool m_isGiveBirth;
};

#endif // __ACTION_NODE__