#include "MoveToPlayerAction.h"

#include "Scene.h"

MoveToPlayerAction::MoveToPlayerAction(Character* character) :
	ActionNode(character)
{
}

MoveToPlayerAction::~MoveToPlayerAction()
{
}

void MoveToPlayerAction::Action()
{
	if (m_isActionDone)
	{
		int newPatrolGoal;
		auto target = static_cast<Character*>(m_pCharacter->getParent()->getPlayer());

		m_pCharacter->calculateF(target->getGridPosition());
		m_pCharacter->findAStarPath();
		m_isActionDone = false;
	}
	else
	{
		if (!m_pCharacter->moveToPath())
		{
			m_isActionDone = true;
		}
	}
}
