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
		auto middleTarget = target->getMiddlePosition();
		m_pCharacter->calculateF({(middleTarget.y +target->getRealCollisionRect().h )/ Config::TILE_SIZE, middleTarget.x / Config::TILE_SIZE});
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
